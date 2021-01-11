#include "huimidi.h"
#include <CoreMIDI/CoreMIDI.h>
#include <CoreAudio/HostTime.h>
#include <CoreServices/CoreServices.h>
#include <RtMidi.h>
#include "porttime/porttime.h"
#include <vector>
#include <iomanip>

std::vector<HUIMidi *> instances;
const std::vector<unsigned char> mHUIReq = { 0x90, 0, 0  };
const std::vector<unsigned char> mHUIACK =  { 0x90, 0, 0x7F };

void printMessage(double deltatime,std::vector< unsigned char > *message){
    unsigned int nBytes = message->size();
    std::cout << "bytes: ";
    for ( unsigned int i=0; i<nBytes; i++ ) 
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)message->at(i) << " ";
    if ( nBytes > 0 )
        std::cout << "   stamp = " << std::fixed << deltatime << std::endl;
}

HUIMidi::HUIMidi() {
    bool live = false; 
    if( !instances.empty() ) stop();
    instances.push_back(this);
    try {
        midiin = new RtMidiIn();
        midiout = new RtMidiOut();
        huimidiin = new RtMidiIn();
        huimidiout = new RtMidiOut();        
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

void huicallback( double deltatime, std::vector< unsigned char > *message, void * userdata )
{
    HUIMidi& midi = *(HUIMidi *)userdata;
    if(*message == mHUIReq) {
        midi.live = true;
        //std::cout << ">>" << "HUIReq" << std::endl;
        return;
    }
    midi.huiReceived(deltatime,message);
}

void callback( double deltatime, std::vector< unsigned char > *message, void * userdata )
{
    HUIMidi& midi = *(HUIMidi *)userdata;
    midi.received(deltatime,message);
}

void HUIMidi::received( double deltatime, std::vector< unsigned char > *message) {
    std::cout << "DEV RECV ";
    printMessage(deltatime,message);
}

void HUIMidi::huiReceived( double deltatime, std::vector< unsigned char > *message) {
    std::cout << "VIRT RECV ";
    printMessage(deltatime,message);
}


void HUIMidi::watchdog() {
    if(live) {     
        live = false;
        //std::cout << ">>" << "HUIAck" << std::endl;
    } else
        std::cout << "VIRT RECV " << "HUITimeout" << std::endl;
    huimidiout->sendMessage(&mHUIACK);
}

void HUIMidi::Connect(const char *Manufacturer,const char *Model) {
    int srcNdx = searchSource(Manufacturer,Model);
    int dstNdx = searchDestination(Manufacturer,Model);    
    midiin->openPort( srcNdx );
    midiout->openPort( dstNdx );
    std::string srcName = std::string("HUI ") + midiin->getPortName(srcNdx);
    std::string dstName = std::string("HUI ") + midiout->getPortName(dstNdx);
    huimidiin->openVirtualPort(srcName);
    huimidiout->openVirtualPort(dstName);
    huimidiin->setCallback( &huicallback,this );
    //huimidiin->ignoreTypes( false, false, false );
    midiin->setCallback( &callback,this );
    //midiin->ignoreTypes( false, false, false );
}

void poll(PtTimestamp timestamp, void *) {
    for (std::vector<HUIMidi *>::iterator it = instances.begin(); it != instances.end(); ++it) 
        (*it)->watchdog();
}


void HUIMidi::start() {
    PtError err = Pt_Start(2000, poll,NULL);  
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
