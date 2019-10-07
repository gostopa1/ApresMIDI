/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ApresMidiAudioProcessor::ApresMidiAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                 .withInput("Input", AudioChannelSet::stereo(), true)
#endif
                 .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
                 )
#endif
{
    m1 = midi_core();
    
}

ApresMidiAudioProcessor::~ApresMidiAudioProcessor()
{
}

//==============================================================================
const String ApresMidiAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ApresMidiAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool ApresMidiAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool ApresMidiAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double ApresMidiAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ApresMidiAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int ApresMidiAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ApresMidiAudioProcessor::setCurrentProgram(int index)
{
}

const String ApresMidiAudioProcessor::getProgramName(int index)
{
    return {};
}

void ApresMidiAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void ApresMidiAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ApresMidiAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ApresMidiAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void ApresMidiAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    buffer.clear();
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    

    // Uncomment next 3 lines to work with play button
    AudioPlayHead::CurrentPositionInfo head_info;
    getPlayHead()->getCurrentPosition(head_info);
    
    if (head_info.isPlaying)
        
    {
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            if (m1.is_ready)
            {
                
                float offset = 100.0f;
                
                //if ((timer++) > ((int)(gap/m1.durations[m1.cur_pattern])))
                
                if ((timer++) > ((int)gap))
                {
                    m1.choose_next_pattern();
                    
                    for (int notei = 0; notei < m1.unique_patterns[m1.previous_pattern].size(); ++notei)
                    {
                        midiMessages.addEvent(MidiMessage::noteOff(1, m1.unique_patterns[m1.previous_pattern][notei], (uint8)0), offset);
                    }
                    for (int notei = 0; notei < m1.unique_patterns[m1.cur_pattern].size(); ++notei)
                    {
                        midiMessages.addEvent(MidiMessage::noteOn(1, m1.unique_patterns[m1.cur_pattern][notei], (uint8)m1.velocity), offset);
                    }
                    timer = 0;
                }
                gap = m1.duration * m1.speed;
            }
        }
    }


}

//==============================================================================
bool ApresMidiAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ApresMidiAudioProcessor::createEditor()
{
    return new ApresMidiAudioProcessorEditor(*this);
}

//==============================================================================
void ApresMidiAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ApresMidiAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ApresMidiAudioProcessor();
}
