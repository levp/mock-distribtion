#include <iostream>
#include <thread>
#include <chrono>
#include <zmq/zmq.hpp>
#include <zmq/zhelpers.hpp>

[[noreturn]]
int main() {
	std::cout << "Launching worker" << std::endl;

	// Init & cleanup
	zmq::context_t context;

	// Balancer socket
	zmq::socket_t balancerSocket{context, ZMQ_PULL};
	// Sink socket
	zmq::socket_t sinkSocket{context, ZMQ_PUSH};

	// Connect to balancer
	{
		constexpr auto balancerAddress = "tcp://localhost:5557";
		balancerSocket.connect(balancerAddress);
		std::cout << "Connected to balancer at: " << balancerAddress << "." << std::endl;
	}

	// Connect to sink
	{
		constexpr auto sinkAddress = "tcp://localhost:5558";
		sinkSocket.connect(sinkAddress);
		std::cout << "Connected to sink at: " << sinkAddress << "." << std::endl;
	}

	std::cout << "Now listening for messages from the balancer." << std::endl;
	while (true) {
		// Pull data from the balancer
		const std::string data{s_recv(balancerSocket)};
		std::cout << "Received data from balancer: " << data << std::endl;

		// Make an important calculation.
		std::this_thread::sleep_for(std::chrono::milliseconds(250));

		// Send the result to the sink
		s_send(sinkSocket, "hmm?");
	}
}
