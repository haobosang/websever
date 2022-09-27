test:
	g++ src/Eventloop.cpp src/Sever.cpp src/channel.cpp src/epoll.cpp src/util.cpp src/InetAddress.cpp src/Socket.cpp sever.cpp -o sever && g++ client.cpp -o client 
clean:
	rm client && rm sever
