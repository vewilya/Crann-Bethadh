/*
  ==============================================================================

    ColourMenu.h
    Created: 25 Mar 2023 11:08:47am
    Author:  Urs Bollhalder

  ==============================================================================
*/

#pragma once
#include "MenuStyleSheet.h"


namespace ub_ui
{

class ColourMenu : public juce::ComboBox, private juce::Timer
{
public:
    ColourMenu();
    
    ~ColourMenu();
private:
    
    void mouseEnter (const juce::MouseEvent& event) override;
    
    void mouseExit (const juce::MouseEvent& event) override;
    
    void timerCallback() final;
   
    juce::myMenuLAF menuLAF;
};
}
