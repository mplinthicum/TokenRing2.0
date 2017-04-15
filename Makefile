all:
	gcc workstation.c Server.c Client.c -o workstation

clean:
	rm workstation
