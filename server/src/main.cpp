#include <chrono>
#include <filesystem>
#include <map>
#include <random>
#include <grpc++/ext/proto_server_reflection_plugin.h>

// --------------- local includes --------------- //

#include <service/service.hpp>

#define CONFIG_FILE_PATH "~/.config/ner-ternary.config.json"

/*
	Run the Server
*/
void RunServer(nlohmann::json config) {
	if (config.size() < 1) {
		BOOST_LOG_TRIVIAL(warning) << "No user config supplied. Proceeding to start Server with default values.";
		config[0]["port"] = "50051";
	}

	// Add port and initiate service
	std::string server_address("[::]:" + config[0]["port"].get<std::string>());
	SearchTreeServiceImpl service;
	BOOST_LOG_TRIVIAL(info) << "Initiating Service and Building Default Tree.";
	service.Initialize();

	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();

	grpc::ServerBuilder builder;

	// Add insecure port
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we will communicate with clients
	// In this case it corresponds to a synchronous service.
	builder.RegisterService(&service);
	// Finally assemble the server
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	BOOST_LOG_TRIVIAL(info) << "Server listening on " << server_address;

	// Wait for the Server to shut down. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	server->Wait();
}

/*
	Read in and parse config to json object.
*/
nlohmann::json getConfig() {
	std::ifstream f(CONFIG_FILE_PATH);
	nlohmann::json config;
	if (!f.is_open()) {
		BOOST_LOG_TRIVIAL(error) << "Cannot open server configuration file from: " << CONFIG_FILE_PATH << ": " << strerror(errno);
		return config;
	}

	config = nlohmann::json::parse(f);
	return config;
}

/*
	MAIN
*/
int main(int argc, char* argv[]) {
	nlohmann::json config = getConfig();
	// Initialise variables and fill with input values

	RunServer(config);
	// Server - Start Server
	return 0;
}
