#include <cli/cli.hpp>

// using namespace grpc;
// using namespace annotater;

// class SearchTreeClient {
//     public:
//         SearchTreeClient(std::shared_ptr<grpc::Channel> channel) : _stub{searchtree::SearchTree::NewStub(channel)} {}

//         void ReplaceTree(std::string terms) {
//             // Prepare request
//             searchtree::TempTreeRequest request;
//             request.set_tree_terms(terms);

//             // Container for the expected response
//             searchtree::TempTreeResponse response;

//             // Contedt for the client. It could be used to convey extra information
//             // to the server and/or tweak certain RPC behaviours.
//             grpc::ClientContext context;

//             // The Actual RPC
//             std::cout << "Submitting terms to build a temporary tree." << std::endl;
//             grpc::Status status = _stub->ReplaceTree(&context, request, &response);

//             // Check status of request/response
//             if (status.ok()) {
//                 std::cout << "RESPONSE: " << response.tree_id() << std::endl;
//             } else {
//                 std::cout << status.error_code() << ": " << status.error_message() << std::endl;
//             }
//         }

//         void InsertToTree(std::string terms) {
//             // Prepare request
//             searchtree::InsertTreeRequest request;
//             request.set_tree_terms(terms);

//             // Container for the expected response
//             searchtree::InsertTreeResponse response;

//             // Contedt for the client. It could be used to convey extra information
//             // to the server and/or tweak certain RPC behaviours.
//             grpc::ClientContext context;

//             // The Actual RPC
//             std::cout << "Inserting new terms to existing tree." << std::endl;
//             grpc::Status status = _stub->InsertToTree(&context, request, &response);

//             // Check status of request/response
//             if (status.ok()) {
//                 std::cout << "RESPONSE: " << response.ready() << std::endl;
//             } else {
//                 std::cout << status.error_code() << ": " << status.error_message() << std::endl;
//             }
//         }

//         void Annotate(std::string document, int ind) {
//             // Prepare request
//             searchtree::AnnotateRequest request;
//             request.set_test(ind);
//             request.set_document(document);

//             // Container for the response expected
//             searchtree::AnnotateResponse response;

//             // Contedt for the client. It could be used to convey extra information
//             // to the server and/or tweak certain RPC behaviours.
//             grpc::ClientContext context;

//             // The actual RPC
//             std::cout << "Submitting document (ID: " << request.test() << ") for annotating.\nContents: " << request.document() << std::endl;
//             grpc::Status status = _stub->Annotate(&context, request, &response);

//             if (status.ok()) {
//                 std::cout << "RESPONSE: " << response.annotations() << std::endl;
//             } else {
//                 std::cout << status.error_code() << ": " << status.error_message() << std::endl;
//             }
//         }

//     private:
//         std::unique_ptr<searchtree::SearchTree::Stub> _stub;
// };

int main(int argc, char** argv) {
    // std::string server_address{"localhost:50051"};
    // SearchTreeClient client{grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials())};
    // client.InsertToTree("Hello World");
    // client.Annotate("Hello World this document is all about cancer, specifically about prostate cancer.", 1);
    // client.ReplaceTree("term1, term2, term3");

    ProcessCommandLine(argc, argv);

    return 0;
}
