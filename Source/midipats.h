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
	int speed = 200;
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
    
    midi_core();
    ~midi_core();
    
    void initialize();
    void reset();
    void choose_next_pattern();
    void read_midi_file(const char * filename);
    void find_unique_patterns();
    void make_transition_matrix();
private:

    void print_patterns_to_file();
    void write_transitions_to_file();
    void write_events_to_file();
};
