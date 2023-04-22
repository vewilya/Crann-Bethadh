/*
  ==============================================================================

    Title.h
    Created: 20 Apr 2023 5:14:25pm
    Author:  Urs Bollhalder

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
namespace ub {


class Title  : public juce::Component
{
public:
    Title();
    ~Title() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Title)
    
    juce::ImageComponent mImageComponent;
};
}
