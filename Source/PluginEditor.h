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
class ApresMidiAudioProcessorEditor  : public AudioProcessorEditor, public FilenameComponentListener, public Slider::Listener
{
public:
    ApresMidiAudioProcessorEditor (ApresMidiAudioProcessor&);
    ~ApresMidiAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	
	Slider speed_slider;
	Slider order_slider;
	TextEditor order_text;
	Label order_label;

	Label trackno_label;
	Label warning_label;
	
	void filenameComponentChanged(FilenameComponent* fileComponentThatHasChanged) override
	{
		if (fileComponentThatHasChanged == fileComp.get())
		{
			processor.m1.is_ready = 0;
			processor.m1.reset();
			processor.m1.read_midi_file((const char *)(fileComp->getCurrentFileText()).toUTF8());
			processor.m1.is_ready = 1;
		}
	}
	void sliderValueChanged(Slider* slider) override {};

private:

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	std::unique_ptr<FilenameComponent> fileComp;
	ApresMidiAudioProcessor& processor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ApresMidiAudioProcessorEditor)
};
