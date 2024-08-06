/*
  ==============================================================================

    FilterComponent.cpp
    Created: 10 Jul 2024 10:35:26pm
    Author:  tmobr

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(SimpleLofiFilterAudioProcessor& p) : audioProcessor(p)
{
    addAndMakeVisible(mSliderSetup.setUpLabel(titleLabel, "Filter", 22.0f));

    addAndMakeVisible(mSliderSetup.addAndSetupSlider(lowCutSlider, "Bit Depth", 65.0, 20.0, juce::Slider::TextBoxBelow));
    addAndMakeVisible(mSliderSetup.addAndSetupSlider(highCutSlider, "Sample Rate Reduction", 65.0, 20.0, juce::Slider::TextBoxBelow));

    lowCutAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Low Cut Freq", lowCutSlider));
    highCutAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "High Cut Freq", highCutSlider));
    bypassAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.parameters, "Filter Bypass", bypassButton));

    addAndMakeVisible(mSliderSetup.setUpSmallLabel(lowCutLabel, "Low Cut", 15.0f));
    addAndMakeVisible(mSliderSetup.setUpSmallLabel(highCutLabel, "High Cut", 15.0f));

    addAndMakeVisible(mSliderSetup.setUpButton(bypassButton));
    bypassButton.onClick = [this] { repaint(); };
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    if (bypassButton.getToggleState()) g.fillAll(juce::Colours::darkgrey.withAlpha(0.5f));
    if (!bypassButton.getToggleState()) g.fillAll(juce::Colours::lightblue.withAlpha(0.5f));
}

void FilterComponent::resized()
{
    titleLabel.setBoundsRelative(0.23f, 0.05f, mSliderSetup.labelW + 0.05f, mSliderSetup.labelH);

    lowCutSlider.setBoundsRelative(0.1f, 0.28f, mSliderSetup.largeSliderW, mSliderSetup.largeSliderH);
    lowCutLabel.setBoundsRelative(0.1f + 0.12f, 0.28f - 0.08f, mSliderSetup.labelW, mSliderSetup.labelH);

    highCutSlider.setBoundsRelative(0.5f, 0.28f, mSliderSetup.largeSliderW, mSliderSetup.largeSliderH);
    highCutLabel.setBoundsRelative(0.5f + 0.12f, 0.28f - 0.08f, mSliderSetup.labelW, mSliderSetup.labelH);

    bypassButton.setBoundsRelative(0.7f, 0.06f, mSliderSetup.buttonW, mSliderSetup.buttonH);
}
