#ifndef __MASSDATATRANSFER_H_
#define __MASSDATATRANSFER_H

#include "mdtHeader.h"

// chooses if to use files or message
const int filemode = 1;

// uses arm library if set to 1
const int armMode =1;

// physical address to write to
const unsigned int long long address = 0x6FE00000;

// constant message to send
const unsigned int mess = 0xdead;

// number of iteratins of message to send
const int defaultIters =16*512;//10//24

// if the messages/file need to be send infintly 
const int infinte =1; 

// displays log of what is sent if set to 1. (slows the process, print is expensive)
const int log =  0;


#endif __MASSDATATRANSFER_H_
