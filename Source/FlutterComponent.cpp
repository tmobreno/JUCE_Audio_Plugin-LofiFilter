/*
  ==============================================================================

    FlutterComponent.cpp
    Created: 10 Jul 2024 9:32:13pm
    Author:  tmobr

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FlutterComponent.h"

//==============================================================================
FlutterComponent::FlutterComponent(SimpleLofiFilterAudioProcessor& p) : audioProcessor(p)
{
    addAndMakeVisible(mSliderSetup.setUpLabel(titleLabel, "Flutter", 22.0f));

    addAndMakeVisible(mSliderSetup.addAndSetupSlider(intensitySlider, "Flutter Intensity", 50.0, 20.0, juce::Slider::TextBoxBelow));
    addAndMakeVisible(mSliderSetup.addAndSetupSlider(depthSlider, "Flutter Strength", 40.0, 20.0, juce::Slider::TextBoxRight));
    addAndMakeVisible(mSliderSetup.addAndSetupSlider(speedSlider, "Flutter Speed", 40.0, 20.0, juce::Slider::TextBoxRight));

    intensityAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Flutter Intensity", intensitySlider));
    depthAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Flutter Strength", depthSlider));
    speedAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Flutter Speed", speedSlider));
    bypassAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.parameters, "Wow Flutter Bypass", bypassButton));

    addAndMakeVisible(mSliderSetup.setUpSmallLabel(intensityLabel, "Intensity", 18.0f));
    addAndMakeVisible(mSliderSetup.setUpSmallLabel(depthLabel, "Depth", 15.0f));
    addAndMakeVisible(mSliderSetup.setUpSmallLabel(speedLabel, "Speed", 15.0f));

    addAndMakeVisible(mSliderSetup.setUpButton(bypassButton));
    bypassButton.onClick = [this] { repaint(); };
}

FlutterComponent::~FlutterComponent()
{
    intensitySlider.setLookAndFeel(nullptr);
    depthSlider.setLookAndFeel(nullptr);
    speedSlider.setLookAndFeel(nullptr);
}

void FlutterComponent::paint (juce::Graphics& g)
{
    if (bypassButton.getToggleState()) g.fillAll(juce::Colours::darkgrey.withAlpha(0.5f));
    if (!bypassButton.getToggleState()) g.fillAll(juce::Colours::lightblue.withAlpha(0.5f));
}

void FlutterComponent::resized()
{
    titleLabel.setBoundsRelative(0.25f, 0.05f, mSliderSetup.labelW, mSliderSetup.labelH);

    intensitySlider.setBoundsRelative(0.05f, 0.3f, mSliderSetup.largeSliderW, mSliderSetup.largeSliderH);
    intensityLabel.setBoundsRelative(0.05f + 0.1f, 0.3f - 0.08f, mSliderSetup.labelW, mSliderSetup.labelH);

    depthSlider.setBoundsRelative(0.55f, 0.3f, mSliderSetup.smallSliderW, mSliderSetup.smallSliderH);
    depthLabel.setBoundsRelative(0.55f + 0.2f, 0.3f - 0.04f, mSliderSetup.labelW, mSliderSetup.labelH);

    speedSlider.setBoundsRelative(0.55f, 0.6f, mSliderSetup.smallSliderW, mSliderSetup.smallSliderH);
    speedLabel.setBoundsRelative(0.55f + 0.2f, 0.6f - 0.04f, mSliderSetup.labelW, mSliderSetup.labelH);

    bypassButton.setBoundsRelative(0.7f, 0.06f, mSliderSetup.buttonW, mSliderSetup.buttonH);
}
