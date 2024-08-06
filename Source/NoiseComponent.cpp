/*
  ==============================================================================

    NoiseComponent.cpp
    Created: 10 Jul 2024 2:42:01pm
    Author:  tmobr

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NoiseComponent.h"

//==============================================================================
NoiseComponent::NoiseComponent(SimpleLofiFilterAudioProcessor& p) : audioProcessor(p)
{
    addAndMakeVisible(mSliderSetup.setUpLabel(titleLabel, "Noise", 22.0f));

    addAndMakeVisible(mSliderSetup.addAndSetupSlider(intensitySlider, "Noise Level", 50.0, 20.0, juce::Slider::TextBoxBelow));
    addAndMakeVisible(mSliderSetup.addAndSetupSlider(toneSlider, "Noise Tone", 40.0, 20.0, juce::Slider::TextBoxRight));
    addAndMakeVisible(mSliderSetup.addAndSetupSlider(fluxSlider, "Noise Flux", 40.0, 20.0, juce::Slider::TextBoxRight));
    addAndMakeVisible(mSliderSetup.addAndSetupSlider(typeSlider, "Noise Type", 40.0, 20.0, juce::Slider::TextBoxRight));

    intensityAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Noise Level", intensitySlider));
    toneAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Noise Tone", toneSlider));
    fluxAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Noise Flux", fluxSlider));
    typeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Noise Type", typeSlider));
    bypassAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.parameters, "Noise Bypass", bypassButton));

    addAndMakeVisible(mSliderSetup.setUpSmallLabel(intensityLabel, "Intensity", 18.0f));
    addAndMakeVisible(mSliderSetup.setUpSmallLabel(toneLabel, "Tone", 15.0f));
    addAndMakeVisible(mSliderSetup.setUpSmallLabel(fluxLabel, "Flux", 15.0f));
    addAndMakeVisible(mSliderSetup.setUpSmallLabel(typeLabel, "Type", 15.0f));

    addAndMakeVisible(mSliderSetup.setUpButton(bypassButton));
    bypassButton.onClick = [this] { repaint(); };
}

NoiseComponent::~NoiseComponent()
{
    intensitySlider.setLookAndFeel(nullptr);
    toneSlider.setLookAndFeel(nullptr);
    fluxSlider.setLookAndFeel(nullptr);
    typeSlider.setLookAndFeel(nullptr);
}

void NoiseComponent::paint (juce::Graphics& g)
{
    if (bypassButton.getToggleState()) g.fillAll(juce::Colours::darkgrey.withAlpha(0.5f));
    if (!bypassButton.getToggleState()) g.fillAll(juce::Colours::lightblue.withAlpha(0.5f));
}

void NoiseComponent::resized()
{
    titleLabel.setBoundsRelative(0.25f, 0.05f, mSliderSetup.labelW, mSliderSetup.labelH);

    intensitySlider.setBoundsRelative(0.05f, 0.3f, mSliderSetup.largeSliderW, mSliderSetup.largeSliderH);
    intensityLabel.setBoundsRelative(0.05f + 0.1f, 0.3f - 0.08f, mSliderSetup.labelW, mSliderSetup.labelH);

    toneSlider.setBoundsRelative(0.55f, 0.2f, mSliderSetup.smallSliderW, mSliderSetup.smallSliderH);
    toneLabel.setBoundsRelative(0.55f + 0.2f, 0.2f - 0.04f, mSliderSetup.labelW, mSliderSetup.labelH);

    fluxSlider.setBoundsRelative(0.55f, 0.45f, mSliderSetup.smallSliderW, mSliderSetup.smallSliderH);
    fluxLabel.setBoundsRelative(0.55f + 0.2f, 0.45f - 0.04f, mSliderSetup.labelW, mSliderSetup.labelH);

    typeSlider.setBoundsRelative(0.55f, 0.7f, mSliderSetup.smallSliderW, mSliderSetup.smallSliderH);
    typeLabel.setBoundsRelative(0.55f + 0.2f, 0.7f - 0.04f, mSliderSetup.labelW, mSliderSetup.labelH);

    bypassButton.setBoundsRelative(0.7f, 0.06f, mSliderSetup.buttonW, mSliderSetup.buttonH);
}
