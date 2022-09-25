test:
	g++ src/channel.cpp src/epoll.cpp src/util.cpp src/InetAddress.cpp src/Socket.cpp epollsever.cpp -o sever && g++ client.cpp -o client 
clean:
	rm client && rm sever
