build:
	g++ -g -Wall -std=c++20 main.cpp -o a.out

ctest:
	rm -f tests.exe
	g++ -Wall -std=c++20 tests.cpp -o tests.exe

gtest:
	rm -f tests.exe
	g++ -g -std=c++2a -Wall tests.cpp -o tests.exe -lgtest -lgtest_main -lpthread

runtest:
	./tests.exe

clean:
	rm -f program.exe
	rm -f tests.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./program.exe
