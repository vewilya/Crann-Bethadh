#pragma once
#include <vector>

namespace ub::dsp
{
    class DelayLine

{
public:
    
    DelayLine(): delayLine(MAX_DELAY_SIZE, .0f)
    {
    }

    
    float popSample();
    void pushSample(float sampleValue);
    void setDelay(int delaySizeValue);
    
private:
    
    int writeHead { 0 };
    int readHead;
    int delaySize { 100 };
    const int MAX_DELAY_SIZE = 2000;
    
    std::vector<float> delayLine;
};
} // namespace ub
