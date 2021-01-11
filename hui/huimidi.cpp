#include "huimidi.h"
#include <CoreMIDI/CoreMIDI.h>
#include <CoreAudio/HostTime.h>
#include <CoreServices/CoreServices.h>
#include <RtMidi.h>
#include "porttime/porttime.h"
#include <vector>


std::vector<HUIMidi *> instances;
void HUIMidi::timer() { std::cout << "timer" << std::endl; }
 
HUIMidi::HUIMidi(const char *Manufacturer,const char *Model) {
    if( !instances.empty() ) stop();
    instances.push_back(this);
    try {
        midiin = new RtMidiIn();
        midiout = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }
    start();
}

HUIMidi::~HUIMidi()
{
    stop();
    instances.erase( std::remove(instances.begin(), instances.end(), this), instances.end() );
    if( !instances.empty() ) start();
}

void poll(PtTimestamp timestamp, void *userData) {
    for (std::vector<HUIMidi *>::iterator it = instances.begin(); 
        it != instances.end(); ++it) (*it)->timer();
}

void HUIMidi::start() {
    PtError err = Pt_Start(1000, poll,NULL);  
    if(err) throw err;
}

void HUIMidi::stop() { 
    PtError err = Pt_Stop(); 
    if(err) throw err;
}

void HUIMidi::Sleep(int32_t duration) { 
    Pt_Sleep(duration);
}


int MIDISearchPort(MIDIEndpointRef PortRef,const char *Manufacturer,const char *Model) {
    CFStringRef CFmodel = NULL;
    CFStringRef CFmanufacturer = NULL;
    CFStringRef CFManufacturer = CFStringCreateWithCString( NULL, Manufacturer, kCFStringEncodingASCII );
    CFStringRef CFModel = CFStringCreateWithCString( NULL, Model, kCFStringEncodingASCII );
    MIDIObjectGetStringProperty( PortRef, kMIDIPropertyManufacturer, &CFmanufacturer );
    MIDIObjectGetStringProperty( PortRef, kMIDIPropertyModel, &CFmodel );
    CFComparisonResult result = CFStringCompare(CFManufacturer,CFmanufacturer,0);
    CFComparisonResult result2 = CFStringCompare(CFModel,CFmodel,0);
    return !result && !result2;     
}

int HUIMidi::searchSource(const char *Manufacturer,const char *Model) {
  for(int count = 0; count < MIDIGetNumberOfSources(); count++ ) {
    MIDIEndpointRef portRef =  MIDIGetSource(count);
    if (MIDISearchPort(portRef,Manufacturer,Model)) 
      return count;
  }
  return -1;
}

int HUIMidi::searchDestination(const char *Manufacturer,const char *Model) {
  for(int count = 0; count < MIDIGetNumberOfDestinations(); count++ ) {
    MIDIEndpointRef portRef =  MIDIGetDestination(count);
    if (MIDISearchPort(portRef,Manufacturer,Model)) 
      return count;
  }
  return -1;
}
