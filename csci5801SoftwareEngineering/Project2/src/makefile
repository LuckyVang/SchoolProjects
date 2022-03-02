objects = main.o helpers.o VotingSystem.o Candidate.o Ballot.o Party.o OPL.o IR.o PO.o

CFLAGS = -g -fsanitize=address -fno-omit-frame-pointer
CXXFLAGS = $(CFLAGS)

Aegis : $(objects)
	g++ $(CXXFLAGS) -o Aegis $(objects)

main.o :

helpers.o:

VotingSystem.o :

Candidate.o :

Ballot.o :

Party.o :

OPL.o :

IR.o :

PO.o :

.PHONY: clean
clean :
	rm Aegis $(objects)
