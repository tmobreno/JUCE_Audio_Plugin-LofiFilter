/*
  ==============================================================================

    FlutterComponent.h
    Created: 10 Jul 2024 9:32:13pm
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
class FlutterComponent  : public juce::Component
{
public:
    FlutterComponent(SimpleLofiFilterAudioProcessor& p);
    ~FlutterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SliderSetup mSliderSetup;
    SimpleLofiFilterAudioProcessor& audioProcessor;

    CustomSlider intensitySlider, depthSlider, speedSlider;

    juce::Label titleLabel, intensityLabel, depthLabel, speedLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        intensityAttachment, depthAttachment, speedAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    juce::TextButton bypassButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlutterComponent)
};
