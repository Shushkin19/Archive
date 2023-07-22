ELF = compressor
CXX = g++
CXXFLAGS =  -g -O2 -I$(INC)

OBJ_PREFIX = objs/
SRC_PREFIX = src/

SRC = $(wildcard $(SRC_PREFIX)*.cpp)
OBJS = $(patsubst $(SRC_PREFIX)%.cpp, $(OBJ_PREFIX)%.o, $(SRC))
INC = inc/
DEPEND = 


$(ELF) : $(OBJS) 
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_PREFIX)%.o : $(SRC_PREFIX)%.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@


all :
	@echo $(SRC)
	@echo $(OBJS)
	@echo $(INC)
	@echo $(DEPEND)

clean :
	rm -f $(OBJ_PREFIX)*.o
	rm -f $(ELF)