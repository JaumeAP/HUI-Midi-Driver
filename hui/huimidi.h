#ifndef OPENMIDI_H
#define OPENMIDI_H

#include <RtMidi.h>
#include <iostream>
#include "openhuitimer.h"

class openMidi : public openHUITimer
{
public:
    openMidi();
    ~openMidi();
protected:
    virtual void timer() { std::cout << "timer" << std::endl; };
private:
    RtMidiIn  *midiin;
    RtMidiOut *midiout;
};

#endif // OPENMIDI_H
