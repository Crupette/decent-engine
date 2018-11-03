SRCDIR		:= src/
INCDIR		:= include/

OBJDIR		:= obj/
BINDIR		:= bin/

SRCFILES	:= $(wildcard $(SRCDIR)*.cpp)
OBJFILES	:= $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRCFILES))

CC		:= g++
LIBS		:= -lSDL2 -lGLEW -lGL -lSDL2_ttf
CPPFLAGS	:= -Wall -Werror -std=c++17 -I $(INCDIR)

OUT		:= Decent-Engine.a

.PHONY: build clean

build: $(OBJFILES)
	@echo Building engine
	@$(AR) rcs $(BINDIR)$(OUT) $^
	@echo Liked obj files to $(BINDIR)$(OUT)
clean:
	@echo Cleaning temporary and built files
	@rm -rf $(OBJDIR)/*
	@rm -rf $(BINDIR)/*

$(OBJDIR)%.o : $(SRCDIR)%.cpp
	@echo Compiling $< into $@
	$(CC) $(CPPFLAGS) $(LIBS) -c $< -o $@
