/*
  ==============================================================================

    BitDepthComponent.h
    Created: 10 Jul 2024 9:54:30pm
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
class BitDepthComponent  : public juce::Component
{
public:
    BitDepthComponent(SimpleLofiFilterAudioProcessor& p);
    ~BitDepthComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SliderSetup mSliderSetup;
    SimpleLofiFilterAudioProcessor& audioProcessor;

    CustomSlider depthSlider, reductionSlider;

    juce::Label titleLabel, depthLabel, reductionLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        depthAttachment, reductionAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    juce::TextButton bypassButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitDepthComponent)
};
