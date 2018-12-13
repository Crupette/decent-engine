SRCDIR		:= src/
INCDIR		:= include/

OBJDIR		:= obj/
BINDIR		:= bin/

SRCFILES	:= $(wildcard $(SRCDIR)*.cpp)
OBJFILES	:= $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRCFILES))

CC		:= gcc
AR		:= ar
LIBS		:= -lSDL2 -lGLEW -lGL -lSDL2_ttf -lm -lSDL2_mixer
CPPFLAGS	:= -Wall -std=c++17 -I $(INCDIR)

OUT		:= libdecent-engine.a

.PHONY: build clean

build: $(OBJFILES) | $(BINDIR) $(OUTDIR)
	$(AR) crf $(BINDIR)$(OUT) $^
clean:
	@rm -rf $(OBJDIR)/*
	@rm -rf $(BINDIR)/*

$(OBJDIR)%.o : $(SRCDIR)%.cpp | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(LIBS) -c $< -o $@
	
$(OBJDIR):
	@mkdir -p $@
	
$(BINDIR):
	@mkdir -p $@
