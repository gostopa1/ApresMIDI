/*
  ==============================================================================

    Components.h
    Created: 6 Oct 2019 1:42:46pm
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once



class Analyzer : public Component
{
public:
    TextButton loadButton;
    
    Analyzer(ApresMidiAudioProcessor * proc)
    {
        processor = proc;
        addAndMakeVisible(loadButton);
        loadButton.setButtonText("Analyze track");
        loadButton.onClick = [this]
        {
            processor->m1.is_ready = 0;
            processor->m1.reset();
            processor->m1.analyze_track();
            processor->m1.is_ready = 1;
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
                processor->m1.analyze_file((const char *)file.getFullPathName().toUTF8());
                processor->m1.analyze_track();
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
        
        g.drawFittedText("Duration", offset*getWidth(), 0.20*getHeight(), (1-2*offset)*getWidth(), getHeight() , Justification::centredTop, 1);   
    };
    
private:
    ApresMidiAudioProcessor* processor;
};
