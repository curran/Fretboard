#include "midi.h"
#include "keymap.h"
#include "instrument.h"
using namespace std;

jack_client_t *client;
jack_port_t *output_port;

queue< int > key_down_queue;
queue< int > key_up_queue;

Instrument instrument;

void connect_to_jack(){
  //TODO move this to gui
  //  instrument.setLowestNote(50);
  //instrument.setOffset(0,0);
  //instrument.setOffset(1,5);
  //instrument.setOffset(2,10);
  //instrument.setOffset(3,15);

  jack_status_t status;
  if((client = jack_client_open ("Fretboard", JackNoStartServer, &status)) == 0){
    QMessageBox::critical( 0, "Fretboard", QString("Cannot connect to Jack. Is the Jack server running?"));
    exit(1);
  }
  else{
    jack_set_process_callback (client, process, 0);
    output_port = jack_port_register (client, "out", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);

    if (jack_activate(client)){
      QMessageBox::critical( 0, "Fretboard", QString("Cannot activate Jack client."));
      exit(1);
    }     
  }
}

void disconnect_from_jack(){
  jack_client_close(client);
}

int process(jack_nframes_t nframes, void * /*arg*/)
{
  void* port_buf = jack_port_get_buffer(output_port, nframes);

  unsigned char* buffer;
  jack_midi_clear_buffer(port_buf);

  int x; int y; int key;
  while(!key_down_queue.empty()){
    key = key_down_queue.front();
    key_down_queue.pop();
    if(translate_key_to_grid(key,x,y)){
      buffer = jack_midi_event_reserve(port_buf, 0, 3);
      buffer[2] = 64;     /* velocity */
      buffer[1] = instrument.getNote(x,y);//lowest_note+x+y*row_interval;
      buffer[0] = 0x90;	/* note on */
    }
  }
  while(!key_up_queue.empty()){
    key = key_up_queue.front();
    key_up_queue.pop();
    if(translate_key_to_grid(key,x,y)){
      buffer = jack_midi_event_reserve(port_buf, 0, 3);
      buffer[2] = 64;     /* velocity */
      buffer[1] = instrument.getNote(x,y);//lowest_note+x+y*row_interval;
      buffer[0] = 0x80;	/* note off */
    }
  }
  return 0;
}
