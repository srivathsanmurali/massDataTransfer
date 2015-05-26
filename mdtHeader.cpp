#include "mdtHeader.h"
#include <iostream>
#include <fstream>

void wrapWithHeaders(WORD[][] &output, int &nPackets, int packetLen, char* filename){
	ifstream fin;
	fin.open(filename,ios::in);
	
	fin.seekg(0,ios::end);
	int totalWords = fin.tellg()/2;
	fin.seekg(0,ios::beg);

	nPackets = (totalWords/(packetLen-headerSize)) + 1;
	
	// setting up stuff that dont change between packets
	PmdtHeader head;
	head->signature 	= 0xCFCF;
	head->size 			= headerSize;
	head->camID 		= 0x0000;
	head->nPackets		= nPackets;
	// need to set packetID;
	head->packetLen 	= packetLen; // need to change for last packet
	head->lastPacket 	= 0x0000;
	output = new WORD[nPackets][packetLen];
	for(int i = 0; i<nPackets-1;i++){
		output[i][0] = 0xCFCF;
		output[i][1] = headerSize;
		output[i][2] = 0x0000;
		output[i][3] = nPackets;
		output[i][4] = i;
		output[i][5] = packetLen;
		output[i][6] = 0x0000;

		for (int j = headerSize; j< packetLen;j++){
			fin.get(v1);
			fin.get(v2);
			unsigned int value = v2 <<8 | v1;			
			output[i][j] = value;
		}
	}
	int lastlen = totalWords%(packetLen-headerSize);
	output[nPackets-1][0] = 0xCFCF;
	output[nPackets-1][1] = headerSize;
	output[nPackets-1][2] = 0x0000;
	output[nPackets-1][3] = nPackets;
	output[nPackets-1][4] = nPackets-1;
	output[nPackets-1][5] = lastlen;
	output[nPackets-1][6] = 0xFFFF;

	for(int i = 0; i< lastlen;i++){
		fin.get(v1);
		fin.get(v2);
		unsigned int value = v2 <<8 | v1;	
		output[nPackets-1][i] = value;
	}
	//padding
	for(int i = lastlen; i<packetLen; i++){
		output[nPackets-1][i] = 0xFFFF;	
	}
}