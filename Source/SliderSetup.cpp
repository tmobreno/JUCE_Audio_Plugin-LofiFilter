/*
  ==============================================================================

    SliderSetup.cpp
    Created: 10 Jul 2024 3:26:44pm
    Author:  tmobr

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SliderSetup.h"

//==============================================================================
SliderSetup::SliderSetup()
{
}

SliderSetup::~SliderSetup()
{
}

juce::Slider& SliderSetup::addAndSetupSlider(juce::Slider& slider,
    const juce::String& name,
    double width,
    double height,
    juce::Slider::TextEntryBoxPosition entry) {

    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::darkgrey);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::darkgrey);
    slider.setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::dodgerblue);
    slider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::lightgrey);

    slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider.setTextBoxStyle(entry, false, width, height);

    slider.setLookAndFeel(&customLookAndFeel);

    return slider;
}

juce::Label& SliderSetup::setUpLabel(juce::Label& label, const juce::String & text, int fontSize) {
    label.setColour(juce::Label::textColourId, juce::Colours::darkgrey);
    label.setText(text, juce::dontSendNotification);
    label.setFont(juce::Font(fontSize));
    label.setJustificationType(juce::Justification::left);
    return label;
}

juce::Label& SliderSetup::setUpSmallLabel(juce::Label& label, const juce::String& text, int fontSize) {
    label.setColour(juce::Label::textColourId, juce::Colours::darkgrey);
    label.setText(text, juce::dontSendNotification);
    label.setFont(juce::Font(fontSize));
    label.setJustificationType(juce::Justification::left);
    return label;
}

juce::Button& SliderSetup::setUpButton(juce::Button& button) {
    button.setClickingTogglesState(true);
    button.setColour(juce::TextButton::buttonOnColourId, juce::Colours::indianred);
    button.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    button.setButtonText("Bypass");
    return button;
}

void SliderSetup::paint (juce::Graphics& g)
{

}

void SliderSetup::resized()
{

}
