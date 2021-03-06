#To run "mingw32-make.exe"
#OBJS specifies which files to compile as part of the project
OBJS = ./*.cpp

#CC specifies which compiler we're using
CXX = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\Compilers\MinGW\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\Compilers\MinGw\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
CFLAGS = -w -static-libgcc -static-libstdc++

CXXFLAGS = -g -O0 -std=c++11 -Wall

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
EXE = EpicQuest.exe

all : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CFLAGS) $(LINKER_FLAGS) -o $(EXE)

debug : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CFLAGS) $(LINKER_FLAGS) -o $(EXE)
