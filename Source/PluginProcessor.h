#pragma once

#include <JuceHeader.h>
#include "Saturator.h"
#include "SaturatorBoutique.h"
#include "Convolver.h"
#include "PluginParameters.h"

constexpr auto MIX_PARAMETER = "mix";
constexpr auto SATTYPE_PARAMETER = "sattype";
constexpr auto DRIVE_PARAMETER = "drive";
constexpr auto FEEDBACK_PARAMETER = "feedback";
constexpr auto CONVOLUTION_PARAMETER = "convolution";

//==============================================================================
/**
*/
class CrannBethadhAudioProcessor  : public juce::AudioProcessor, 
                                          juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    CrannBethadhAudioProcessor();
    ~CrannBethadhAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;


    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void process(juce::dsp::ProcessContextReplacing<float> context);
    void updateParameters();
    
    // Value Tree =======================================================================
    juce::AudioProcessorValueTreeState& getTreeState() {
      return treeState;
    }   

    ub::Convolver& getConvolver() {
      return convolver;
    }

    ub::dsp::Saturator& getSaturator() {
      return saturationModule;
    }
private:
    
    juce::AudioProcessorValueTreeState treeState;
    juce::dsp::ProcessSpec spec;
    juce::AudioBuffer<float> wetBuffer;
      
    ub::PluginParameters pluginParams;

    static constexpr float piDivisor = 2.0f / juce::MathConstants<float>::pi;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    
    juce::dsp::Oversampling<float> oversampling;

    ub::dsp::Saturator saturationModule;
    ub::Convolver convolver;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrannBethadhAudioProcessor)
};
