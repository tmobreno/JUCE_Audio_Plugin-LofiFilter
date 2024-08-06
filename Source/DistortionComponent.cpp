/*
  ==============================================================================

    DistortionComponent.cpp
    Created: 10 Jul 2024 10:35:17pm
    Author:  tmobr

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionComponent.h"

//==============================================================================
DistortionComponent::DistortionComponent(SimpleLofiFilterAudioProcessor& p) : audioProcessor(p)
{
    addAndMakeVisible(mSliderSetup.setUpLabel(titleLabel, "Distortion", 22.0f));

    addAndMakeVisible(mSliderSetup.addAndSetupSlider(intensitySlider, "Distortion Intensity", 50.0, 20.0, juce::Slider::TextBoxBelow));
    addAndMakeVisible(mSliderSetup.addAndSetupSlider(toneSlider, "Distortion Tone", 40.0, 20.0, juce::Slider::TextBoxRight));
    addAndMakeVisible(mSliderSetup.addAndSetupSlider(mixSlider, "Distortion Mix", 40.0, 20.0, juce::Slider::TextBoxRight));

    intensityAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Distortion Level", intensitySlider));
    toneAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Distortion Tone", toneSlider));
    mixAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Distortion Mix", mixSlider));
    bypassAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.parameters, "Distortion Bypass", bypassButton));

    addAndMakeVisible(mSliderSetup.setUpSmallLabel(intensityLabel, "Intensity", 18.0f));
    addAndMakeVisible(mSliderSetup.setUpSmallLabel(toneLabel, "Tone", 15.0f));
    addAndMakeVisible(mSliderSetup.setUpSmallLabel(mixLabel, "Mix", 15.0f));

    addAndMakeVisible(mSliderSetup.setUpButton(bypassButton));
    bypassButton.onClick = [this] { repaint(); };
}

DistortionComponent::~DistortionComponent()
{
    intensitySlider.setLookAndFeel(nullptr);
    toneSlider.setLookAndFeel(nullptr);
    mixSlider.setLookAndFeel(nullptr);
}

void DistortionComponent::paint (juce::Graphics& g)
{
    if (bypassButton.getToggleState()) g.fillAll(juce::Colours::darkgrey.withAlpha(0.5f));
    if (!bypassButton.getToggleState()) g.fillAll(juce::Colours::lightblue.withAlpha(0.5f));
}

void DistortionComponent::resized()
{
    titleLabel.setBoundsRelative(0.2f, 0.05f, mSliderSetup.labelW + 0.08, mSliderSetup.labelH);

    intensitySlider.setBoundsRelative(0.05f, 0.3f, mSliderSetup.largeSliderW, mSliderSetup.largeSliderH);
    intensityLabel.setBoundsRelative(0.05f + 0.1f, 0.3f - 0.08f, mSliderSetup.labelW, mSliderSetup.labelH);

    toneSlider.setBoundsRelative(0.55f, 0.3f, mSliderSetup.smallSliderW, mSliderSetup.smallSliderH);
    toneLabel.setBoundsRelative(0.55f + 0.2f, 0.3f - 0.04f, mSliderSetup.labelW, mSliderSetup.labelH);

    mixSlider.setBoundsRelative(0.55f, 0.6f, mSliderSetup.smallSliderW, mSliderSetup.smallSliderH);
    mixLabel.setBoundsRelative(0.55f + 0.2f, 0.6f - 0.04f, mSliderSetup.labelW, mSliderSetup.labelH);

    bypassButton.setBoundsRelative(0.7f, 0.06f, mSliderSetup.buttonW, mSliderSetup.buttonH);
}
