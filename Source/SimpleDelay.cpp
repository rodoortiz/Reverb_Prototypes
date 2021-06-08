#include "SimpleDelay.h"

SimpleDelay::SimpleDelay(int _delay)
{
    this->delay = _delay;
}

SimpleDelay::~SimpleDelay()
= default;

void SimpleDelay::processDelay(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int index = 0; index < buffer.getNumSamples(); ++index)
        {
            float sample = buffer.getReadPointer(channel)[index];

            float delayedSample = processSample(sample, channel);

            float output = (0.5f * sample) + (0.5f * delayedSample);

            buffer.getWritePointer(channel)[index] = output;
        }
    }
}

float SimpleDelay::processSample(float sample, int channel)
{
    if (delay < 1)
    {
        return sample; //When delay is equal to 0
    } else {

        readPointer = writePointer[channel] - delay;
        if (readPointer < 0)
            readPointer += delayBufferSize;

        float out = delayBuffer[readPointer][channel];

        delayBuffer[writePointer[channel]][channel] = sample;

        if (writePointer[channel] < delayBufferSize - 1)
        {
            writePointer[channel]++;
        } else {
            writePointer[channel] = 0;
        }

        return out;
    }
}

void SimpleDelay::setDelayInSamples(int newDelay)
{
    this->delay = newDelay;
}

