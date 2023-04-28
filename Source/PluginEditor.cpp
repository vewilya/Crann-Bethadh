/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProcessBLockAudioProcessorEditor::ProcessBLockAudioProcessorEditor (CrannBethadhAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Title
    addAndMakeVisible(title);
    
    // UI Size and Resizing
    setSize (500, 500);
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(1.0);
    setResizeLimits(400, 400, 750, 750);
    
    // IR Loader
    addAndMakeVisible(colourMenu);
    colourMenu.addSectionHeading ("Atmosphere");
    colourMenu.addItem ("Plains",  1);
    colourMenu.addItem ("Broken Glass",   2);
    colourMenu.addItem ("Freezing Frenzie", 3);
    colourMenu.addSeparator();
    colourMenu.addSectionHeading ("Noises");
    colourMenu.addItem ("Bursts",  4);
    colourMenu.addItem ("Crackle",   5);
    colourMenu.addItem ("Boom", 6);
    
    colourMenu.setSelectedId (1);
    colourMenu.onChange = [this] { colourMenuChanged(); };
        
    addAndMakeVisible(myKnob);
    myKnob.setSize(getWidth() * .4, getWidth() * .4
                   );
    
    mixSliderAttach =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.getTreeState(), MIX_PARAMETER, myKnob);

}

ProcessBLockAudioProcessorEditor::~ProcessBLockAudioProcessorEditor()
{
}

//==============================================================================
void ProcessBLockAudioProcessorEditor::paint (juce::Graphics& g)
{
    const juce::Colour bgColourOne (juce::Colour::fromString ("FF0B4B55"));
    const juce::Colour bgColourTwo (juce::Colour::fromString ("FF000000"));
    
    g.setGradientFill(juce::ColourGradient::vertical(bgColourTwo, getHeight() * colPosOne
                                                     , bgColourOne, getHeight() * colPosTwo));
    g.fillAll();

    g.setGradientFill(juce::ColourGradient::vertical(bgColourOne, getHeight() * .8f
                                              , bgColourTwo, getHeight() * .1f));
    
    for(auto i = 0; i < 8; i++)
    {
        if (i > 4)
        {
            juce::Line<float> line (juce::Point<float> (getWidth()/9*i, getHeight()),
                                        juce::Point<float> (getWidth()/9*(i+9), 0));
            g.setOpacity(1.0f - 1.0f / (i+1));
            g.drawLine (line, 4.0f/(i+1));
        }
        else
        {
            juce::Line<float> line (juce::Point<float> (0, getHeight()/(i+1)),
                                        juce::Point<float> (getWidth()/(i+1), 0));
            g.setOpacity(1.0f - 1.0f / (i+1));
            g.drawLine (line, 5.0f/(i+1));
        }
    }
   
}

void ProcessBLockAudioProcessorEditor::resized()
{
    auto w = getWidth();
    auto h = getHeight();
    
    // Title
    title.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
    
    // IR
    colourMenu.setBounds(w * .35, 20, w * .3, 30);
    
    // LAF Slider
    myKnob.setBounds(w * .3, h * .4, w*.4, h*.4);
    myKnob.repaint();
    
}

void  ProcessBLockAudioProcessorEditor::colourMenuChanged() {
    {
        juce::File result;
     
        switch (colourMenu.getSelectedId())
        {
            case 1:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Atmosphere/UB_UB_ACM__RYMDIGARE_01.wav"); break;
            case 2:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Atmosphere/UB_UB_ACM__RYMDIGARE_02.wav"); break;
            case 3:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Atmosphere/UB_UB_ACM__RYMDIGARE_03.wav"); break;
            case 4:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Atmosphere/UB_UB_ACM__RYMDIGARE_04.wav"); break;
            case 5:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Noise/UB_UB_ACM__RYMDIGARE_05.wav"); break;
            case 6:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Noise/UB_UB_ACM__RYMDIGARE_06.wav"); break;
            case 7:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Noise/UB_UB_ACM__RYMDIGARE_07.wav"); break;
            case 8:    result = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getChildFile("BearSound/Noise/UB_UB_ACM__RYMDIGARE_08.wav"); break;
                
        }
        if (result.getFileExtension() == ".wav" | result.getFileExtension() == ".mp3")
        {
            juce::FileInputStream stream (result);
            if (stream.openedOk())
            {
                audioProcessor.getSavedFile() = result;
                // audioProcessor.getRoot() = result.getParentDirectory().getFullPathName();
                audioProcessor.getIrLoader().reset();
                audioProcessor.getIrLoader().loadImpulseResponse(result, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0); // 0 to initialise the size of the loaded file dynamically!
            }
            
        }

    }
}