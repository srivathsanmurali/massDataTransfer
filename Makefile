#-------------------------------------------

SOURCE=massDataTransfer.cpp DevMem.cpp
OUTPUT=mdt
FLAGS=-w

all:
	echo "make arm or make pc"

arm:
	echo "arm"
	arm-linux-gnueabi-g++-4.7 $(FLAGS) $(SOURCE) -o $(OUTPUT)_arm

pc: 
	echo "pc"
	g++-4.8 $(FLAGS) $(SOURCE) -o $(OUTPUT)_pc

clean:
	rm -f $(OUTPUT)_arm
	rm -f $(OUTPUT)_pc
	
