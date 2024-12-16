CC = g++
BISON = bison
FLEX = flex

TARGET = mycc
YY = yy
BISON_SOURCE = $(YY)/preproparser.y
FLEX_SOUCRCE = $(YY)/preproscanner.l
YY_SRC = $(YY)/src
BISON_OUTPUT = $(YY_SRC)/preparser.cc
FLEX_OUTPUT = $(YY_SRC)/prescanner.cc
SOURCES = src/*.cpp $(YY_SRC)/*.cc
INCLUDE = include
BIN = bin

OPTIMIZE = -O0


all : 
	@mkdir -p $(YY_SRC) $(BIN)
	@$(BISON) -ra -o $(BISON_OUTPUT) $(BISON_SOURCE)
	@$(FLEX) -o $(FLEX_OUTPUT) $(FLEX_SOUCRCE)
	@$(CC)  -DNDEBUG $(OPTIMIZE) -I$(INCLUDE) -I$(YY_SRC) -o $(BIN)/$(TARGET) $(SOURCES) 

debug :
	@mkdir -p $(YY_SRC) $(BIN)
	@$(BISON) -ra -o $(BISON_OUTPUT) $(BISON_SOURCE)
	@$(FLEX) -o $(FLEX_OUTPUT) $(FLEX_SOUCRCE)
	@$(CC)  -g $(OPTIMIZE) -I$(INCLUDE) -I$(YY_SRC) -o $(BIN)/$(TARGET)_d $(SOURCES) 


clean :
	@rm -r $(YY_SRC) $(BIN)