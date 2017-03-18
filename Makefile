DEPDIR = .d
ODIR = obj
SDIR = src
INCDIR = inc

DIRS =
$(shell mkdir -p $(DEPDIR) >/dev/null)
$(shell find $(SDIR) -type d -exec mkdir -p $(ODIR)/\{\} >/dev/null \;)
$(shell find $(SDIR) -type d -exec mkdir -p $(DEPDIR)/\{\} >/dev/null \;)

DEPFLAGS = -MT $@ -MD -MP -MF $(DEPDIR)/$*.Td

CC = g++-4.9
CFLAGS = -std=c++11 -Wall -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl

COMPILE = $(CC) $(DEPFLAGS) $(CFLAGS) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

_SRC = $(wildcard $(SDIR)/*.cpp) $(wildcard $(SDIR)/*/*.cpp) $(wildcard $(INCDIR)/*/*.cpp)
_OBJ = $(_SRC:.cpp=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(OBJ): $(ODIR)/%.o: %.cpp %.h $(DEPDIR)/%.d
	$(COMPILE) -o $@ $<
	$(POSTCOMPILE)

all: exercise_5.cpp $(OBJ)
	$(CC) -o bin/$@ exercise_5.cpp $(OBJ) $(CFLAGS)

debug: exercise_5.cpp $(OBJ)
	$(CC) -g -o bin/$@ exercise_5.cpp $(OBJ) $(CFLAGS)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf .d/*
