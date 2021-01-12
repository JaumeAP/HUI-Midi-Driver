
#include <iostream>
#include <cstdlib>
#include "hui/huimidi.h"

#define hSHUTTLE1    0x30
#define hSHUTTLE2    0x31
#define hCUE1        0x0E
#define hPAUSE1      0x0F
#define hKEYSET      0x7F
#define hKEYRESET    0x00
#define hSHUTLEFT    0x7F
#define hSHUTRIGHT   0x01

const std::vector<unsigned char> mHERCSHUTTLEL = { mCONTROLLER, hSHUTTLE1, hSHUTLEFT  };
const std::vector<unsigned char> mHERCSHUTTLER = { mCONTROLLER, hSHUTTLE1, hSHUTRIGHT  };
const std::vector<unsigned char> mHERCCUE1 = { mNOTE, hCUE1, hKEYSET  };
const std::vector<unsigned char> mHERCPAUSE1 = { mNOTE, hPAUSE1, hKEYSET  };

class Hercules : public HUIMidi {
protected:  
    void received( double deltatime, const std::vector< unsigned char > *message);
};


void Hercules::received( double deltatime, const std::vector< unsigned char > *message) {
    if(*message == mHERCCUE1)
       sendMessage(message);
    printMessage(deltatime,message);
}


int main( int argc, char ** /*argv[]*/ )
{
  Hercules midi;
  midi.Connect("Hercules","DJ Control MP3 e2");  
  
  while ( -1 ) {
    
  }

  return 0;
}

