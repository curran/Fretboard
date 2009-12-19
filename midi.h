#ifndef MIDI_H
#define MIDI_H

#include "instrument.h"
#include <QMessageBox>
#include <queue>
#include <jack/jack.h>
#include <jack/midiport.h>

extern std::queue< int > key_down_queue;
extern std::queue< int > key_up_queue;
extern Instrument instrument;

void connect_to_jack();
void disconnect_from_jack();
int process(jack_nframes_t nframes, void * arg);

#endif
