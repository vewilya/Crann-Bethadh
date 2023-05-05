/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Saturator.h"
#include "Convolver.h"
#include <array>

constexpr auto MIX_PARAMETER = "mix";

//==============================================================================
/**
*/
class CrannBethadhAudioProcessor  : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
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
private:
    
    juce::AudioProcessorValueTreeState treeState;
    juce::dsp::ProcessSpec spec;
    juce::AudioBuffer<float> wetBuffer;
    
    float rawDrive = 1.0f;
    float rawMix = 0.0f;
    float rawConvo = 0.0f;
    float rawDryGain { 1.0f };
    
    static constexpr float piDivisor = 2.0f / juce::MathConstants<float>::pi;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    
    juce::dsp::Oversampling<float> oversampling;

    std::array<ub::Saturator, 2> channelSaturators;
    // std::array<ub::Convolver, 2> channelConvolvers;
    ub::Convolver convolver;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrannBethadhAudioProcessor)
};
