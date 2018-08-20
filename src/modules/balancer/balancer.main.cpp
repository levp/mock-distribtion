#include <iostream>
#include <zmq.hpp>

int main(){
	// Create context and socket.
	zmq::context_t context;
	zmq::socket_t{context, ZMQ_PUSH};


	std::cout << "Server" << std::endl;
	return EXIT_SUCCESS;
}
