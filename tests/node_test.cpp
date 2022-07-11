#include <catch2/catch_test_macros.hpp>
#include <lib/node.cpp>
#include <fstream>

TEST_CASE( "Test insertNode function with individual strings.", "[node]" ) {
    Node* root = nullptr;

    SECTION ( "Testing with valid words." ) {
        root = insertNode(root, "cat", 0);
        root = insertNode(root, "cation", 0);
        REQUIRE( searchTST(root, "cat") == true );
        REQUIRE( searchTST(root, "cation") == true );
    }

    SECTION ( "Testing with valid chars." ) {
        root = insertNode(root, "1234", 0);
        root = insertNode(root, "!@£$", 0);
        REQUIRE( searchTST(root, "1234") == true );
        REQUIRE( searchTST(root, "!@£$") == true );
    }
}

TEST_CASE( "Test buildTST function with Vector of strings", "[node]" ) {
    std::vector<std::string> treeStrings {"cat", "catch", "cation", "dog"};

    Node* root = buildTST(treeStrings);

    SECTION ("Testing that words do exist in the tree") {
        REQUIRE( searchTST(root, "cat") == true );
        REQUIRE( searchTST(root, "catch") == true );
        REQUIRE( searchTST(root, "cation") == true );
        REQUIRE( searchTST(root, "dog") == true );
    }

    SECTION ("Test that words do NOT exist in the tree"){
        REQUIRE( searchTST(root, "fish") == false );
        REQUIRE( searchTST(root, "fishch") == false );
        REQUIRE( searchTST(root, "fishion") == false );
        REQUIRE( searchTST(root, "fish") == false );
    }
}

TEST_CASE( "Test the tree functions", "[node]" ) {
    std::vector<std::string> treeStrings {"fish", "fishch", "fishion"};

    Node* root = buildTST(treeStrings);

    SECTION ("Testing that words do exist in the tree") {
        REQUIRE( maxDepth(root) == 8 );
    }
}

// TEST_CASE( "Test against Real Data", "[node]" ) {
//     std::fstream readTreeDataFile;
//     readTreeDataFile.open("./tests/out/treeData.txt", std::ios::in);
//     std::vector<std::string> diseases;
// 	std::string line;

//     while (!readTreeDataFile.eof()) {
// 		std::getline(readTreeDataFile, line);
// 		if (line.length() > 0)
// 			diseases.push_back(line);
// 	}
// 	readTreeDataFile.close();

//     Node* root = buildTST(diseases);

//     SECTION ("Testing that words do exist in the tree") {
//         REQUIRE( searchTST(root, "al") == false );
//         REQUIRE( searchTST(root, "gmp") == false );
//         REQUIRE( searchTST(root, "cancer") == true );
//     }
// }
