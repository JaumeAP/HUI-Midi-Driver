#ifndef HUIMSG_H
#define HUIMSG_H

#include <vector>

// Message Midi
#define mNOTE           0x90   // 144
#define mCONTROL        0xB0   // 176
#define mRESET          0xFF   // 255

// Data 1 mCONTROL
#define mSHUTTLE        0x0D   // 13
#define mKEY            0x2F   // 47
//#define mHOTPEDAL     0xB0   // 176
//#define mPAN          0x40   // 40

// Data 2 - mKEY
#define mREWIND         0x01   // 1
#define mFORWARD        0x02   // 2
#define mSTOP           0x03   // 3
#define mPLAY           0x04   // 4
#define mREC            0x05   // 5
#define mJOG            0x05   // 7
#define mSHUT           0x06   // 6
// Data 2 Add mKEY
#define mON             0x40   // 64 
#define mOFF            0x00   // 0 

// Data 2 mSHUTTLE
#define mSHUTTLEL        0x01   // 1 
#define mSHUTTLER        0x41   // 65
 
const std::vector<unsigned char> mHUIReq      = { mNOTE, 0, 0  };
const std::vector<unsigned char> mHUIACK      = { mNOTE, 0, 0x7F };
const std::vector<unsigned char> mHUIRESET    = { mRESET };
const std::vector<unsigned char> mHUISHUTTLEL = { mCONTROL, mSHUTTLE, mSHUTTLEL };
const std::vector<unsigned char> mHUISHUTTLER = { mCONTROL, mSHUTTLE, mSHUTTLER };
const std::vector<unsigned char> mHUIPREPSHUT  = { mCONTROL, 0x0F, 0x0D };
const std::vector<unsigned char> mHUIPREPTRANS = { mCONTROL, 0x0F, 0x0E };
const std::vector<unsigned char> mHUISTOPON    = { mCONTROL, mKEY, mSTOP + mON  };
const std::vector<unsigned char> mHUISTOPOFF   = { mCONTROL, mKEY, mSTOP + mOFF };
const std::vector<unsigned char> mHUISHUTON     = { mCONTROL, mKEY, mSHUT + mON  };
const std::vector<unsigned char> mHUISHUTOFF    = { mCONTROL, mKEY, mSHUT + mOFF };
const std::vector<unsigned char> mHUIJOGON     = { mCONTROL, mKEY, mJOG + mON  };
const std::vector<unsigned char> mHUIJOGOFF    = { mCONTROL, mKEY, mJOG + mOFF };

#endif // HUIMSG_H