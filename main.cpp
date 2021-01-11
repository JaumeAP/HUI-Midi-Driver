
#include <iostream>
#include <cstdlib>
#include "hui/huimidi.h"

int main( int argc, char ** /*argv[]*/ )
{
  HUIMidi midi;
  midi.Connect("Hercules","DJ Control MP3 e2");  

  std::vector<unsigned char> message;
  double stamp;
  int nBytes,i;

  midi.midiin->ignoreTypes( false, false, false );

while ( -1 ) {
    double stamp = midi.midiin->getMessage( &message );
    nBytes = message.size();
    for ( i=0; i<nBytes; i++ )
      std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
    if ( nBytes > 0 )
      std::cout << "stamp = " << stamp << std::endl;
    midi.Sleep( 10 );
  }

  return 0;
}

