all:
	gcc tests.c Server.c Client.c -o tests

clean:
	rm tests
