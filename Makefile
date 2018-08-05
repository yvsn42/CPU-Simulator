#Target
CPU := CPU.out
all : $(CPU)

# Files to archive
## Get all C++ files from current directory
SOURCES	:= $(wildcard *.cpp)
## Replace .c with .o
OUR_OBJS := $(patsubst %.cpp,%.o,$(SOURCES))

# Compiler options
CC := g++
# General g++ options
CCFLAGS	:= -Wall -Werror -ansi

## Debug flag
ifneq ($(D),1)
CCFLAGS	+= -O2
else
CCFLAGS	+= -O0
CCFLAGS	+= -g
endif

# Don't print the commands unless explicitly requested with `make V=1`
ifneq ($(V),1)
Q = @
V = 0
endif

# Generate dependencies
DEPFLAGS = -MMD -MF $(@:.o=.d)

## Dependencies for each file"
DEPS := $(patsubst %.o,%.d,$(OUR_OBJS))
-include $(DEPS)

$(CPU) : $(OUR_OBJS)
	@echo "BUILT	$(CPU)"
	$(Q)$(CC) $(CCFLAGS) -o $(CPU) $(OUR_OBJS)

%.o : %.cpp
	@echo "CC 	$@"
	$(Q)$(CC) $(CCFLAGS) -c $< $( DEPFLAGS)

clean :
	@echo "CLEAN	$(shell pwd)"
	$(Q)rm -f $(OUR_OBJS) $(DEPS)
