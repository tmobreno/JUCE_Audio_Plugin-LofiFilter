/*
  ==============================================================================

    CrackleComponent.h
    Created: 10 Jul 2024 9:32:04pm
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
class CrackleComponent  : public juce::Component
{
public:
    CrackleComponent(SimpleLofiFilterAudioProcessor& p);
    ~CrackleComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SliderSetup mSliderSetup;
    SimpleLofiFilterAudioProcessor& audioProcessor;
    
    CustomSlider intensitySlider, typeSlider;
    juce::Label titleLabel, intensityLabel, typeLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        intensityAttachment, typeAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    juce::TextButton bypassButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrackleComponent)
};
