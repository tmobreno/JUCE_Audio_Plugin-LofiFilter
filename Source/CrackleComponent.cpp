/*
  ==============================================================================

    CrackleComponent.cpp
    Created: 10 Jul 2024 9:32:04pm
    Author:  tmobr

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CrackleComponent.h"

//==============================================================================
CrackleComponent::CrackleComponent(SimpleLofiFilterAudioProcessor& p) : audioProcessor(p)
{
    addAndMakeVisible(mSliderSetup.setUpLabel(titleLabel, "Crackle", 22.0f));

    addAndMakeVisible(mSliderSetup.addAndSetupSlider(intensitySlider, "Crackle Level", 50.0, 20.0, juce::Slider::TextBoxBelow));
    addAndMakeVisible(mSliderSetup.addAndSetupSlider(typeSlider, "Crackle Type", 40.0, 20.0, juce::Slider::TextBoxRight));

    intensityAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Crackle Level", intensitySlider));
    typeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parameters, "Crackle Type", typeSlider));
    bypassAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.parameters, "Crackle Bypass", bypassButton));

    addAndMakeVisible(mSliderSetup.setUpSmallLabel(intensityLabel, "Intensity", 18.0f));
    addAndMakeVisible(mSliderSetup.setUpSmallLabel(typeLabel, "Type", 15.0f));

    addAndMakeVisible(mSliderSetup.setUpButton(bypassButton));
    bypassButton.onClick = [this] { repaint(); };
}

CrackleComponent::~CrackleComponent()
{
    intensitySlider.setLookAndFeel(nullptr);
    typeSlider.setLookAndFeel(nullptr);
}

void CrackleComponent::paint (juce::Graphics& g)
{
    if (bypassButton.getToggleState()) g.fillAll(juce::Colours::darkgrey.withAlpha(0.5f));
    if (!bypassButton.getToggleState()) g.fillAll(juce::Colours::lightblue.withAlpha(0.5f));
}

void CrackleComponent::resized()
{
    titleLabel.setBoundsRelative(0.25f, 0.05f, mSliderSetup.labelW, mSliderSetup.labelH);

    intensitySlider.setBoundsRelative(0.05f, 0.3f, mSliderSetup.largeSliderW, mSliderSetup.largeSliderH);
    intensityLabel.setBoundsRelative(0.05f + 0.1f, 0.3f - 0.08f, mSliderSetup.labelW, mSliderSetup.labelH);

    typeSlider.setBoundsRelative(0.55f, 0.7f, mSliderSetup.smallSliderW, mSliderSetup.smallSliderH);
    typeLabel.setBoundsRelative(0.55f + 0.2f, 0.7f - 0.04f, mSliderSetup.labelW, mSliderSetup.labelH);

    bypassButton.setBoundsRelative(0.7f, 0.06f, mSliderSetup.buttonW, mSliderSetup.buttonH);
}
