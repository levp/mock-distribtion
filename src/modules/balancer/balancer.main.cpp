#include <iostream>
#include <zmq/zmq.hpp>
#include <zmq/zhelpers.hpp>

[[noreturn]]
int main() {
	std::cout << "Launching balancer" << std::endl;

	// Init & cleanup
	zmq::context_t context;

	// Create balancer socket
	zmq::socket_t balancerSocket{context, ZMQ_PUSH};
	// Create server socket
	zmq::socket_t serverSocket{context, ZMQ_PULL};

	// Setup balancer
	{
		constexpr auto balancerAddress = "tcp://*:5557";
		balancerSocket.bind(balancerAddress);
		std::cout << "Balancer running on: " << balancerAddress << "." << std::endl;
	}

	// Connect to server
	{
		constexpr auto serverAddress = "tcp://localhost:5556";
		serverSocket.connect(serverAddress);
		std::cout << "Connected to server at: " << serverAddress << "." << std::endl;
	}

	std::cout << "Now listening for messages from the server." << std::endl;
	while (true) {
		// Wait for message from server.
		const std::string message{s_recv(serverSocket)};
		std::cout << "Received data from server: " << message << std::endl;

		// Message received, now pass it on to a worker.
		s_send(balancerSocket, message);
	}
}
