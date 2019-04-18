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
	// editor's size to whatever you need it to be.
	fileComp.reset(new FilenameComponent("fileComp",
		{},                       // current file
		false,                    // can edit file name,
		false,                    // is directory,
		false,                    // is for saving,
		"*.mid",                       // browser wildcard suffix,
		{},                       // enforced suffix,
		"Select midi file to open"));  // text when nothing selected
	addAndMakeVisible(fileComp.get());
	fileComp->addListener(this);

	/*
	//addAndMakeVisible(order_slider);
	order_slider.setValue(processor.m1.next_order);
	order_slider.setRange(1, 10, 1);
	order_slider.onValueChange = [this] {processor.m1.next_order = order_slider.getValue(); };
	order_slider.setBounds(10, 70, 200, 20);
	setSize(400, 300);

	order_text.setBounds(10,70,200,20);
	order_text.setText((String)processor.m1.order);
	order_text.onTextChange = [this]
	{
		processor.m1.next_order = atoi((char *) order_text.getText());
	};
	addAndMakeVisible(order_text);
	*/

	order_label.setBounds(200, 50, 200, 20);
	order_label.setText(" (default is 2)", juce::NotificationType::sendNotification);
	order_label.setEditable(1, false, 1);
	order_label.onTextChange = [this]
	{
		auto temp = order_label.getTextValue();
		processor.m1.next_order = (int)temp.getValue();
	};
	addAndMakeVisible(order_label);

	trackno_label.setBounds(200, 70, 200, 20);
	trackno_label.setText(" (default is -1 = the largest)", juce::NotificationType::sendNotification);
	trackno_label.setEditable(1, false, 1);
	trackno_label.onTextChange = [this]
	{
		auto temp = trackno_label.getTextValue();
		processor.m1.trackno = (int)temp.getValue();
	};
	addAndMakeVisible(trackno_label);

	addAndMakeVisible(speed_slider);
	speed_slider.setRange(1, 1000, 1);
	speed_slider.setValue(processor.m1.speed);
	speed_slider.onValueChange = [this] {processor.m1.speed = speed_slider.getValue(); };
	speed_slider.setBounds(10, 200, 200, 20);


	addAndMakeVisible(warning_label);
	warning_label.setBounds(10, 250, 380, 10);
	warning_label.setJustificationType(juce::Justification::left);


	setSize(400, 300);
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
	//g.drawFittedText ("Order", 10,50,100,20, Justification::centred, 1);
	g.drawFittedText("Order (of the next MIDI)", 10, 50, 200, 20, Justification::left, 1);
	g.drawFittedText("Track (of the next MIDI)", 10, 70, 200, 20, Justification::left, 1);

	g.drawFittedText("Duration Multiplier (Inverse Speed)", 10, 180, 200, 20, Justification::left, 1);

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

void ApresMidiAudioProcessorEditor::resized()
{
	fileComp->setBounds(10, 100, getWidth() - 20, 20);
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
}
