/*
 ==============================================================================
 
 midipats.h
 Created: 5 Feb 2019 1:35:30pm
 Author:  tanil
 
 ==============================================================================
 */


#include "midipats.h"

midi_core::midi_core()
{
    initialize();
}

midi_core::~midi_core()
{
}

void midi_core::initialize()
{
    is_ready = 0;
    order = next_order;
    state_buffer.resize(order);
    srand(uint(time(NULL))); // Explicit conversion to avoid the warning
    list_size = (rand() % 9) + 1;
}

void midi_core::reset()
{
    order = next_order;
    previous_pattern = 0;
    cur_pattern = 0;
    state_buffer.resize(order);
    srand(uint(time(NULL))); // Explicit conversion to avoid the warning
    list_size = (rand() % 9) + 1;
    durations.resize(list_size);
    
    notenums.clear();
    timestamps.clear();
    velocities.clear();
    onoffs.clear();
    alldurations.clear();
    allvelocities.clear();
    patterns.clear();
    unique_patterns.clear();
    unique_durations.clear();
    pattern_ids.clear();
    pre_transitions.clear();
    post_durations.clear();
    post_velocities.clear();
    post_transitions.clear();
}

void midi_core::choose_next_pattern()
{
    previous_pattern = cur_pattern;
    
    int found_one = 0; // This keeps in track whether a suitable transition has been found
    
    // Check each possible transition to see if it matches the current state
    for (int transi = 0; transi < notrans; ++transi)
    {
        if (pre_transitions[transi] == state_buffer)
        {
            // If you found one, choose the next pattern randomly, and make the found_one into one.
            found_one = 1;
            int nextone = rand() % post_transitions[transi].size();
            cur_pattern = post_transitions[transi][nextone];
            duration = post_durations[transi][nextone];
            velocity = post_velocities[transi][nextone];
        }
    }
    // If no transitions are found, then just select one randomly.
    if (found_one == 0)
    {
        cur_pattern = rand() % number_of_unique_patterns;
    }
    
    for (int orderi = 1; orderi < order; ++orderi)
    {
        state_buffer[orderi - 1] = state_buffer[orderi];
    }
    
    state_buffer[order - 1] = cur_pattern;
    
}

void midi_core::analyze_file(const char * filename)
{
    // Opening the MIDI file
    myFile=File(filename);
    DBG(filename);
    FileInputStream myStream(myFile);
    
    myMIDIFile.readFrom(myStream);
    //myMIDIFile.convertTimestampTicksToSeconds();
    // Checking if our selection of track is possible, i.e. the MIDI file has enough tracks and the track has enough events to model
    int max_events = 0; // Here we accumulate the number of note on events
    track_with_max_events = 0;
    notes_per_track.clear();
    for (int tracki = 0; tracki < myMIDIFile.getNumTracks(); ++tracki)
    {
        const MidiMessageSequence & tempstream = *(myMIDIFile.getTrack(tracki));
        int temp = 0;
        int numevents = tempstream.getNumEvents();
        
        for (int eventi = 0; eventi < numevents; ++eventi)
        {
            if (tempstream.getEventPointer(eventi)->message.isNoteOn())
            {
                temp++;
            }
            
        }
        if (temp > max_events)
        {
            track_with_max_events = tracki;
        }
        notes_per_track.push_back(temp);
    }
    
    
    print_summary();
    DBG("Printing a summary of notes in each track");
    for (int notei=0;notei<notes_per_track.size();++notei)
    {
        DBG("Track "+(String)notei+" has "+(String)notes_per_track[notei]);
    }
}
void midi_core::analyze_track()
{
    
    track_number_ok = 0;
    
    if (trackno >= 0)
    {
        if (trackno < notes_per_track.size()) // Make sure that there are at least that many channels
        {
            if (notes_per_track[trackno] > (order + 1))
            {
                track_number_ok = 1;
            }
        }
    }
    
    int track_to_load = track_with_max_events;
    if (track_number_ok==0)
    {
        problematic_track = 1;
    }
    else
    {
        problematic_track = 0;
        track_to_load = trackno;
    }
    
    const MidiMessageSequence & mystream = *(myMIDIFile.getTrack(track_to_load));
    int noevents = mystream.getNumEvents();
    
    // Get all the note numbers, timestamps, velocities and onoffs (whether it is a note-on or note-off) for each note-on note-off event.
    for (int eventi = 0; eventi < noevents; ++eventi)
    {
        if (mystream.getEventPointer(eventi)->message.isNoteOnOrOff())
        {
            notenums.insert(notenums.end(), 1, mystream.getEventPointer(eventi)->message.getNoteNumber());
            timestamps.insert(timestamps.end(), 1, mystream.getEventPointer(eventi)->message.getTimeStamp());
            velocities.insert(velocities.end(), 1, mystream.getEventPointer(eventi)->message.getVelocity());
            
            if (mystream.getEventPointer(eventi)->message.isNoteOff())
            {
                onoffs.insert(onoffs.end(), 1, 0);
            }
            else
            {
                onoffs.insert(onoffs.end(), 1, 1);
            }
        }
    }
    
    DBG("Done reading MIDI File" + (String)onoffs.size());
    //write_events_to_file();
    
    alldurations.clear(); // To remove any contents that might be generated from the random patterns earlier
    durations.clear(); // To remove any contents that might be generated from the random patterns earlier
    patterns.clear(); // To remove any contents that might be generated from the random patterns earlier
    patterns.resize(1); // Allocate one element so that it doesn't complain in the first insertion
    int pati = 0;
    int curtime = timestamps[0];
    for (int eventi = 0; eventi < onoffs.size(); ++eventi)
    {
        if (velocities[eventi] > 0)
        {
            if (timestamps[eventi] == curtime)
            {
            }
            else
            {
                alldurations.insert(alldurations.end(), 1, timestamps[eventi] - 1 - curtime);
                allvelocities.insert(allvelocities.end(), 1, velocities[eventi]);
                pati++;
                patterns.resize(pati + 1);
                curtime = timestamps[eventi];
            }
            patterns[pati].insert(patterns[pati].end(), 1, notenums[eventi]);
        }
    };
    alldurations.insert(alldurations.end(), 1, timestamps[onoffs.size() - 1] - curtime);
    
    DBG("Size of patterns");
    DBG(patterns.size());
    //print_patterns_to_file();
    
    //patterns = allpatterns;
    list_size = int(patterns.size());
    
    durations = alldurations;
    //DBG("Done analyzing MIDI File");
    
    find_unique_patterns();
    
    // Make transition matrices:
    // Pre_transitions refers to the previous state, post_transition refers to the next state.
    make_transition_matrix();
    
    write_transitions_to_file();
    
    is_ready = 1;
    
};

void midi_core::write_transitions_to_file()
{
    std::ofstream transitions_f;
    
    transitions_f.open("transitions.txt", 'w');
    
    for (int transi = 0; transi < notrans; ++transi)
    {
        for (int orderi = 0; orderi < order; ++orderi)
        {
            transitions_f << (pre_transitions[transi][orderi]) << "\t";
        }
        transitions_f << " ||";
        for (int itemi = 0; itemi < post_transitions[transi].size(); ++itemi)
        {
            transitions_f << (post_transitions[transi][itemi]) << "\t";
        }
        transitions_f << "\n";
    }
    transitions_f.close();
}

// Function writing all the events of the selected track to a file
void  midi_core::write_events_to_file()
{
    
    std::ofstream myfile;
    myfile.open("example.txt", 'w');
    
    for (int notei = 0; notei < onoffs.size(); ++notei)
    {
        myfile << notenums[notei] << "\t" << onoffs[notei] << "\t" << timestamps[notei] << "\t" << velocities[notei] << "\n";
    }
    myfile.close();
}

void midi_core::print_patterns_to_file()
{
    std::ofstream myfile2;
    myfile2.open("teset2.txt", 'w');
    
    DBG("Done reading MIDI File" + (String)onoffs.size());
    for (int patterni = 0; patterni < patterns.size(); ++patterni)
    {
        for (int notei = 0; notei < patterns[patterni].size(); ++notei)
        {
            myfile2 << patterns[patterni][notei] << "\t";
        }
        myfile2 << "\n";
    }
    
    myfile2.close();
}

void midi_core::find_unique_patterns()
{
    //DBG("Now I will check patterns");
    
    number_of_patterns = int(patterns.size());
    pattern_ids.resize(number_of_patterns);
    
    int patnum = 0;
    // Assign IDs to patterns and find duplicates
    unique_patterns.clear();
    unique_durations.clear();
    for (int pati = 0; pati < number_of_patterns; ++pati)
    {
        pattern_ids[pati] = patnum;
        int found_similar = 0;
        for (int patj = 0; patj < pati; ++patj)
        {
            if (patterns[pati] == patterns[patj])
            {
                found_similar = 1;
                pattern_ids[pati] = pattern_ids[patj];
                
            }
        }
        if (found_similar == 0)
        {
            patnum++;
            unique_patterns.resize(patnum);
            unique_durations.resize(patnum);
            for (int notei = 0; notei < patterns[pati].size(); ++notei)
            {
                
                unique_patterns[patnum - 1].insert(unique_patterns[patnum - 1].end(), 1, patterns[pati][notei]);
                unique_durations[patnum - 1].insert(unique_durations[patnum - 1].end(), 1, alldurations[pati]);
            }
        }
    }
    
    number_of_unique_patterns = patnum;
    //DBG("Number of patterns: " + (String)number_of_patterns);
    //DBG("Number of unique patterns: " + (String)number_of_unique_patterns);
    
}

void midi_core::make_transition_matrix()
{
    pre_transitions.clear();
    post_durations.clear();
    post_velocities.clear();
    post_transitions.clear();
    
    int cnt = 0;
    std::vector<int> temp_trans;
    temp_trans.resize(order);
    for (int pati = order; pati < (number_of_patterns - 1); ++pati)
    {
        
        for (int orderi = 0; orderi < order; ++orderi)
        {
            temp_trans[orderi] = pattern_ids[pati - order + orderi];
        }
        
        int found_one = 0;
        for (int transi = 0; transi < pre_transitions.size(); ++transi)
        {
            if (temp_trans == pre_transitions[transi])
            {
                post_transitions[transi].insert(post_transitions[transi].end(), 1, pattern_ids[pati]);
                post_durations[transi].insert(post_durations[transi].end(), 1, alldurations[pati]);
                post_velocities[transi].insert(post_velocities[transi].end(), 1, allvelocities[pati]);
                found_one = 1;
            }
        }
        if (found_one == 0)
        {
            pre_transitions.resize(cnt + 1);
            post_transitions.resize(cnt + 1);
            post_durations.resize(cnt + 1);
            post_velocities.resize(cnt + 1);
            
            for (int orderi = 0; orderi < order; ++orderi)
            {
                //DBG(pre_transitions.size());
                //DBG("Counter");
                //DBG(cnt);
                pre_transitions[cnt].insert(pre_transitions[cnt].end(), 1, temp_trans[orderi]);
            }
            post_transitions[cnt].insert(post_transitions[cnt].end(), 1, pattern_ids[pati]);
            post_durations[cnt].insert(post_durations[cnt].end(), 1, alldurations[pati]);
            post_velocities[cnt].insert(post_velocities[cnt].end(), 1, allvelocities[pati]);
            cnt++;
        }
    }
    
    for (int orderi = 0; orderi < order; ++orderi)
    {
        state_buffer[orderi] = pre_transitions[0][orderi];
    }
    notrans = cnt;
}


void midi_core::print_summary()
{
};
