expr: main.cpp
	g++ -o stock -std=gnu++98 -Wall -Werror -ggdb3 main.cpp

clean:
	rm -f *~ stock

