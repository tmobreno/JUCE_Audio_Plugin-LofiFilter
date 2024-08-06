/*
  ==============================================================================

    FilterComponent.h
    Created: 10 Jul 2024 10:35:26pm
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
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(SimpleLofiFilterAudioProcessor& p);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SliderSetup mSliderSetup;
    SimpleLofiFilterAudioProcessor& audioProcessor;

    CustomSlider lowCutSlider, highCutSlider;

    juce::Label titleLabel, lowCutLabel, highCutLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        lowCutAttachment, highCutAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    juce::TextButton bypassButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
