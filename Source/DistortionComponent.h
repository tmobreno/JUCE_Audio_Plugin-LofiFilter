/*
  ==============================================================================

    DistortionComponent.h
    Created: 10 Jul 2024 10:35:17pm
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
class DistortionComponent  : public juce::Component
{
public:
    DistortionComponent(SimpleLofiFilterAudioProcessor& p);
    ~DistortionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SliderSetup mSliderSetup;
    SimpleLofiFilterAudioProcessor& audioProcessor;

    CustomSlider intensitySlider, toneSlider, mixSlider;

    juce::Label titleLabel, intensityLabel, toneLabel, mixLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        intensityAttachment, toneAttachment, mixAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    juce::TextButton bypassButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};
