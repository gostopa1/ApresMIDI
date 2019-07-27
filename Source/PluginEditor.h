/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ApresMidiAudioProcessorEditor  :   public AudioProcessorEditor,
                                        public Slider::Listener, public Button::Listener
{
public:
    ApresMidiAudioProcessorEditor (ApresMidiAudioProcessor&);
    ~ApresMidiAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	
	Slider speed_slider;
	Slider order_slider;
    
    TextButton loadButton;
    
	TextEditor order_text;
	Label order_label;


	Label trackno_label;
	Label warning_label;
	
private:
    void sliderValueChanged(Slider* slider) override {};
    virtual void buttonClicked(Button* button) override;
    void loadButtonClicked();
    
	ApresMidiAudioProcessor& processor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ApresMidiAudioProcessorEditor)
};
