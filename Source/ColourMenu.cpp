/*
  ==============================================================================

    ColourMenu.cpp
    Created: 25 Mar 2023 11:08:47am
    Author:  Urs Bollhalder

  ==============================================================================
*/

#include "ColourMenu.h"

ub_ui::ColourMenu::ColourMenu()
{
    setLookAndFeel (&menuLAF);
    setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::white.withAlpha(.2f));
    setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::lavender);
    setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colours::white.withAlpha(.0f));
    
    setJustificationType(juce::Justification::centred);
}


ub_ui::ColourMenu::~ColourMenu()
{
    setLookAndFeel (nullptr);
}

void ub_ui::ColourMenu::timerCallback()
{
    setColour(juce::ComboBox::ColourIds::backgroundColourId, (juce::Colours::white).withMultipliedAlpha(.3));
};

void ub_ui::ColourMenu::mouseEnter (const juce::MouseEvent& event)
{
    startTimer(100);
    
};

void ub_ui::ColourMenu::mouseExit (const juce::MouseEvent& event) 
{
    stopTimer();
//    counter = 0.0f;
    setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::white.withAlpha(.2f));
};
