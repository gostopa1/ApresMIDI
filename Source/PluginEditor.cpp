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
    allComps.emplace_back(new PianoRoll(&processor));
    allComps.emplace_back(new GenerateMarkov(&processor));
    allComps.emplace_back(new PlayingComponent(&processor));
    allComps.emplace_back(new FileComp(&processor));
    allComps.emplace_back(new Analyzer(&processor));
    
    
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("Load MIDI File");
    loadButton.addListener(this);
    loadButton.setBounds(10, 10, 200, 20);
    
	order_label.setBounds(200, 150, 200, 20);
	order_label.setText(" (default is 2 ho)", juce::NotificationType::sendNotification);
	order_label.setEditable(1, false, 0);
	order_label.onTextChange = [this]
	{
		auto temp = order_label.getTextValue();
		processor.m1.next_order = (int)temp.getValue();
	};
	addAndMakeVisible(order_label);

	trackno_label.setBounds(200, 170, 200, 20);
	trackno_label.setText(" (default is -1 = the largest)", juce::NotificationType::sendNotification);
	trackno_label.setEditable(1, false, 0);
	trackno_label.onTextChange = [this]
	{
		auto temp = trackno_label.getTextValue();
		processor.m1.trackno = (int)temp.getValue();
        trackno_label.setText( temp.toString(),juce::NotificationType::sendNotification);
        warning_label.setText(temp.getValue().toString(), juce::NotificationType::dontSendNotification);
	};
	addAndMakeVisible(trackno_label);

	addAndMakeVisible(warning_label);
	warning_label.setBounds(10, 200, 380, 10);
	warning_label.setJustificationType(juce::Justification::left);
    
    // Add component for piano roll
    addAndMakeVisible(*allComps[0]);
    allComps[0]->setBounds(250,200,200,100);
    
    // Add component for Generating the transition matrices etc.
    addAndMakeVisible(*allComps[1]);
    allComps[1]->setBounds(250,300,200,100);
    
    addAndMakeVisible(*allComps[2]);
    allComps[2]->setBounds(250,400,200,100);
    
    //addAndMakeVisible(*allComps[3]);
    //allComps[3]->setBounds(0,100,200,100);
    
    addAndMakeVisible(*allComps[4]);
    allComps[4]->setBounds(0,100,200,199);
    
	setSize(500, 500);
}

ApresMidiAudioProcessorEditor::~ApresMidiAudioProcessorEditor()
{
    
}

//==============================================================================
void ApresMidiAudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	g.setColour(Colours::white);
	g.setFont(15.0f);
	
	g.drawFittedText("Order (of the next MIDI)", 10, 150, 200, 20, Justification::left, 1);
	g.drawFittedText("Track (of the next MIDI)", 10, 170, 200, 20, Justification::left, 1);

	if (processor.m1.problematic_track==1)
	{
		trackno_label.setColour(trackno_label.outlineColourId, juce::Colours::red);
		
		warning_label.setText("Problematic track number", juce::NotificationType::dontSendNotification);
	}
	else
	{
		trackno_label.setColour(trackno_label.outlineColourId, juce::Colours::blue);
		warning_label.setText("MIDI loaded fine", juce::NotificationType::dontSendNotification);
	}
}
void ApresMidiAudioProcessorEditor::buttonClicked(Button* button)
{
    if (button == &loadButton)
        loadButtonClicked();
};

void ApresMidiAudioProcessorEditor::loadButtonClicked()
{
    FileChooser chooser ("Load a MIDI file",
                         {},
                         "*.mid");
    if (chooser.browseForFileToOpen())
    {
        File file = chooser.getResult();
        
        processor.m1.is_ready = 0;
        processor.m1.reset();
        processor.m1.read_midi_file((const char *)file.getFullPathName().toUTF8());
        processor.m1.is_ready = 1;
    }
}
void ApresMidiAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
}
