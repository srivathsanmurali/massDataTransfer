#include "DevMem.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#define filemode 1
#define armMode 1
#define address 0x6FE00000
#define mess 0xdead
#define defaultIters 16*512//10//24
#define infinte 1 
#define log 0
using namespace std;

void sendFile(char * filename,unsigned int long long phyAddress){
	
	#if armMode == 1
		// opening a mem node to send data	
		DevMem dm(phyAddress,1024);
		cout<<"opened memory :"<< phyAddress <<endl;
	#endif

	ifstream fin;
	fin.open(filename,ios::in);

	
	fin.seekg(0,ios::end);
	int len = fin.tellg()/2;
	fin.seekg(0,ios::beg);
	#if armMode == 1
		//dm.write_word(0,0xdead);
		//dm.write_word(0,0xbeef);
		//dm.write_word(0,len);
	#endif
	printf("%d length \n",len);
		
	char v1,v2;
	int lenLeft = len;
	while (lenLeft != 0){
		if(lenLeft > 1024){
			for (int i = 0; i< 1024;i++){
				// fin>>v1>>v2;
				fin.get(v1);
				fin.get(v2);
				#if log == 1
					cout<<v1<<v2;
				#endif
				unsigned int value = v2 <<8 | v1;			
				#if armMode == 1
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
				#if log == 1
					cout<<v1<<v2;
				#endif
				unsigned int value = v2 <<8 | v1;			
				#if armMode == 1
					dm.write_word(0,value);	
				#endif
			}
			//  padding with 0xffff
			for (int i =0; i<1024-lenLeft; i++){
				#if armMode == 1
					dm.write_word(0,0xffff);	
				#endif	
			}
			lenLeft = 0;
		}
	}
	/* using padding implemented above
	while(!fin.eof()){
		#if armMode == 1
			dm.write_word(0,value);	
		#endif
 		//printf("0x%0.4X -> 0x%X\n",value,phyAddress);

		fin>>v1>>v2;
		value = v2 <<8 | v1;
	}
	*/
	fin.close();
}


void sendMessage(unsigned int message,unsigned int long long phyAddress, int totalIter){
	
	#if armMode == 1
		// opening a mem node to send data	
		DevMem dm(phyAddress,1024);
		cout<<"opened memory :"<< phyAddress <<endl;
	#endif

	for (int i = 0; i<totalIter; i++){
		#if armMode == 1
			dm.write_word(0,message);	
		#endif
 		printf("0x%0.4X -> 0x%X\n",message,phyAddress);	
	}
}
int main(int argc, char* argv[]){
	
	//int numRep = atoi(argv[2]);	
//	for(int i = 0; i< numRep; i++){	
	while(true){
		#if filemode == 1		
		sendFile(argv[1],address);
		#else 
		sendMessage(mess,address,defaultIters);
		#endif
		#if infinte == 0
		break;
		#endif	
		sleep(1);
	}
	return 0;
}

