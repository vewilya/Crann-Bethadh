/*
  ==============================================================================

    MenuStyleSheet.h
    Created: 25 Mar 2023 10:53:33am
    Author:  Urs Bollhalder

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
namespace juce
{
class myMenuLAF : public LookAndFeel_V4
{
public:
    void drawComboBox (Graphics&, int width, int height, bool isButtonDown,
                       int buttonX, int buttonY, int buttonW, int buttonH,
                       ComboBox&) override;
    
    
private:

};
} // namespace juce
