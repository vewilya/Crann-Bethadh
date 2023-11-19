#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CrannBethadhAudioProcessor::CrannBethadhAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),  treeState(*this, nullptr, "PARAMETERS",  createParameterLayout()),
oversampling (2, 3, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR)
#endif
{
    treeState.addParameterListener(MIX_PARAMETER, this);
    treeState.addParameterListener(SATTYPE_PARAMETER, this);
    treeState.addParameterListener(DRIVE_PARAMETER, this);
    treeState.addParameterListener(FEEDBACK_PARAMETER, this);
    treeState.addParameterListener(CONVOLUTION_PARAMETER, this);
}

CrannBethadhAudioProcessor::~CrannBethadhAudioProcessor()
{
    treeState.removeParameterListener(MIX_PARAMETER, this);
    treeState.removeParameterListener(SATTYPE_PARAMETER, this);
    treeState.removeParameterListener(DRIVE_PARAMETER, this);
    treeState.removeParameterListener(FEEDBACK_PARAMETER, this);
    treeState.removeParameterListener(CONVOLUTION_PARAMETER, this);
}

juce::AudioProcessorValueTreeState::ParameterLayout CrannBethadhAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    auto pMix = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { MIX_PARAMETER, 1 }, MIX_PARAMETER,  0.0f, 1.0f, 0.0f );
    auto pSatType = std::make_unique<juce::AudioParameterChoice> (juce::ParameterID { SATTYPE_PARAMETER, 1 }, SATTYPE_PARAMETER, SaturatorBoutique::getSatChoices(), 0);
    auto pDrive = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { DRIVE_PARAMETER, 1 }, DRIVE_PARAMETER,  0.0f, 1.0f, 0.0f );
    auto pFeedback = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { FEEDBACK_PARAMETER, 1 }, FEEDBACK_PARAMETER,  0.0f, 1.0f, 0.0f );
    auto pConvo = std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { CONVOLUTION_PARAMETER, 1 }, CONVOLUTION_PARAMETER,  0.0f, 1.0f, 0.0f );
    
    params.push_back(std::move(pMix));
    params.push_back(std::move(pSatType));
    params.push_back(std::move(pDrive));
    params.push_back(std::move(pFeedback));
    params.push_back(std::move(pConvo));
    return { params.begin(), params.end() };
}

void CrannBethadhAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    
    if (parameterID == MIX_PARAMETER)
    {
        pluginParams.mix = newValue;
    }
    else if (parameterID == DRIVE_PARAMETER)
    {
        pluginParams.drive = newValue;
    }
    else if (parameterID == CONVOLUTION_PARAMETER)
    {
        pluginParams.convolution = newValue;
    }

}

//==============================================================================
const juce::String CrannBethadhAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CrannBethadhAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CrannBethadhAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CrannBethadhAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CrannBethadhAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CrannBethadhAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CrannBethadhAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CrannBethadhAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CrannBethadhAudioProcessor::getProgramName (int index)
{
    return {};
}

void CrannBethadhAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CrannBethadhAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Oversampling
    oversampling.initProcessing(samplesPerBlock);
    
    // Make buffer copy
    wetBuffer.setSize(getTotalNumInputChannels(), samplesPerBlock);
    
    convolver.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());

}

void CrannBethadhAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CrannBethadhAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CrannBethadhAudioProcessor::updateParameters()
{
    // update your Parameters for your procceses here
}

/*
How to pass arguments to functions in C++:
- if the object is small (like an int), pass by copy:
void foo(int c);
- if object is large and does not need to be modified inside the function, pass by const reference:
void foo(const ClassName& c);
- if object is large and needs to be modified inside the function, pass by reference:
void foo(ClassName& c);
*/

void CrannBethadhAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    juce::ignoreUnused (midiMessages);

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Create AudioBlocks for Oversampling
    juce::dsp::AudioBlock<float> block {buffer};
    juce::dsp::AudioBlock<float> overSamplingBlock {buffer};
    
    // Oversample, Saturate and Back
    overSamplingBlock = oversampling.processSamplesUp(block);
    saturationModule.process(overSamplingBlock, pluginParams);
    oversampling.processSamplesDown(block);
    
    // Split into Dry and Wet Blocks
    wetBuffer.makeCopyOf(buffer, true);
    juce::dsp::AudioBlock<float> wetBlock {wetBuffer};
    
    // Convolve and Mix Blocks accordingly
    // convolver.process(block, wetBlock, 1.0 - pluginParams.convolution, pluginParams.convolution);
}

//==============================================================================
bool CrannBethadhAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CrannBethadhAudioProcessor::createEditor()
{
    return new ProcessBlockAudioProcessorEditor (*this);
//    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void CrannBethadhAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    //Save Param
    juce::MemoryOutputStream stream(destData, false);
    treeState.state.writeToStream (stream);
}

void CrannBethadhAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
   //Recall Param
    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
    if (tree.isValid())
    {
        treeState.state = tree;

    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CrannBethadhAudioProcessor();
}
