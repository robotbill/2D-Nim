all:	nim2d

nim2d:	nim2d.cpp matrix.cpp matrix.h nimber.cpp nimber.h findvalue.cpp\
		newgame.cpp hash.cpp hash.h
	g++ nim2d.cpp matrix.cpp nimber.cpp findvalue.cpp newgame.cpp\
	 hash.cpp -o nim2d
