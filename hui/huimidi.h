#ifndef HUIMIDI_H
#define HUIMIDI_H

#include <iostream>
#include <RtMidi.h>
#include "huimsg.h"

class HUIMidi
{
public:
    HUIMidi();
    ~HUIMidi();
    void Sleep(int32_t duration);
    void Connect(const char *Manufacturer,const char *Model);
  protected:
    virtual void timer() {};
    virtual void received( double deltatime, const std::vector< unsigned char > *message);
    virtual void sendMessage(const std::vector< unsigned char > *message);
    virtual void huiReceived( double deltatime,  const std::vector< unsigned char > *message);
    virtual void huiSendMessage(const std::vector< unsigned char > *message);
    void printMessage(double deltatime,const std::vector< unsigned char > *message);
  private:
    RtMidiIn *midiin;
    RtMidiOut *midiout;
    RtMidiIn *huimidiin;
    RtMidiOut *huimidiout;
    int live;
    void start();
    void stop();
    void watchdog();
    int searchSource(const char *,const char *);
    int searchDestination(const char *,const char *);
    friend void poll(int32_t, void *);
    friend void callback( double, std::vector< unsigned char > *, void * );
    friend void huicallback( double, std::vector< unsigned char > *, void * );
} ;

#endif // HUIMIDI_H
