/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class SimpleLofiFilterAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleLofiFilterAudioProcessor();
    ~SimpleLofiFilterAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float getNoiseLevel() const { return *noiseLevel; }
    void setNoiseLevel(float newValue) { *noiseLevel = newValue; }

    float getNoiseTone() const { return *noiseTone; }
    void setNoiseTone(float newValue) { *noiseTone = newValue; }

    float getNoiseFlux() const { return *noiseFlux; }
    void setNoiseFlux(float newValue) { *noiseFlux = newValue; }

    float getNoiseType() const { return *noiseType; }
    void setNoiseType(float newValue) { *noiseType = newValue; }

    float getCrackleLevel() const { return *crackleLevel; }
    void setCrackleLevel(float newValue) { *crackleLevel = newValue; }

    float getWowFlutterIntensity() const { return *wowFlutterIntensity; }
    void setWowFlutterIntensity(float newValue) { *wowFlutterIntensity = newValue; }

    float getBitDepth() const { return *bitDepth; }
    void setBitDepth(float newValue) { *bitDepth = newValue; }

    float getSampleRateReduction() const { return *sampleRateReduction; }
    void setSampleRateReduction(float newValue) { *sampleRateReduction = newValue; }

    float getDistortionLevel() const { return *distortionLevel; }
    void setDistortionLevel(float newValue) { *distortionLevel = newValue; }

    float getDistortionTone() const { return *distortionTone; }
    void setDistortionTone(float newValue) { *distortionTone = newValue; }

    float getDistortionMix() const { return *distortionMix; }
    void setDistortionMix(float newValue) { *distortionMix = newValue; }

    float getLowCutFreq() const { return *lowCutFreq; }
    void setLowCutFreq(float newValue) { *lowCutFreq = newValue; }

    float getHighCutFreq() const { return *highCutFreq; }
    void setHighCutFreq(float newValue) { *highCutFreq = newValue; }

    float getCrackleType() const { return *crackleType; }
    void setCrackleType(float newValue) { *crackleType = newValue; }

    float getWowFlutterStrength() const { return *wowFlutterStrength; }
    void setWowFlutterStrength(float newValue) { *wowFlutterStrength = newValue; }

    float getWowFlutterSpeed() const { return *wowFlutterSpeed; }
    void setWowFlutterSpeed(float newValue) { *wowFlutterSpeed = newValue; }

    juce::AudioProcessorValueTreeState parameters;

private:

    std::atomic<float>* noiseLevel;
    std::atomic<float>* noiseTone;
    std::atomic<float>* noiseFlux;
    std::atomic<float>* noiseType;

    std::atomic<float>* crackleLevel;
    std::atomic<float>* crackleType;

    std::atomic<float>* wowFlutterIntensity;
    std::atomic<float>* wowFlutterStrength;
    std::atomic<float>* wowFlutterSpeed;

    std::atomic<float>* bitDepth;
    std::atomic<float>* sampleRateReduction;

    std::atomic<float>* distortionLevel;
    std::atomic<float>* distortionTone;
    std::atomic<float>* distortionMix;

    std::atomic<float>* lowCutFreq;
    std::atomic<float>* highCutFreq;

    std::atomic<float>* noiseBypass;
    std::atomic<float>* crackleBypass;
    std::atomic<float>* wowFlutterBypass;
    std::atomic<float>* bitDepthBypass;
    std::atomic<float>* filterBypass;
    std::atomic<float>* distortionBypass;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> lowCutFilter;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> highCutFilter;

    void updateFilters(juce::AudioBuffer<float>& buffer);
    float generateWhiteNoise();
    float generatePinkNoise();
    float generateBrownNoise();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleLofiFilterAudioProcessor)
};
