/*
  ==============================================================================

    Title.cpp
    Created: 20 Apr 2023 5:14:25pm
    Author:  Urs Bollhalder

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Title.h"

//==============================================================================
namespace ub {


Title::Title()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

Title::~Title()
{
}

void Title::paint (juce::Graphics& g)
{
    
    // BG Image
    auto titleImage = juce::ImageCache::getFromMemory(BinaryData::title_png, BinaryData::title_pngSize);
    
    if(!titleImage.isNull())
        mImageComponent.setImage(titleImage, juce::RectanglePlacement::fillDestination);
    jassert(! titleImage.isNull());
    addAndMakeVisible(mImageComponent);
    
}

void Title::resized()
{
    // BG Image
  auto w = getWidth();
  auto h = getHeight();

  mImageComponent.setBounds(0.0f, h * .1, w, h * 0.3f);
}
}
