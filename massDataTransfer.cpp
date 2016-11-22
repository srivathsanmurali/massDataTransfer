#include "DevMem.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#define FILEMODE 1
#define ARMMODE 1
#define ADDRESS 0x6FE00000
#define MESSAGE 0xdead
#define DEFAULT_ITERS 16*512//10//24
#define INFINITE 1
#define LOG 0
using namespace std;

void sendFile(char * filename,unsigned int long long phyAddress){

	#if ARMMODE
		// opening a mem node to send data
		DevMem dm(phyAddress,1024);
		cout<<"opened memory :"<< phyAddress <<endl;
	#endif

	ifstream fin;
	fin.open(filename,ios::in);


	fin.seekg(0,ios::end);
	int len = fin.tellg()/2;
	fin.seekg(0,ios::beg);
	printf("%d length \n",len);

	char v1,v2;
	int lenLeft = len;
	while (lenLeft != 0){
		if(lenLeft > 1024){
			for (int i = 0; i< 1024;i++){
				// fin>>v1>>v2;
				fin.get(v1);
				fin.get(v2);
				#if LOG
					cout<<v1<<v2;
				#endif
				unsigned int value = v2 <<8 | v1;
				#if ARMMODE
					dm.write_word(0,value);
				#endif
			}
			lenLeft = lenLeft-1024;
		}
		else{
			// sending the last set of data
			for (int i = 0; i< lenLeft;i++){
				// fin>>v1>>v2;
				fin.get(v1);
				fin.get(v2);
				#if LOG
					cout<<v1<<v2;
				#endif
				unsigned int value = v2 <<8 | v1;
				#if ARMMODE
					dm.write_word(0,value);
				#endif
			}
			//  padding with 0xffff
			for (int i =0; i<1024-lenLeft; i++){
				#if ARMMODE
					dm.write_word(0,0xffff);
				#endif
			}
			lenLeft = 0;
		}
	}
	fin.close();
}


void sendMessage(unsigned int message,unsigned int long long phyAddress, int totalIter){

	#if ARMMODE
		// opening a mem node to send data
		DevMem dm(phyAddress,1024);
		cout<<"opened memory :"<< phyAddress <<endl;
	#endif

	for (int i = 0; i<totalIter; i++){
		#if ARMMODE
			dm.write_word(0,message);
		#endif
 		printf("0x%0.4X -> 0x%X\n",message,phyAddress);
	}
}
int main(int argc, char* argv[]){

  do {
		#if FILEMODE
		sendFile(argv[1],ADDRESS);
		#else
		sendMessage(MESSAGE,ADDRESS,DEFAULT_ITERS);
		#endif
		sleep(1);
	} while(INFINITE)
	return 0;
}

