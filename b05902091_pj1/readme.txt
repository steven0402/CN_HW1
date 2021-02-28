client:
1.Fill in an addrinfo structure 'hints' as that will be used in the
getaddrinfo() function, which is called to get the information I needed when building socket.

2.When n > 0
	Connect to the socketfds that are created by socket() function and start to send a message to 
the server and start the clock.(In client, the message is defined as "test".)A while loop is running 
in order to check wheather the time difference exceeds (t). If it receive the message from server
before the time limit, print the server_ip and the rtt.If not, print timeout and start the send the 
next message. If it has already sent n messages to the server,it will start to send messages to the next server.
  When n = 0
	The two methods are similar. The only difference is that I will only send one message to eachserver. 
Once messages are received from all servers, it starts again from the first server.

server:
1.The getaddrinfo() part is same as above.

2.A socket of server is created. Then the sockfd is used to call bind() and listen() functions. The backlog 
in listen() is set as 10.

3.A while loop starts. In every loop it accepts a client and creat a child process to receive messages from client.
  If a message is received, send a message to client and print the ip and port of the client.(The message is defined
  as "ok".)

Compile:
Use the makefile in the folder.