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

class PianoRoll : public Component
{
public:
    Slider speed_slider;
    PianoRoll(ApresMidiAudioProcessor * proc)
    {
        processor = proc;
    }
    
    void paint (Graphics& g) override
    {
        g.fillAll(Colours::lightskyblue);
        addAndMakeVisible(speed_slider);
        speed_slider.setBounds(0,0,getWidth(),getHeight());
    };
private:
    ApresMidiAudioProcessor* processor;

};


class GenerateMarkov : public Component
{
public:
    Slider speed_slider;
    GenerateMarkov(ApresMidiAudioProcessor * proc)
    {
        processor = proc;
    }
    
    void paint (Graphics& g) override
    {
        g.fillAll(Colours::darkkhaki);
        addAndMakeVisible(speed_slider);
        speed_slider.setBounds(0,0,getWidth(),getHeight());
    };
    
private:
        ApresMidiAudioProcessor* processor;
};


class PlayingComponent : public Component
{
public:
    Slider speed_slider;
    PlayingComponent(ApresMidiAudioProcessor * proc)
    {
        processor = proc;
        addAndMakeVisible(speed_slider);
        speed_slider.setRange(1, 1000, 1);
        speed_slider.setValue(processor->m1.speed);
        speed_slider.onValueChange = [this] {processor->m1.speed = speed_slider.getValue(); };
    }
    
    void paint (Graphics& g) override
    {
        g.setColour(Colours::white);
        g.setFont(15.0f);
        g.fillAll(Colours::darkblue);
        
        
        g.drawFittedText("Duration Multiplier (Inverse Speed)", 0, 0.25*getHeight(), getWidth(), getHeight()*0.25, Justification::left, 1);
        
        speed_slider.setBounds(0,0.5*getHeight(),getWidth(),0.25*getHeight());
    };
    
private:
    ApresMidiAudioProcessor* processor;
};


class ApresMidiAudioProcessorEditor  :   public AudioProcessorEditor, public Slider::Listener, public Button::Listener
{
public:
    
    ApresMidiAudioProcessorEditor (ApresMidiAudioProcessor&);
    ~ApresMidiAudioProcessorEditor();

    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
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
    
    // Here we store all the Child Components, which will also handle all the smaller elements
    std::vector<std::unique_ptr<Component>> allComps;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ApresMidiAudioProcessorEditor)
};

