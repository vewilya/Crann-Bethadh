/*
  ==============================================================================

    StyleSheet.cpp
    Created: 21 Mar 2023 8:41:50pm
    Author:  Urs Bollhalder

  ==============================================================================
*/

#include "RotaryKnobStyleSheet.h"

CustomLAF::CustomLAF()
{
//    auto robotFont = juce::Typeface::createSystemTypefaceFor (Resources::Barlow_Medium, Resources::Barlow_MediumSize);
//    setDefaultSansSerifTypeface (robotFont);

}

juce::Slider::SliderLayout CustomLAF::getSliderLayout (juce::Slider& slider)
{
    juce::Slider::SliderLayout layout;
    layout.sliderBounds = juce::Rectangle<int> (0, 0, 300, 300);
    return layout;
}


void CustomLAF::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                                       const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    auto outline = slider.findColour (juce::Slider::rotarySliderOutlineColourId);
    auto fill    = slider.findColour (juce::Slider::rotarySliderFillColourId);
    
    auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat();
    
    auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 3.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = juce::jmax (1.5f, radius * 0.05f);
    auto arcRadius = radius - lineW * 0.9f;
    
    // Background Checker
   g.fillAll(juce::Colours::orange);
//        juce::Rectangle<float> bgRect (0.0f, 0.0f, bounds.getWidth(), bounds.getHeight());
//        g.setColour(juce::Colours::black);
//        g.fillRect(bgRect);
    
    juce::Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius+1.7f,
                                 arcRadius+1.7f,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);
    
    g.setColour (outline.withAlpha(.1f + sliderPos * .9f));
    g.strokePath (backgroundArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
    juce::Point<float> thumbPoint (bounds.getCentreX() + (arcRadius - 10.0f) * std::cos (toAngle - juce::MathConstants<float>::halfPi),
                                   bounds.getCentreY() + (arcRadius - 10.0f) * std::sin (toAngle - juce::MathConstants<float>::halfPi));
    
    g.setColour (fill);
    
    
    // Acutal Outer Value Arc
    if (slider.isEnabled())
    {
        // Center Circles
        float widener = (bounds.getWidth() * .4) - 20.*exp2(sliderPos);
        juce::Path centerCricle;
        centerCricle.addCentredArc (bounds.getWidth()*.5f,
                                    bounds.getHeight()*.5f,
                                    arcRadius,
                                    arcRadius,
                                    0.0f,
                                    0,
                                    2*juce::MathConstants<float>::pi * 2.75f,
                                    true);
        g.setGradientFill(juce::ColourGradient((juce::Colours::green).withBrightness(sliderPos*.7), bounds.getWidth()*.5, bounds.getWidth()*.5, (juce::Colours::black).withMultipliedAlpha(sliderPos*.2), widener, widener, true));
        g.fillPath(centerCricle);
        
        // Shadow
        juce::DropShadow ds((juce::Colours::white.withAlpha(sliderPos)), 100 * juce::jmin(pow(sliderPos, 11), 1.0) + 1 ,{0,0});
        ds.drawForPath(g, centerCricle);
        
        // Outer Circle
        juce::Path outerCricle;
        outerCricle.addCentredArc (bounds.getWidth()*.5f,
                                   bounds.getHeight()*.5f,
                                   arcRadius,
                                   arcRadius,
                                   0.0f,
                                   0,
                                   2*juce::MathConstants<float>::pi * 2.75f,
                                   true);
        
        const juce::Colour outerCircleColour (juce::Colour::fromString ("FF179595"));
        
        g.setGradientFill(juce::ColourGradient(outerCircleColour.withBrightness(sliderPos), bounds.getWidth()*.5, bounds.getWidth()*.5, juce::Colours::black, widener, widener, true));
        g.fillPath(outerCricle);
        
        // Image Layer
        g.setOpacity(sliderPos*.3 +.1);
        auto circleCenterX = bounds.getWidth()*.5f - radius + lineW;
        auto circleCenterY = bounds.getHeight()*.5f - radius + lineW;
        auto mask = juce::ImageCache::getFromMemory(BinaryData::Mask_png, BinaryData::Mask_pngSize);
        g.drawImageWithin(mask, circleCenterX, circleCenterY, arcRadius*2, arcRadius*2, 4);
//        auto transform = juce::AffineTransform::scale (bounds.getWidth(), bounds.getHeight()).rotated (sliderPos, bounds.getCentreX(), bounds.getCentreY());
//
//        g.drawImageTransformed (mask, transform);
        
        // Value Arc
        juce::Path valueArc;
        valueArc.addCentredArc (bounds.getWidth()*.5f,
                                bounds.getHeight()*.5f,
                                arcRadius+1.7f,
                                arcRadius+1.7f,
                                0.0f,
                                rotaryStartAngle,
                                toAngle,
                                true);
        
        const juce::Colour arcColour (juce::Colour::fromString ("FF29F6F8"));
        g.setGradientFill(juce::ColourGradient::horizontal( (juce::Colours::orange), bounds.getWidth()*.9-.8*sliderPos, (arcColour).withBrightness(sliderPos*.3).withMultipliedAlpha((1.0 - sliderPos*.2)), bounds.getWidth()*.4 - .2*sliderPos));
        g.strokePath (valueArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        
        g.setGradientFill(juce::ColourGradient::horizontal((juce::Colours::transparentBlack), bounds.getWidth()*.1, (juce::Colours::lavender ).withBrightness(sliderPos*.9).withMultipliedAlpha((1.0 - sliderPos*.2)), bounds.getWidth()*.4));
        g.strokePath (valueArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        
    }
    
   
}
