#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include <choc_WebView.h>

//==============================================================================
/**
*/
class CrannBethadhAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CrannBethadhAudioProcessorEditor (CrannBethadhAudioProcessor&);
    ~CrannBethadhAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::unique_ptr<choc::ui::WebView> webView;

    CrannBethadhAudioProcessor& processorRef;
    
    //==============================================================================
    choc::value::Value handleSetParameterValueEvent(const choc::value::ValueView& e);

    #if JUCE_MAC
        juce::NSViewComponent viewContainer;
    #elif JUCE_WINDOWS
        juce::HWNDComponent viewContainer;
    #else
        #error "No Linux support"
    #endif
    
    // Reference Audio Processor
    CrannBethadhAudioProcessor& audioProcessor;
    
    void colourMenuChanged();
     
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrannBethadhAudioProcessorEditor)
};
