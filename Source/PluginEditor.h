/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Components.h"
//==============================================================================
/**
*/


class ApresMidiAudioProcessorEditor  :   public AudioProcessorEditor, public Slider::Listener
{
public:
    
    ApresMidiAudioProcessorEditor (ApresMidiAudioProcessor&);
    ~ApresMidiAudioProcessorEditor();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    TextButton loadButton;
	TextEditor order_text;
	
	Label warning_label;
	ComboBox track_menu;
    ComboBox order_menu;
	
private:
    void sliderValueChanged(Slider* slider) override {};
    void loadButtonClicked();
    
	ApresMidiAudioProcessor& processor;
    
    // Here we store all the Child Components, which will also handle all the smaller elements
    std::vector<std::unique_ptr<Component>> allComps;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ApresMidiAudioProcessorEditor)
};

