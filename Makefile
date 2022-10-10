###########################################################
#Makefile

#Auteur : Jean-Francois Brandon
##########################################################

########################
#Variables du MAKEFILE #
#######################"
#Compilateur
CC=gcc
IDIR=./include
ODIR=./obj
CDIR=./src
CFLAG=-g -Wall
EXE=./bin/arnoldi
BIN_DIR=./bin
LDFLAGS =-lm -llapack -lblas -L/usr/lib -fopenmp
LDLIBS=-MMD -MP -Iinclude -g


#Repertoires


SRC= $(wildcard $(CDIR)/*.c)
OBJ= $(patsubst $(CDIR)/%, $(ODIR)/%,$(SRC:%.c=%.o))
DEPS=$(OBJ:.o=.d)
DEPS_TEST= $(OBJ_TEST:.o=.d)
DEPS_MAIN= $(OBJ_MAIN:.o=.d)
EXEC= bin/arnoldi
LIBS_TEST=-I$(DEPS_TEST)
LIBS_MAIN=-I$(DEPS_MAIN)

##############
#MAKEFILE    #
##############

all: $(EXEC)


$(BIN_DIR):
	mkdir -p $@

$(ODIR)/%.o: $(CDIR)/%.c | $(ODIR)
	@mkdir -p $(dir $@)
	@echo "=============================="
	@echo "#Compiling $< #"
	$(CC) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

$(ODIR):
	mkdir -p $@

$(EXEC): $(OBJ) | $(BIN_DIR)
	@echo "============================="
	@echo "#Linking the target $@"
	@echo "============================="
	$(CC) $^  $(LDFLAGS) $(LDLIBS) -o $@
	@echo "_______ LINK FINISHED _______"


.PHONY: clean


clean:
	rm -rf $(ODIR)/*

mrproper:
	rm -rf $(ODIR)/* $(EXEC)


-include $(DEPS)
-include $(DEPS_TEST)
-include $(DEPS_MAIN)
