#ifndef HUIMSG_H
#define HUIMSG_H

#include <vector>

// Message Midi
#define mNOTE           0x90   // 144
#define mCONTROLLER     0xB0   // 176
#define mRESET          0xFF   // 255

// Data 1 mCONTROLLER
//#define mHOTPEDAL     0xB0   // 176
#define mSHUTTLE        0x0D   // 13
#define mTRANSPORTKEY   0x2F   // 47
//#define mPAN          0x40   // 40

// Data 2 - mTRANSPORTKEY
#define mREWIND         0x01   // 1
#define mFORWARD        0x02   // 2
#define mSTOP           0x03   // 3
#define mPLAY           0x04   // 4
#define mREC            0x05   // 5
#define mJOG            0x05   // 5
// Data 2 Add mTRANSPORTKEY
#define mTRANSPON       0x40   // 64 
#define mTRANSPOFF      0x00   // 0 

// Data 2 mSHUTTLE
#define mSHUTTLEL        0x01   // 1 
#define mSHUTTLER        0x41   // 65

const std::vector<unsigned char> mHUIReq =      { mNOTE, 0, 0  };
const std::vector<unsigned char> mHUIACK =      { mNOTE, 0, 0x7F };
const std::vector<unsigned char> mHUIRESET =    { mRESET };
const std::vector<unsigned char> mHUISHUTTLEL = { mCONTROLLER, mSHUTTLE, mSHUTTLEL };
const std::vector<unsigned char> mHUISHUTTLER = { mCONTROLLER, mSHUTTLE, mSHUTTLER };
const std::vector<unsigned char> mHUITRNSPRT =  { mCONTROLLER, 0x0F, 0x0E };
const std::vector<unsigned char> mHUIKEY =      { mCONTROLLER, 0x0F, 0x0D };

#endif // HUIMSG_H