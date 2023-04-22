/*
  ==============================================================================

    MenuStyleSheet.cpp
    Created: 25 Mar 2023 10:53:33am
    Author:  Urs Bollhalder

  ==============================================================================
*/

#include "MenuStyleSheet.h"

void juce::myMenuLAF::drawComboBox (Graphics& g, int width, int height, bool,
                                   int, int, int, int, ComboBox& box)
{   
    auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : 7.0f;
    Rectangle<int> boxBounds (0, 0, width, height);

    g.setColour (box.findColour (ComboBox::backgroundColourId));
    g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);

    g.setColour (box.findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (boxBounds.toFloat().reduced (0.5f, 0.5f), cornerSize, 1.0f);
    
    Rectangle<int> arrowZone (width - 30, 0, 20, height);
    
    Path circle;
    circle.addCentredArc (boxBounds.getWidth() - arrowZone.getWidth()*.8,
                        arrowZone.getHeight()*.5,
                        5.0f,
                        5.0f,
                        0.0f,
                        0,
                        2*juce::MathConstants<float>::pi * 2.75f,
                        true);
    g.setGradientFill(juce::ColourGradient((juce::Colours::green).withBrightness(.7), arrowZone.getWidth()*.5, arrowZone.getWidth()*.5, (juce::Colours::black).withMultipliedAlpha(.5), 5.0f, 4.0f, true));

    g.setColour (box.findColour (ComboBox::arrowColourId).withAlpha (.7f));
    
    g.fillPath(circle);

}
