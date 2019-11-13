/*
 ==============================================================================
 
 midipats.h
 Created: 5 Feb 2019 1:35:30pm
 Author:  tanil
 
 ==============================================================================
 */

#pragma once
#include <ctime>
#include <fstream>
#include "../JuceLibraryCode/JuceHeader.h"

class midi_core
{
public: 
    int speed = 100;
    std::vector<std::vector<int>> unique_patterns;
    std::vector<std::vector<int>> unique_durations;
    std::vector<int> alldurations;
    std::vector<int> allvelocities;
    std::vector<std::vector<int>> patterns;
    std::vector<int> durations;
    std::vector<int> state_buffer;
    std::vector<std::vector<int>> pre_transitions;
    std::vector<std::vector<int>> post_transitions;
    std::vector<std::vector<int>> post_durations;
    std::vector<std::vector<int>> post_velocities;
    
    std::vector<int> notenums;
    std::vector<int> velocities;
    std::vector<int> onoffs;
    std::vector<int> timestamps;
    std::vector<int> notes_per_track;
    
    std::vector<int> pattern_ids;
    int list_size = 0;
    int cur_pattern = 0;
    int previous_pattern = 0;
    int order;
    int notrans = 0;
    int number_of_unique_patterns = 0;
    int number_of_patterns=0;
    int is_ready = 0;
    int next_order = 2;
    int velocity = 70;
    int duration = 10;
    int trackno = -1;
    int problematic_track = 0;
    int track_with_max_events;
    int track_number_ok=0;
    
    midi_core();
    ~midi_core();
    
    void initialize();
    void reset();
    void choose_next_pattern();
    void analyze_file(const char * filename);
    void analyze_track();
    void find_unique_patterns();
    void make_transition_matrix();
    
    MidiFile myMIDIFile;
    int timer = 0;
    int gap = 44100 / 8;
    void process(MidiBuffer & midiMessages)
    {
        if (is_ready)
        {
            
            float offset = 100.0f;
            
            //if ((timer++) > ((int)(gap/m1.durations[m1.cur_pattern])))
            
            if ((timer++) > ((int)gap))
            {
                choose_next_pattern();
                
                for (int notei = 0; notei < unique_patterns[previous_pattern].size(); ++notei)
                {
                    midiMessages.addEvent(MidiMessage::noteOff(1, unique_patterns[previous_pattern][notei], (uint8)0), offset);
                }
                for (int notei = 0; notei < unique_patterns[cur_pattern].size(); ++notei)
                {
                    midiMessages.addEvent(MidiMessage::noteOn(1, unique_patterns[cur_pattern][notei], (uint8)velocity), offset);
                }
                timer = 0;
            }
            gap = duration * speed;
        }
        
    };
private:
    
    File myFile;
    void print_patterns_to_file();
    void write_transitions_to_file();
    void write_events_to_file();
    void print_summary();
};
