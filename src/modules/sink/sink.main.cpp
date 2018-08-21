#include <iostream>
#include <zmq/zmq.hpp>
#include <zmq/zhelpers.hpp>

int main() {
	std::cout << "Launching server" << std::endl;

	// Init & cleanup
	zmq::context_t context;

	// Sink socket
	zmq::socket_t sinkInputSocket{context, ZMQ_PULL};
	// Server socket
	zmq::socket_t sinkResultSocket{context, ZMQ_PUSH};

	// Setup sink
	{
		constexpr auto sinkInputAddress = "tcp://*:5558";
		sinkInputSocket.bind(sinkInputAddress);
		std::cout << "Sink running on " << sinkInputAddress << "." << std::endl;
	}

	// Connect to server
	{
		constexpr auto sinkOutputAddress = "tcp://*:5559";
		sinkResultSocket.bind(sinkOutputAddress);
		std::cout << "Connected to server at " << sinkOutputAddress << "." << std::endl;
	}

	for (int i = 0; i < 20; i++) {
		const std::string workerResult{s_recv(sinkInputSocket)};
		std::cout << "Result #" << i << " received from worker. Data received: " << workerResult << std::endl;
	}

	// Send result to server.
	const std::string result{"this-is-result-omg"};
	s_send(sinkResultSocket, result);

	std::cout << "Sink result: " << result << std::endl;
	std::cout << "Sink finished working and is closing. Goodbye." << std::endl;

	return EXIT_SUCCESS;
}
