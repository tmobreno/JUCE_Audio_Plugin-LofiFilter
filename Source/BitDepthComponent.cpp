/*
  ==============================================================================

    BitDepthComponent.cpp
    Created: 10 Jul 2024 9:54:30pm
    Author:  tmobr

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BitDepthComponent.h"

//==============================================================================
BitDepthComponent::BitDepthComponent(SimpleLofiFilterAudioProcessor& p) : audioProcessor(p)
{
    addAndMakeVisible(mSliderSetup.setUpLabel(titleLabel, "Bit Depth", 22.0f));

    addAndMakeVisible(mSliderSetup.addAndSetupSlider(depthSlider, "Bit Depth", 65.0, 20.0, juce::Slider::TextBoxRight));
    addAndMakeVisible(mSliderSetup.addAndSetupSlider(reductionSlider, "Sample Rate Reduction", 65.0, 20.0, juce::Slider::TextBoxRight));

    depthAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Bit Depth", depthSlider));
    reductionAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Sample Rate Reduction", reductionSlider));
    bypassAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.parameters, "Bit Depth Bypass", bypassButton));

    addAndMakeVisible(mSliderSetup.setUpSmallLabel(depthLabel, "Depth", 15.0f));
    addAndMakeVisible(mSliderSetup.setUpSmallLabel(reductionLabel, "Reduction", 15.0f));

    addAndMakeVisible(mSliderSetup.setUpButton(bypassButton));
    bypassButton.onClick = [this] { repaint(); };
}

BitDepthComponent::~BitDepthComponent()
{
    depthSlider.setLookAndFeel(nullptr);
    reductionSlider.setLookAndFeel(nullptr);
}

void BitDepthComponent::paint (juce::Graphics& g)
{
    if (bypassButton.getToggleState()) g.fillAll(juce::Colours::darkgrey.withAlpha(0.5f));
    if (!bypassButton.getToggleState()) g.fillAll(juce::Colours::lightblue.withAlpha(0.5f));
}

void BitDepthComponent::resized()
{
    titleLabel.setBoundsRelative(0.23f, 0.05f, mSliderSetup.labelW + 0.05f, mSliderSetup.labelH);

    depthSlider.setBoundsRelative(0.2f, 0.1f, mSliderSetup.largeSliderW * 1.5, mSliderSetup.largeSliderH);
    depthLabel.setBoundsRelative(0.2f + 0.42f, 0.1f + 0.08f, mSliderSetup.labelW, mSliderSetup.labelH);

    reductionSlider.setBoundsRelative(0.2f, 0.5f, mSliderSetup.largeSliderW * 1.5, mSliderSetup.largeSliderH);
    reductionLabel.setBoundsRelative(0.2f + 0.42f, 0.5f + 0.08f, mSliderSetup.labelW, mSliderSetup.labelH);

    bypassButton.setBoundsRelative(0.7f, 0.06f, mSliderSetup.buttonW, mSliderSetup.buttonH);
}
