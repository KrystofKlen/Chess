# Makefile Chess 
#*****************************************************

#Compiler
CXX=g++
LD=g++
CXXFLAGS=-g 

#Path varialbes
UI_PATH=src/UI/
APPLICATION_PATH=src/Application/
API_PATH=src/API/
GAME_CONTROL_PATH=src/Game/GameControl/
CORE_PATH=src/Game/Engine/Core/
PIECES_PATH=src/Game/Engine/Core/Pieces/
FILE_OPERATIONS_PATH=src/FileOperations/
AI_PATH=src/Game/Engine/AI/

#Variables for files in folders
UI=$(UI_PATH)/UI.o
API=$(API_PATH)Api.o $(API_PATH)Converter.o
GAME_CONTROL=$(GAME_CONTROL_PATH)GameControl.o $(GAME_CONTROL_PATH)OnePlayerGame.o $(GAME_CONTROL_PATH)TwoPlayersGame.o
CORE=$(CORE_PATH)Moves.o $(CORE_PATH)Piece.o $(CORE_PATH)Position.o $(CORE_PATH)Coordinates.o $(CORE_PATH)Board.o $(CORE_PATH)Game.o
PIECES=$(PIECES_PATH)King.o $(PIECES_PATH)Queen.o $(PIECES_PATH)Bishop.o $(PIECES_PATH)Knight.o $(PIECES_PATH)Rock.o $(PIECES_PATH)Pawn.o
FILE_OPERATIONS=$(FILE_OPERATIONS_PATH)FileVerifier.o $(FILE_OPERATIONS_PATH)PieceFileData.o $(FILE_OPERATIONS_PATH)HistoryFileData.o $(FILE_OPERATIONS_PATH)WritingAutomata.o $(FILE_OPERATIONS_PATH)ReadingAutomata.o $(FILE_OPERATIONS_PATH)FileOperations.o
APPLICATION=$(APPLICATION_PATH)Application.o
AI=$(AI_PATH)ComputerPlayer.o $(AI_PATH)DifficultLevel.o  $(AI_PATH)EasyLevel.o  $(AI_PATH)MidLevel.o

all: compile doc

doc:
	doxygen Doxyfile


compile: klenkrys

klenkrys: src/main.o  $(CORE) $(PIECES) $(GAME_CONTROL) $(AI) $(API) $(UI) $(FILE_OPERATIONS)  $(APPLICATION) 
	$(LD) $(CXXFLAGS) -o $@ $^ -lncurses 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	rm -f *.o klenkrys src/main.o $(UI_PATH)*.o $(APPLICATION_PATH)*.o $(API_PATH)*.o $(GAME_CONTROL_PATH)*.o $(GAME_CONTROL)*.o $(CORE_PATH)*.o $(PIECES_PATH)*.o $(FILE_OPERATIONS_PATH)*.o  $(AI_PATH)*.o

run:
	./klenkrys

deps:
	$(CXX) -MM *cpp > Makefile.d

-include Makefile.d