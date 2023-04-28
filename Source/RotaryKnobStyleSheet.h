/*
  ==============================================================================

    StyleSheet.h
    Created: 21 Mar 2023 8:41:50pm
    Author:  Urs Bollhalder

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustomLAF : public juce::LookAndFeel_V4
{
public:
    CustomLAF();
    // juce::Slider::SliderLayout getSliderLayout (juce::Slider& slider) override;

    void drawRotarySlider (juce::Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider) override;  
    
};

class BigKnob : public juce::Slider
{
public:
    BigKnob()
    {
        setLookAndFeel(&myLAF);
        auto rotaryParameters = getRotaryParameters();
        rotaryParameters.startAngleRadians = juce::MathConstants<float>::pi * 1.25f;
        rotaryParameters.endAngleRadians = juce::MathConstants<float>::pi * 2.75f;
        rotaryParameters.stopAtEnd = true;
        setRotaryParameters (rotaryParameters);
        setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange);
        setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
;    }
    
    ~BigKnob()
    {
        setLookAndFeel(nullptr);
    }
public:

   
private:
    CustomLAF myLAF;
    juce::ImageComponent maskImage;
};