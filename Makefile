GPP	=	g++

CFLAGS	=	-g	-Wall

FILES	=	solver.cpp	init.cpp	CDCL.cpp	launch.cpp	prop.cpp	fill_literal.cpp	unfill_literal.cpp	polarity.cpp	backtrack.cpp	conflict_solve.cpp	choosevariable.cpp

all:	solver

solver:	$(FILES)
	g++	$(FILES)	$(CFLAGS)	-o	bin/solver