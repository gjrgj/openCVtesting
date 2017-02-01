all:
	g++ -ggdb `pkg-config --cflags --libs opencv` -stdlib=libc++ MVPposition.cpp -o test

clean:
	rm -f test