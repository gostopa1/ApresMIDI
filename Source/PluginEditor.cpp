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
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("LOAD MIDI FILE");
    loadButton.addListener(this);
    loadButton.setBounds(10, 10, 200, 20);

	// editor's size to whatever you need it to be.
   
	order_label.setBounds(200, 50, 200, 20);
	order_label.setText(" (default is 2 ho)", juce::NotificationType::sendNotification);
	order_label.setEditable(1, false, 0);
	order_label.onTextChange = [this]
	{
		auto temp = order_label.getTextValue();
		processor.m1.next_order = (int)temp.getValue();
	};
	addAndMakeVisible(order_label);

	trackno_label.setBounds(200, 70, 200, 20);
	trackno_label.setText(" (default is -1 = the largest)", juce::NotificationType::sendNotification);
	trackno_label.setEditable(1, false, 0);
	trackno_label.onTextChange = [this]
	{
		auto temp = trackno_label.getTextValue();
		processor.m1.trackno = (int)temp.getValue();
        trackno_label.setText( temp.toString(),juce::NotificationType::sendNotification);
        //trackno_label.setText( (String) temp.getValue().toString(),juce::NotificationType::sendNotification);
        warning_label.setText(temp.getValue().toString(), juce::NotificationType::dontSendNotification);
	};
	addAndMakeVisible(trackno_label);

	addAndMakeVisible(speed_slider);
	speed_slider.setRange(1, 1000, 1);
	speed_slider.setValue(processor.m1.speed);
	speed_slider.onValueChange = [this] {processor.m1.speed = speed_slider.getValue(); };
	speed_slider.setBounds(10, 150, 200, 20);

	addAndMakeVisible(warning_label);
	warning_label.setBounds(10, 200, 380, 10);
	warning_label.setJustificationType(juce::Justification::left);

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
	
	g.drawFittedText("Order (of the next MIDI)", 10, 50, 200, 20, Justification::left, 1);
	g.drawFittedText("Track (of the next MIDI)", 10, 70, 200, 20, Justification::left, 1);

	g.drawFittedText("Duration Multiplier (Inverse Speed)", 10, 130, 200, 20, Justification::left, 1);

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
