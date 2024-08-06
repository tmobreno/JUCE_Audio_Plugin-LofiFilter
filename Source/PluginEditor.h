/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "NoiseComponent.h"
#include "CrackleComponent.h"
#include "FlutterComponent.h"
#include "BitDepthComponent.h"
#include "DistortionComponent.h"
#include "FilterComponent.h"

//==============================================================================
/**
*/
class SimpleLofiFilterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleLofiFilterAudioProcessorEditor (SimpleLofiFilterAudioProcessor&);
    ~SimpleLofiFilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleLofiFilterAudioProcessor& audioProcessor;

    NoiseComponent mNoiseComponent;
    CrackleComponent mCrackleComponent;
    FlutterComponent mFlutterComponent;
    BitDepthComponent mBitDepthComponent;
    DistortionComponent mDistortionComponent;
    FilterComponent mFilterComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleLofiFilterAudioProcessorEditor)
};
