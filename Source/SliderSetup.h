/*
  ==============================================================================

    SliderSetup.h
    Created: 10 Jul 2024 3:26:44pm
    Author:  tmobr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomSlider : public juce::Slider
{
public:
    CustomSlider() : juce::Slider() {}

    void mouseDown(const juce::MouseEvent& event) override
    {
        originalMousePosition = event.source.getScreenPosition();
        setMouseCursor(juce::MouseCursor::NoCursor);
        juce::Slider::mouseDown(event);
    }

    void mouseUp(const juce::MouseEvent& event) override
    {
        juce::Slider::mouseUp(event);
        setMouseCursor(juce::MouseCursor::NormalCursor);
        juce::Desktop::getInstance().getMainMouseSource().setScreenPosition(originalMousePosition);
    }

private:
    juce::Point<float> originalMousePosition;
};

class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
        juce::Slider&) override
    {
        auto radius = ((float)juce::jmin(width / 2, height / 2) - 4.0f) / 1.4;
        auto centreX = (float)x + (float)width * 0.5f;
        auto centreY = (float)y + (float)height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

        // Visual Shading (TRY A GRADIENT)
        float change = 0;
        float scale = 1.2;
        if (radius > 20) {
            change = 3;
            scale = 1.2;
        }

        g.setColour(juce::Colours::darkgrey);
        g.fillEllipse(rx - change, ry - change, rw * scale, rw * scale);

        // Fill background with desired color
        g.setColour(juce::Colours::grey);
        g.fillEllipse(rx, ry, rw, rw);

        // Draw outline
        //g.setColour(juce::Colours::lightgrey);
        //g.drawEllipse(rx, ry, rw, rw, 2.0f);

        // Draw rotary thumb
        juce::Path p;
        auto pointerLength = radius * 0.6f;
        auto pointerThickness = 5.0f;
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

        // Fill rotary thumb with desired color
        g.setColour(juce::Colours::lightgrey);
        g.fillPath(p);
    }
};

//==============================================================================
/*
*/
class SliderSetup  : public juce::Component
{
public:
    SliderSetup();
    ~SliderSetup() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::Slider& addAndSetupSlider(juce::Slider& slider,
        const juce::String& name,
        double width,
        double height,
        juce::Slider::TextEntryBoxPosition entry);

    juce::Label& setUpLabel(juce::Label& label, const juce::String& text, int fontSize);
    juce::Label& setUpSmallLabel(juce::Label& label, const juce::String& text, int fontSize);

    juce::Button& setUpButton(juce::Button& button);

    float labelW = 0.3f;
    float labelH = 0.1f;

    float buttonW = 0.25f;
    float buttonH = 0.075f;

    float largeSliderW = 0.46f;
    float largeSliderH = 0.46f;

    float smallSliderW = 0.38f;
    float smallSliderH = 0.2f;

private:
    CustomLookAndFeel customLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderSetup)
};
