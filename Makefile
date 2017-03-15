DEPDIR = .d
$(shell mkdir -p $(DEPDIR) >/dev/null)

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

CC = g++-4.9
CFLAGS =-std=c++11 -Wall -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl

COMPILE = $(CC) $(DEPFLAGS) $(CFLAGS) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

ODIR = obj

src = $(wildcard *.c)
obj = $(src:.c=.o)

_OBJ = $(wildcard **/*.cpp)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp %.h $(DEPDIR)/%.d
	$(COMPILE) -o $@ $<
	$(POSTCOMPILE)

all: exercise_4.cpp $(_OBJ)
	$(CC) $(CFLAGS) -o bin/$@ exercise_4.cpp $(OBJ)
