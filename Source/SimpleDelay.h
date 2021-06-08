#pragma once

#include <JuceHeader.h>

class SimpleDelay {
public:
    SimpleDelay(int _delay);
    ~SimpleDelay();

    void processDelay(juce::AudioBuffer<float>& buffer);
    float processSample(float sample, int channel);

    void setDelayInSamples(int newDelay);

private:
   int delay {0};

   const int delayBufferSize = 96000;
   float delayBuffer[96000][2] = {{0.0f}};

   int writePointer[2] = {0};
   int readPointer {0};
};
