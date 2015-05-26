#include "mdtHeader.h"
#include <iostream>
#include <fstream>

void wrapWithHeaders(WORD[] &output, int &nPackets, int packetLen, char* filename){
	ifstream fin;
	fin.open(filename,ios::in);
	
	fin.seekg(0,ios::end);
	int totalWords = fin.tellg()/2;
	fin.seekg(0,ios::beg);

	nPackets = (totalWords/(packetLen-headerSize)) + 1;
	
	// setting up stuff that dont change between packets
	PmdtHeader head;
	head->signature = 0xCFCF;
	head->size 		= headerSize;
	head->camID 	= 0x0000;
	head->nPackets	= nPackets;
	// need to set packetID;
	head->packetLen = packetLen; // need to change for last packet

	
}