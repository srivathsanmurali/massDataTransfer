#ifndef __mdtHeader_H_
#define __mdtHeader_H_

#include "DevMem.h"
typedef unsigned int WORD;

// number of words that the header occupies
const int headerSize = 7;

// Can have diff types of packets, frames, imu, control, etc. Differentiated by signature first word in the header
// header designed for the frame tranfer packets.
typedef struct mdtHeader{
	WORD signature;		// signature to make sure its a packet issued for frame transfer - 0xCFCF (Camera Frame)
	WORD size;			// size of the header
	WORD camID;			// gives the camera ID for multi camera systems
	WORD nPackets;		// number of packets for the current frame
	WORD packetID;		// gives the current packetID < nPackets
	WORD packetLen;  	// gives the length of the current packet
	WORD lastPacket; 	// will be set to FFFF if last packet else 0000
} mdtHeader, *PmdtHeader;

void wrapWithHeaders(WORD[] &output, int nPackets, int packetLen, char* filename);
#endif __mdtHeader_H_
