/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleLofiFilterAudioProcessorEditor::SimpleLofiFilterAudioProcessorEditor (SimpleLofiFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mNoiseComponent(p), mCrackleComponent(p), mFlutterComponent(p), mBitDepthComponent(p), mDistortionComponent(p), mFilterComponent(p)
{
    addAndMakeVisible(mNoiseComponent);
    addAndMakeVisible(mCrackleComponent);
    addAndMakeVisible(mFlutterComponent);
    addAndMakeVisible(mBitDepthComponent);
    addAndMakeVisible(mDistortionComponent);
    addAndMakeVisible(mFilterComponent);

    setSize (800, 600);
}

SimpleLofiFilterAudioProcessorEditor::~SimpleLofiFilterAudioProcessorEditor()
{
}

//==============================================================================
void SimpleLofiFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightblue);
}

void SimpleLofiFilterAudioProcessorEditor::resized()
{
    mNoiseComponent.setBoundsRelative(0.0f, 0.0f, 0.34f, 0.5f);
    mCrackleComponent.setBoundsRelative(0.34f, 0.0f, 0.33f, 0.5f);
    mFlutterComponent.setBoundsRelative(0.67f, 0.0f, 0.33f, 0.5f);
    mBitDepthComponent.setBoundsRelative(0.0f, 0.5f, 0.34f, 0.5f);
    mDistortionComponent.setBoundsRelative(0.34f, 0.5f, 0.33f, 0.5f);
    mFilterComponent.setBoundsRelative(0.67f, 0.5f, 0.33f, 0.5f);
}
