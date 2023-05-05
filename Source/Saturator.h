#include <JuceHeader.h>

namespace ub 
{
    class Saturator 
    {
        public:
           
            void applySaturation(juce::dsp::AudioBlock<float>& inputBlock, float drive, float mix); 
        private:
            float piDivisor = 2.0f / juce::MathConstants<float>::pi;
            float softClipper(float samples, float drive);
            
            int numChannels { 2 };
    };
}