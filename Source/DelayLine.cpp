#include "DelayLine.h"

namespace ub::dsp
{

void DelayLine::setDelay(int delaySizeValue)
{
    this-> delaySize = delaySizeValue;
}



float DelayLine::popSample()
{
    readHead = writeHead - delaySize;
    
    if (readHead < 0) {
        readHead += MAX_DELAY_SIZE;
    }
    
    return delayLine[readHead];

}

void DelayLine::pushSample(float sampleValue)
{
    
    delayLine[writeHead] = sampleValue;
    
    writeHead++;
    writeHead %= MAX_DELAY_SIZE;
    
//    readHead = writeHead - delaySize;
//    
//    if (readHead < 0) {
//        readHead += MAX_DELAY_SIZE;
//    }
}

} // namespace ub
