SRCDIR		:= src/
INCDIR		:= include/

OBJDIR		:= obj/
BINDIR		:= bin/
OUTDIR		:= out/

SRCFILES	:= $(wildcard $(SRCDIR)*.cpp)
OBJFILES	:= $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRCFILES))

CC		:= g++
AR		:= ar
LIBS		:= -lSDL2 -lGLEW -lGL -lSDL2_ttf
CPPFLAGS	:= -Wall -Werror -std=c++17 -I $(INCDIR)

OUT		:= Decent-Engine.a

.PHONY: build clean

build: $(OBJFILES) | $(BINDIR) $(OUTDIR)
	@echo Building engine
	@$(AR) rcs $(BINDIR)$(OUT) $^
	@echo Liked obj files to $(BINDIR)$(OUT)
	@mv $(BINDIR)/$(OUT) $(OUTDIR)/$(OUT)
clean:
	@echo Cleaning temporary and built files
	@rm -rf $(OBJDIR)/*
	@rm -rf $(BINDIR)/*

$(OBJDIR)%.o : $(SRCDIR)%.cpp $(OBJDIR)
	@echo Compiling $< into $@
	$(CC) $(CPPFLAGS) $(LIBS) -c $< -o $@
	
$(OBJDIR):
	@mkdir -p $@
	
$(BINDIR):
	@mkdir -p $@
	
$(OUTDIR):
	@mkdir -p $@
