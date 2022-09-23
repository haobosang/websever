test:
	g++ util.cpp InetAddress.cpp Socket.cpp epollsever.cpp -o sever && g++ client.cpp -o client
