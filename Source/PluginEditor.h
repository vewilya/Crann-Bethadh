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
    
    // Saturation Menu
    juce::ComboBox saturationMenu;

    // Set up Main Knob
    BigKnob myKnob;

    // Sliders
    juce::Slider driveSlider, mixSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttach;

    juce::Label driveLabel, mixLabel; 

    // Colour Menu
    ub::ColourMenu colourMenu;
    
    // Slider Attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> convolutionSliderAttach;
 
    // IR Menu
    void colourMenuChanged();
     
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProcessBlockAudioProcessorEditor)
};
