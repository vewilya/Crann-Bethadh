/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Title.h"
#include "RotaryKnobStyleSheet.h"
#include "ColourMenu.h"

//==============================================================================
/**
*/
class ProcessBlockAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ProcessBlockAudioProcessorEditor (CrannBethadhAudioProcessor&);
    ~ProcessBlockAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    float colPosOne { .9f }, colPosTwo { .1f };
    
    ub::Title title;
    
    // Reference Audio Processor
    CrannBethadhAudioProcessor& audioProcessor;
    
    // Set up Main Knob
    BigKnob myKnob;

    // Colour Menu
    ub::ColourMenu colourMenu;
    
    // Slider Attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttach;
 
    // IR Menu
    void colourMenuChanged();
     
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProcessBlockAudioProcessorEditor)
};
