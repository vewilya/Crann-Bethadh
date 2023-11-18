#pragma once

#include <JuceHeader.h>

enum SatType
{
    none,
    arcsinh1,
    arcsinh2,
    sigmoid,
    hyperbolicTangent,
};

using SatFunc = std::function<float (float, float)>;

class SaturatorBoutique
{
public:
    static SatFunc getSaturator (SatType type)
    {
        if (type == SatType::arcsinh1) 
            return [] (float x, float drive) { return hyperboleSine (x, drive); };

        if (type == SatType::arcsinh2) 
            return [] (float x, float drive) { return hyperboleSine (x, drive); };
        
        if (type == SatType::sigmoid) 
            return [] (float x, float drive) { return sigmoid (x, drive); };

        if (type == SatType::hyperbolicTangent)
            return [] (float x, float drive) { return hyperbolicTangent (x, drive); };    
        

        return [] (float x, float drive) { return x; };

    }

    static inline float hyperboleSine (float x, float drive)
    {        

        const auto out = asinhf(drive * x) / asinhf(drive);

        return out;
    }

    static inline float arcsinh (float x, float drive) 
    {
        return asinhf(drive * x);
    }

    static inline float sigmoid (float x, float drive) {

        const auto out = x / (1.0f + expf(-drive * x));

        return out;
    }

    static inline float hyperbolicTangent (float x, float drive)
    {
        const auto sat = tanhf(drive * x) / tanhf(drive);
        return sat;
    }

    static juce::StringArray getSatChoices() {
        return { "None", "Arcsinh 1", "Arcsinh 2", "Sigmoid", "hyperbolic Tangent" };
    }
};




