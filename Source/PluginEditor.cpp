/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ApresMidiAudioProcessorEditor::ApresMidiAudioProcessorEditor(ApresMidiAudioProcessor& p)
: AudioProcessorEditor(&p), processor(p)
{
    allComps.emplace_back(new PlayingComponent(&processor));
    allComps.emplace_back(new Analyzer(&processor));
    
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("Load MIDI File");
    loadButton.onClick=[this]
    {
        FileChooser chooser ("Load a MIDI file",
                             {},
                             "*.mid");
        if (chooser.browseForFileToOpen())
        {
            File file = chooser.getResult();
            
            //processor.m1.is_ready = 0;
            //processor.m1.reset();
            processor.m1.analyze_file((const char *)file.getFullPathName().toUTF8());
            track_menu.clear();
            for (int track_i=0;track_i<processor.m1.notes_per_track.size();++track_i)
            {
                if (processor.m1.notes_per_track[track_i]>0)
                {
                    //track_menu.addItem((String)processor.m1.notes_per_track[track_i], track_i+1);
                    track_menu.addItem("Track "+(String)track_i+": "+(String)processor.m1.notes_per_track[track_i]+" events", track_i+1);
                }
            }
            //processor.m1.is_ready = 1;
        }
        
    };
    loadButton.setBounds(10, 10, 200, 30);
    
    addAndMakeVisible(warning_label);
    warning_label.setBounds(10, 200, 380, 10);
    warning_label.setJustificationType(juce::Justification::left);
    
    addAndMakeVisible(*allComps[0]); // Speed slider
    allComps[0]->setBounds(10,300,200,100);
    
    addAndMakeVisible(*allComps[1]);
    allComps[1]->setBounds(10,200,200,30);
    
    addAndMakeVisible(track_menu);
    track_menu.addItem("Load a midi file first",2);
    track_menu.setBounds(10,100,200,30);
    track_menu.onChange=[this]
    {
        DBG((String)track_menu.getSelectedId());
        processor.m1.trackno=(track_menu.getSelectedId()-1);
    };
    
    
    addAndMakeVisible(order_menu);
    for (int order_i=1;order_i<11;++order_i)
    {
    order_menu.addItem((String)order_i,order_i);
    }
    order_menu.setBounds(220,100,200,30);
    order_menu.onChange=[this]
    {
        DBG((String)order_menu.getSelectedId());
        processor.m1.order=order_menu.getSelectedId();
    };
    setSize(500, 500);
}

ApresMidiAudioProcessorEditor::~ApresMidiAudioProcessorEditor()
{
    /*
    switch (styleMenu.getSelectedId())
    {
    }
    textLabel.setFont (textFont);
     */
}

//==============================================================================
void ApresMidiAudioProcessorEditor::paint(Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    
    g.setColour(Colours::white);
    g.setFont(15.0f);
    
    g.drawFittedText("Track",10,70,200,30,Justification::centred,1);
    g.drawFittedText("Order",220,70,200,30,Justification::centred,1);
    g.drawFittedText("by Athanasios Gotsopoulos (c) 2019",250,480,250,20,Justification::centredRight,1);
}

void ApresMidiAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
