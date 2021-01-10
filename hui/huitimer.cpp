#include "huitimer.h"
#include "porttime/porttime.h"
#include <vector>

/////////////////////
//class openHUITimer
////////////////////

std::vector<HUITimer *> instances;

void poll(PtTimestamp timestamp, void *userData) {
    for (std::vector<HUITimer *>::iterator it = instances.begin(); 
        it != instances.end(); ++it) (*it)->timer();
}

void HUITimer::start() {
    PtError err = Pt_Start(1000, poll,NULL);  
    if(err) throw err;
}

void HUITimer::stop() { 
    PtError err = Pt_Stop(); 
    if(err) throw err;
}

HUITimer::HUITimer()  {  
    if( !instances.empty() ) stop();
    instances.push_back(this);
    start();
}

HUITimer::~HUITimer() {  
    stop();
    instances.erase( std::remove(instances.begin(), instances.end(), this), instances.end() );
    if( !instances.empty() ) start();
}

