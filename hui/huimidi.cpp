#include "openmidi.h"

openMidi::openMidi()
{
    try {
        midiin = new RtMidiIn();
        midiout = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }
}

openMidi::~openMidi()
{
}

