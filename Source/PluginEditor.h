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

class Analyzer : public Component
{
public:
    TextButton loadButton;
    
    Analyzer(ApresMidiAudioProcessor * proc)
    {
        processor = proc;
        addAndMakeVisible(loadButton);
        loadButton.setButtonText("Choose file...");
        loadButton.onClick = [this]
        {
            FileChooser chooser ("Load a MIDI file",
                                 {},
                                 "*.mid");
            if (chooser.browseForFileToOpen())
            {
                File file = chooser.getResult();
                
                processor->m1.is_ready = 0;
                processor->m1.reset();
                processor->m1.read_midi_file((const char *)file.getFullPathName().toUTF8());
                processor->m1.is_ready = 1;
            }
        };
    }
    
    void paint (Graphics& g) override
    {
        Path p1;
        float offset=0.01;
        float rounding=10;
        
        p1.addRoundedRectangle(offset*getWidth(),offset*getHeight(),(1-2*offset)*getWidth(),(1-2*offset)*getHeight(),rounding);
        
        g.setColour(Colours::darkblue);
        g.fillPath(p1);
        loadButton.setBounds(0,0,getWidth(),getHeight());
        
    };
private:
    ApresMidiAudioProcessor* processor;
    
};

class FileComp : public Component
{
public:
    TextButton loadButton;
    
    FileComp(ApresMidiAudioProcessor * proc)
    {
        processor = proc;
        addAndMakeVisible(loadButton);
        loadButton.setButtonText("Choose file...");
        loadButton.onClick = [this]
        {
            FileChooser chooser ("Load a MIDI file",
                                 {},
                                 "*.mid");
            if (chooser.browseForFileToOpen())
            {
                File file = chooser.getResult();
                
                processor->m1.is_ready = 0;
                processor->m1.reset();
                processor->m1.read_midi_file((const char *)file.getFullPathName().toUTF8());
                processor->m1.is_ready = 1;
            }
        };
    }
    
    void paint (Graphics& g) override
    {
        Path p1;
        float offset=0.01;
        float rounding=10;
        
        p1.addRoundedRectangle(offset*getWidth(),offset*getHeight(),(1-2*offset)*getWidth(),(1-2*offset)*getHeight(),rounding);
        
        g.setColour(Colours::darkblue);
        g.fillPath(p1);
        loadButton.setBounds(0,0,getWidth(),0.2*getHeight());
        
    };
private:
    ApresMidiAudioProcessor* processor;
    
};


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
        Path p1;
        float offset=0.01;
        float rounding=10;
        
        p1.addRoundedRectangle(offset*getWidth(),offset*getHeight(),(1-2*offset)*getWidth(),(1-2*offset)*getHeight(),rounding);
        
        g.setColour(Colours::darkblue);
        g.fillPath(p1);
        addAndMakeVisible(speed_slider);
        speed_slider.setBounds(4*offset*getWidth(),offset*getHeight(),(1-2*4*offset)*getWidth(),(1-2*offset)*getHeight());
    };
private:
    ApresMidiAudioProcessor* processor;

};


class GenerateMarkov : public Component
{
public:
    Slider speed_slider;
    GenerateMarkov(ApresMidiAudioProcessor * proc) : processor(proc)
    {
        //processor = proc; // This is the same as the initializer above
    }
    
    void paint (Graphics& g) override
    {
        Path p1;
        float offset=0.01;
        float rounding=10;
        
        p1.addRoundedRectangle(offset*getWidth(),offset*getHeight(),(1-2*offset)*getWidth(),(1-2*offset)*getHeight(),rounding);
        
        g.setColour(Colours::darkblue);
        g.fillPath(p1);
        addAndMakeVisible(speed_slider);
        speed_slider.setBounds(4*offset*getWidth(),offset*getHeight(),(1-2*4*offset)*getWidth(),(1-2*offset)*getHeight());
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
        addAndMakeVisible(speed_slider);
    }
    
    void paint (Graphics& g) override
    {
        
        
        Path p1;
        float offset=0.01;
        float rounding=10;
        
        p1.addRoundedRectangle(offset*getWidth(),offset*getHeight(),(1-2*offset)*getWidth(),(1-2*offset)*getHeight(),rounding);
        
        g.setColour(Colours::darkblue);
        g.fillPath(p1);
        speed_slider.setBounds(4*offset*getWidth(),offset*getHeight(),(1-2*4*offset)*getWidth(),(1-2*offset)*getHeight());
        g.setColour(Colours::white);
        
        g.drawFittedText("Duration Multiplier (Inverse Speed)", offset*getWidth(), 0.20*getHeight(), (1-2*offset)*getWidth(), getHeight() , Justification::centredTop, 1);
        
        
        
        
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

