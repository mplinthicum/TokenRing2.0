all:
	gcc workstation.c Server.c Client.c header.c -o workstation

clean:
	rm workstation
