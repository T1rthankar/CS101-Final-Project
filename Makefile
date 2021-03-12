all: lasso

lasso: MovingObject.o coin.o lasso.o score.o instructions.o bomb.o main.cpp
	s++ MovingObject.o coin.o lasso.o score.o instructions.o bomb.o main.cpp -o lasso

MovingObject.o: MovingObject.cpp MovingObject.h
	s++ -c MovingObject.cpp

coin.o: coin.h coin.cpp
	s++ -c coin.cpp

lasso.o: MovingObject.h lasso.cpp lasso.h
	s++ -c lasso.cpp

score.o: score.h score.cpp
	g++ -c score.cpp

instructions.o: instructions.h instructions.cpp
	s++ -c instructions.cpp

bomb.o: bomb.h bomb.cpp
	s++ -c bomb.cpp

.PHONY: clean
clean:
	rm *.o lasso
	rm instructions_test
	rm test
	rm .high_scores.txt
