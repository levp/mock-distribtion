#include <iostream>
#include <thread>
#include <chrono>
#include <zmq/zmq.hpp>
#include <zmq/zhelpers.hpp>

int main() {
	std::cout << "Launching server" << std::endl;

	// Init & cleanup
	zmq::context_t context;

	// Server socket
	zmq::socket_t serverSocket{context, ZMQ_PUSH};
	// Sink socket
	zmq::socket_t sinkResultSocket{context, ZMQ_PULL};

	// Setup server
	{
		constexpr auto serverAddress = "tcp://*:5556";
		serverSocket.bind(serverAddress);
		std::cout << "Server running on " << serverAddress << "." << std::endl;
	}

	// Connect to sink
	{
		constexpr auto sinkResultAddress = "tcp://localhost:5559";
		sinkResultSocket.connect(sinkResultAddress);
		std::cout << "Connected to result at " << sinkResultAddress << "." << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));

	constexpr int taskCount = 20;
	std::chrono::time_point start = std::chrono::steady_clock::now();
	{
		for (int i = 0; i < taskCount; i++) {
			const std::string data{std::to_string(i)};
			std::cout << "Sending data #" << i << ": " << data << std::endl;
			s_send(serverSocket, data);
		}

		// Get result from sink
		std::cout << "Now waiting for result from sink." << std::endl;
		const std::string result{s_recv(sinkResultSocket)};
		std::cout << "Result: " << result << std::endl;
	}

	std::chrono::time_point end = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
	std::cout << "Total processing time: " << elapsedTime.count()
	          << "ms, average time: " << elapsedTime.count() / taskCount << "ms." << std::endl;

	// Print result
	std::cout << "Server finished and is closing. Goodbye." << std::endl;

	return EXIT_SUCCESS;
}
