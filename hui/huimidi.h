#ifndef HUIMIDI_H
#define HUIMIDI_H

#include <iostream>
#include <RtMidi.h>

class HUIMidi
{
public:
    HUIMidi();
    ~HUIMidi();
    void Sleep(int32_t duration);
    void Connect(const char *Manufacturer,const char *Model);
    virtual void timer(); 
    RtMidiIn *midiin;
    RtMidiOut *midiout;
    RtMidiIn *huimidiin;
    RtMidiOut *huimidiout;
 private:
    int searchSource(const char *Manufacturer,const char *Model);
    int searchDestination(const char *Manufacturer,const char *Model);
    void start();
    void stop();
} ;

#endif // HUIMIDI_H
