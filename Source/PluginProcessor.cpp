/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleLofiFilterAudioProcessor::SimpleLofiFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    parameters(*this, nullptr, "Parameters", {
    std::make_unique<juce::AudioParameterFloat>("Noise Level", "Noise Level", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterFloat>("Noise Tone", "Noise Tone", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterFloat>("Noise Flux", "Noise Flux", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterInt>("Noise Type", "Noise Type", 0.0f, 2.0f, 0.0f),

    std::make_unique<juce::AudioParameterFloat>("Crackle Level", "Crackle Level", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterInt>("Crackle Type", "Crackle Type", 0.0f, 2.0f, 0.0f),

    std::make_unique<juce::AudioParameterFloat>("Flutter Intensity", "Flutter Intensity", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterFloat>("Flutter Strength", "Flutter Strength", 0.5f, 1.5f, 0.5f),
    std::make_unique<juce::AudioParameterFloat>("Flutter Speed", "Flutter Speed", 1.0f, 2.0f, 1.0f),

    std::make_unique<juce::AudioParameterFloat>("Bit Depth", "Bit Depth", juce::NormalisableRange<float>(5.f, 32.f, 0.01f, 0.45f), 32.0f),
    std::make_unique<juce::AudioParameterFloat>("Sample Rate Reduction", "Sample Rate Reduction", 1.0f, 44100.0f, 44100.0f),

    std::make_unique<juce::AudioParameterFloat>("Distortion Level", "Distortion Level", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterFloat>("Distortion Tone", "Distortion Tone", 0.01f, 0.1f, 0.01f),
    std::make_unique<juce::AudioParameterFloat>("Distortion Mix", "Distortion Mix", 0.0f, 1.0f, 0.15f),

    std::make_unique<juce::AudioParameterFloat>("Low Cut Freq", "Low Cut Freq", juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.35f), 20.0f),
    std::make_unique<juce::AudioParameterFloat>("High Cut Freq", "High Cut Freq", juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.35f), 20000.0f),

    std::make_unique<juce::AudioParameterInt>("Noise Bypass", "Noise Bypass", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterInt>("Crackle Bypass", "Crackle Bypass", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterInt>("Wow Flutter Bypass", "Wow Flutter Bypass", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterInt>("Bit Depth Bypass", "Bit Depth Bypass", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterInt>("Filter Bypass", "Filter Bypass", 0.0f, 1.0f, 0.0f),
    std::make_unique<juce::AudioParameterInt>("Distortion Bypass", "Distortion Bypass", 0.0f, 1.0f, 0.0f),
    })
#endif
{
    noiseLevel = parameters.getRawParameterValue("Noise Level");
    noiseTone = parameters.getRawParameterValue("Noise Tone");
    noiseFlux = parameters.getRawParameterValue("Noise Flux");
    noiseType = parameters.getRawParameterValue("Noise Type");

    crackleLevel = parameters.getRawParameterValue("Crackle Level");
    crackleType = parameters.getRawParameterValue("Crackle Type");

    wowFlutterIntensity = parameters.getRawParameterValue("Flutter Intensity");
    wowFlutterStrength = parameters.getRawParameterValue("Flutter Strength");
    wowFlutterSpeed = parameters.getRawParameterValue("Flutter Speed");

    bitDepth = parameters.getRawParameterValue("Bit Depth");
    sampleRateReduction = parameters.getRawParameterValue("Sample Rate Reduction");

    distortionLevel = parameters.getRawParameterValue("Distortion Level");
    distortionTone = parameters.getRawParameterValue("Distortion Tone");
    distortionMix = parameters.getRawParameterValue("Distortion Mix");

    lowCutFreq = parameters.getRawParameterValue("Low Cut Freq");
    highCutFreq = parameters.getRawParameterValue("High Cut Freq");

    noiseBypass = parameters.getRawParameterValue("Noise Bypass");
    crackleBypass = parameters.getRawParameterValue("Crackle Bypass");
    wowFlutterBypass = parameters.getRawParameterValue("Wow Flutter Bypass");
    bitDepthBypass = parameters.getRawParameterValue("Bit Depth Bypass");
    filterBypass = parameters.getRawParameterValue("Filter Bypass");
    distortionBypass = parameters.getRawParameterValue("Distortion Bypass");
}

SimpleLofiFilterAudioProcessor::~SimpleLofiFilterAudioProcessor()
{
}

//==============================================================================
const juce::String SimpleLofiFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleLofiFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleLofiFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleLofiFilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleLofiFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleLofiFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleLofiFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleLofiFilterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleLofiFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleLofiFilterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SimpleLofiFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    lowCutFilter.prepare(spec);
    highCutFilter.prepare(spec);
}

void SimpleLofiFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleLofiFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleLofiFilterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    int bpVal = 1;

    // Check if the buffer contains audio (no effect if no audio)
    bool bufferContainsAudio = false;
    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        auto* channelData = buffer.getReadPointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            if (channelData[sample] != 0.0f) {
                bufferContainsAudio = true;
                break;
            }
        }
        if (bufferContainsAudio) break;
    }

    if (!bufferContainsAudio) {
        return;
    }

    // Parameter Effects
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        std::vector<float> noiseBuffer(buffer.getNumSamples());

        float resampleFactor = juce::jmap(getNoiseTone(), 1.0f, 3.0f);
        std::vector<float> resampledNoise(buffer.getNumSamples());

        // Noise Sample
        if (*noiseBypass != bpVal) {
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
                float noiseSample = 0.0f;
                if (getNoiseType() == 0.0f) {
                    noiseSample = generateWhiteNoise();
                }
                else if (getNoiseType() < 1.0f) {
                    noiseSample = generatePinkNoise();
                }
                else {
                    noiseSample = generateBrownNoise();
                }
                noiseBuffer[sample] = noiseSample;
            }

            // Noise Tone
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
                float resampleIndex = sample / resampleFactor;
                int indexBelow = static_cast<int>(resampleIndex);
                int indexAbove = indexBelow + 1;
                float fractionAbove = resampleIndex - indexBelow;

                if (indexBelow >= 0 && indexAbove < buffer.getNumSamples()) {
                    resampledNoise[sample] = noiseBuffer[indexBelow] * (1.0f - fractionAbove) + noiseBuffer[indexAbove] * fractionAbove;
                }
                else if (indexBelow >= 0) {
                    resampledNoise[sample] = noiseBuffer[indexBelow];
                }
                else {
                    resampledNoise[sample] = 0.0f;
                }
            }
        }


        // Other Parameters
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            if (*noiseBypass != bpVal) {
                // Noise Flux
                float fluxAdjustment = 1.0f + juce::Random::getSystemRandom().nextFloat() * getNoiseFlux() * 0.7f;
                resampledNoise[sample] *= fluxAdjustment;

                // Noise Amplitude
                float noiseAmplitude = getNoiseLevel() * 0.025f;
                channelData[sample] += resampledNoise[sample] * noiseAmplitude;
            }

            // Reduce Bit Depth
            if (*bitDepthBypass != bpVal) {
                if (getBitDepth() < 32.0f) {
                    const float maxVal = std::pow(2.0f, getBitDepth()) - 1.0f;
                    channelData[sample] = std::round(channelData[sample] * maxVal) / maxVal;
                }
            }

            // Crackle
            if (*crackleBypass != bpVal) {
                float crackleProbability = getCrackleLevel() * 0.005f;
                float crackleAmplitude = getCrackleLevel() * 0.05f;

                // Crackle Type
                if (getCrackleType() == 0.0f) {
                    if (juce::Random::getSystemRandom().nextFloat() < crackleProbability * 1.5f) {
                        channelData[sample] += (juce::Random::getSystemRandom().nextFloat() - 0.5f) * 3.0f * crackleAmplitude;
                    }
                }
                else if (getCrackleType() == 1.0f) {
                    if (juce::Random::getSystemRandom().nextFloat() < crackleProbability * 0.33f) {
                        channelData[sample] += (juce::Random::getSystemRandom().nextFloat() - 0.5f) * 5.0f * crackleAmplitude;
                    }
                }
                else if (getCrackleType() == 2.0f) {
                    if (juce::Random::getSystemRandom().nextFloat() < crackleProbability * 7.0f) {
                        channelData[sample] += (juce::Random::getSystemRandom().nextFloat() - 0.5f) * 2.5f * crackleAmplitude;
                    }
                }
            }

            if (*wowFlutterBypass != bpVal) {
                // Wow / Flutter
                float depth = getWowFlutterStrength() * 0.2f;
                float speed = getWowFlutterSpeed() * 1.2f;
                float wowFlutter = std::sin(2.0f * juce::MathConstants<float>::pi * sample / (buffer.getNumSamples() / (speed * 10.0f + 1.0f)));
                channelData[sample] *= 1.25f + wowFlutter * depth * getWowFlutterIntensity();
            }

            // Distortion
            if (*distortionBypass != bpVal) {
                if (getDistortionLevel() > 0.0f) {
                    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
                        float input = channelData[sample];
                        float distortedSample = 0.0f;
                        auto distortionLevel = -1 * (getDistortionLevel() - 1);
                        distortedSample = std::tanh(distortionLevel * input);

                        float tone = getDistortionTone();
                        distortedSample = distortedSample * tone + input * (1.0f - tone);

                        float mix = getDistortionMix();
                        channelData[sample] = input * (1.0f - mix) + distortedSample * mix;
                    }
                }
            }
        }

        // Sample Rate Reduction
        if (*bitDepthBypass != bpVal) {
            if (getSampleRateReduction() < 44100.0f) {
                const int reductionFactor = static_cast<int>(getSampleRate() / getSampleRateReduction());
                for (int sample = 0; sample < buffer.getNumSamples(); sample += reductionFactor) {
                    const float reducedSample = channelData[sample];
                    for (int k = 1; k < reductionFactor; ++k) {
                        if (sample + k < buffer.getNumSamples()) {
                            channelData[sample + k] = reducedSample;
                        }
                    }
                }
            }
        }
    }

    if (*filterBypass != bpVal) {
        updateFilters(buffer);
    }
}

float SimpleLofiFilterAudioProcessor::generateWhiteNoise() {
    return juce::Random::getSystemRandom().nextFloat() * 2.0f - 1.0f;
}

float SimpleLofiFilterAudioProcessor::generatePinkNoise() {
    static float pinkNoise[7] = { 0.0f };
    const float white = generateWhiteNoise();

    pinkNoise[0] = 0.99765f * pinkNoise[0] + white * 0.0990460f;
    pinkNoise[1] = 0.96300f * pinkNoise[1] + white * 0.2965164f;
    pinkNoise[2] = 0.57000f * pinkNoise[2] + white * 1.0526913f;

    const float pink = pinkNoise[0] + pinkNoise[1] + pinkNoise[2] + white * 0.1848f;
    return pink * 0.05f;
}

float SimpleLofiFilterAudioProcessor::generateBrownNoise() {
    static float lastBrown = 0.0f;
    const float white = generateWhiteNoise();
    lastBrown = (lastBrown + (0.02f * white)) / 1.02f;
    return lastBrown * 3.5f;
}

void SimpleLofiFilterAudioProcessor::updateFilters(juce::AudioBuffer<float>& buffer) {
    // Low Cut Filter
    *lowCutFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), getLowCutFreq());
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    lowCutFilter.process(context);

    // High Cut Filter
    *highCutFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), getHighCutFreq());
    highCutFilter.process(context);
}

//==============================================================================
bool SimpleLofiFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleLofiFilterAudioProcessor::createEditor()
{
    return new SimpleLofiFilterAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleLofiFilterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    juce::MemoryOutputStream mos(destData, true);
    parameters.state.writeToStream(mos);
}

void SimpleLofiFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) {
        parameters.replaceState(tree);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleLofiFilterAudioProcessor();
}
