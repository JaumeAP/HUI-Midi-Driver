#ifndef HUIMIDI_H
#define HUIMIDI_H

#include <iostream>
#include <RtMidi.h>

class HUIMidi
{
public:
    HUIMidi(const char *Manufacturer,const char *Model);
    ~HUIMidi();
    void Sleep(int32_t duration);
    virtual void timer(); 
 private:
    RtMidiIn *midiin;
    RtMidiOut *midiout;
    int searchSource(const char *Manufacturer,const char *Model);
    int searchDestination(const char *Manufacturer,const char *Model);
    void start();
    void stop();
} ;

#endif // HUIMIDI_H
