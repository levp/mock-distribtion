#include <iostream>
#include <zmq.hpp>

int main() {
	// Create context and socket.
	zmq::context_t context;
	zmq::socket_t socket{context, ZMQ_PUSH};

	// Bind socket to address
	constexpr auto bindAddress = "tcp://*:5557";
	socket.bind(bindAddress);
	std::cout << "Server bound to address " << bindAddress << std::endl;

	std::cout << "Server" << std::endl;
	return EXIT_SUCCESS;
}
