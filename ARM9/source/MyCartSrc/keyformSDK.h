#ifndef KEYFORMSDK_H_
#define KEYFORMSDK_H_
#include "nds.h"

//---- masked value
#define PAD_PLUS_KEY_MASK       0x00f0 // mask : cross keys
#define PAD_BUTTON_MASK         0x2f0f // mask : buttons
#define PAD_DEBUG_BUTTON_MASK   0x2000 // mask : debug button
#define PAD_ALL_MASK            0x3fff // mask : all buttons
#define PAD_RCNTPORT_MASK       0x2c00 // mask : factors ARM7 can read from RCNT register
#define PAD_KEYPORT_MASK        0x03ff // mask : factors ARM7/9 can read from KEY register

#define PAD_DETECT_FOLD_MASK    0x8000 // mask : folding

//---- button and key
#define PAD_BUTTON_A            0x0001 // A
#define PAD_BUTTON_B            0x0002 // B
#define PAD_BUTTON_SELECT       0x0004 // SELECT
#define PAD_BUTTON_START        0x0008 // START
#define PAD_KEY_RIGHT           0x0010 // RIGHT of cross key
#define PAD_KEY_LEFT            0x0020 // LEFT  of cross key
#define PAD_KEY_UP              0x0040 // UP    of cross key
#define PAD_KEY_DOWN            0x0080 // DOWN  of cross key
#define PAD_BUTTON_R            0x0100 // R
#define PAD_BUTTON_L            0x0200 // L
#define PAD_BUTTON_X            0x0400 // X
#define PAD_BUTTON_Y            0x0800 // Y
#define PAD_BUTTON_DEBUG        0x2000 // Debug button
#define PAD_TOUCH               0x1000 // touch screen

#define     KEY_REPEAT_START    25     // number of frames until key repeat starts
#define     KEY_REPEAT_SPAN     10     // number of key repeat interval frames

// key input data
typedef struct KeyInfo
{
    u16     cnt;                       // unprocessed input values
    u16     trg;                       // push trigger input
    u16     up;                        // release trigger input
    u16     rep;                       // push and hold repeat input

}
KeyInfo;

void KeyRead(KeyInfo * pKey);

#endif /*KEYFORMSDK_H_*/
