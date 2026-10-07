#
#	o--{============> THE SUPREME MAKEFILE <============}--o
#
#		       prepare yourself, he has arrived
#
#	Makefile to insert in the mother directory of your c++
#	project.
#	It takes all .cpp files in this directory and in the wole
#	subdirectory tree and compiles them all to object files in
#	an object directory.
#	Specifying the TARGET you can build your program.
#
#					     ! Be Careful !
#	This makefile functions with an only main function (as
#	usually done in projects), else you computer could probably
#	explode. Also, be sure to eliminate all file you don't want
#	to compile from your project folder, else they will be
#	compiled.
#
#	Developer:		Luca Malucelli (Cattivik)
#	Info, C&C:		luca.malucelli@studenti.unimi.com
#
#
#		      +++ Usage instructions +++
#	Specify the base variables:
#		-TARGET		-> the executable you want to create
#		-OBJ_DIR	-> the directory in which object files
#					   will be stored
#		-LIBS		-> The flags to external libraries you want
#					   to use
#	Digit "make" on your terminal and let the magic begin.
#	For partial compilation (creating object file for a specific
#	file) for a FILENAME.cpp file digit "make FILENAME.o" on 
#	your terminal.

#			     +++ BASE VARIABLES +++
CC = g++
TARGET = STURM
OBJ_DIR = obj
LIBS = C:\Users\utente\Downloads\glfw-3.4\include\GLFW\ -lglfw -ldl -lGL

#	     +++ SEARCH FUNCTION AND DEPENDENT VARIABLES +++
rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRC_W_DIR := $(wildcard *.cpp) $(call rwildcard,*/,*.cpp)
SRC = $(notdir $(SRC_W_DIR))

HEAD_W_DIR = $(SRC_W_DIR:.cpp=.h)
HEAD = $(SRC:.cpp=.h)

OBJ = $(SRC:.cpp=.o)
OBJ_W_DIR = $(addprefix $(OBJ_DIR)/, $(OBJ))

.SUFFIXES:	#Disable built-in rules

#				+++ MAIN COMPILATION FLOW +++
all: $(TARGET)
	@echo ""
	@echo "o--{=========> Makefile salutes you <=========}--o"
	@echo ""
	./$(TARGET)

$(TARGET):  $(OBJ)
	@echo ""
	g++ -o $@ $(OBJ_W_DIR) $(LIBS)

%.o: $(SRC_W_DIR) $(filter %$(@:.o=.h),$(SRC_W_DIR))
	$(CC) -g -c -o $(OBJ_DIR)/$@ $(filter %$(@:.o=.cpp),$(SRC_W_DIR))

#			 +++ LAUNCH ONLY FUNCTION +++
launch: 
	./$(TARGET)

#			   +++ PRINT FUNCTION +++
# 	In terminal digit "make print-VARIABLE" for printing out the 
#	content of VARIABLE
print-% : ; @echo $* = $($*)

# 			   +++ CLEAN FUNCTION +++
# Function for removing objects in OBJ_DIR and the executable
clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TARGET)
