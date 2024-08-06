/*
  ==============================================================================

    NoiseComponent.h
    Created: 10 Jul 2024 2:42:01pm
    Author:  tmobr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SliderSetup.h"

//==============================================================================
/*
*/
class NoiseComponent  : public juce::Component
{
public:
    NoiseComponent(SimpleLofiFilterAudioProcessor& p);
    ~NoiseComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SliderSetup mSliderSetup;
    CustomSlider intensitySlider, toneSlider, fluxSlider, typeSlider;

    juce::Label titleLabel, intensityLabel, toneLabel, fluxLabel, typeLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        intensityAttachment, toneAttachment, fluxAttachment, typeAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    juce::TextButton bypassButton;

    SimpleLofiFilterAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseComponent)
};
