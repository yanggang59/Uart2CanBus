# Makefile for sample program
.PHONY			: all clean

# the program to build
NAME			:= main

# Build tools and flags
CXX			:= g++
LD			:= g++
SRCS                    := $(wildcard *.cpp)
OBJS                    := $(patsubst %cpp, %o, $(SRCS))
CPPFLAGS		:= -w -I/usr/include/ \
			       -I./

#LDFLAGS

all			: $(NAME)

$(NAME)			: $(OBJS)
	$(LD) -o $@ $^ $(CPPFLAGS) $(LDFLAGS)

%.o		: %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

clean			:
	$(RM) *.o $(NAME)
