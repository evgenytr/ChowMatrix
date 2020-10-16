#pragma once

#include <JuceHeader.h>

class ParamSlider : public Component,
                    private AudioProcessorParameter::Listener
{
public:
    ParamSlider (AudioParameterFloat* param);
    ~ParamSlider();

    void parameterValueChanged (int, float newVal) override;
    void parameterGestureChanged (int, bool) override {}

    void resized() override;

private:
    AudioParameterFloat* param;
    Label nameLabel;
    Label valueLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParamSlider)
};