SRC=cpp-Generator.c
NAME=cppgen
FOLDER_SYSTEM=/usr/bin
FOLDER_LOCAL=$(HOME)/bin

.PHONY: all system local uninstall

all: system  

system:
	gcc -Wall $(SRC) -o $(NAME)
	mv -f $(NAME) $(FOLDER_SYSTEM)

local:
	gcc -Wall $(SRC) -o $(NAME)
	mv -f $(NAME) $(FOLDER_LOCAL)

uninstall:
	rm -f $(FOLDER_LOCAL)/$(NAME) $(FOLDER_SYSTEM)/$(NAME)

