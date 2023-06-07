#include <catch2/catch_test_macros.hpp>
#include <lib/node.cpp>
#include <fstream>


TEST_CASE( "Test InsertNode function with individual strings.", "[TernaryTree]" ) {
    tree::TernaryTree root;
    SECTION ( "Testing with valid words." ) {
        root.Insert("cat");
        root.Insert("cation");
        REQUIRE( root.Search("cat") == true );
        REQUIRE( root.Search("cation") == true );
    }

    SECTION ( "Testing with valid chars." ) {
        root.Insert("1234");
        root.Insert("!@£$");
        REQUIRE( root.Search("1234") == true );
        REQUIRE( root.Search("!@£$") == true );
    }
}

TEST_CASE( "Test buildTST function with Vector of strings", "[TernaryTree]" ) {
    std::vector<std::string> treeStrings {"cat", "catch", "cation", "dog"};
    std::vector<std::string> new_words {"new", "words", "test insertion"};

    tree::TernaryTree root;
    root.BuildFromVec(treeStrings);

    SECTION ("Testing that words do exist in the tree") {
        REQUIRE( root.Search("cat") == true );
        REQUIRE( root.Search("catch") == true );
        REQUIRE( root.Search("cation") == true );
        REQUIRE( root.Search("dog") == true );
    }

    SECTION ("Test that words do NOT exist in the tree"){
        REQUIRE( root.Search("fish") == false );
        REQUIRE( root.Search("fishch") == false );
        REQUIRE( root.Search("fishion") == false );
        REQUIRE( root.Search("fish") == false );
    }

    SECTION ("Test for utility functions") {
        REQUIRE( root.leaves() == 11);
        REQUIRE( root.size() == 4 );
        REQUIRE( root.depth() == 7);
    }

    // Testing for Insertion of a new vector of words
    root.InsertVec(new_words);
    SECTION ("Testing for new words inserted into tree") {
        // REQUIRE( root.Search("new") == true );
        REQUIRE( root.Search("words") == true );
        REQUIRE( root.Search("test insertion") == true );
    }
}

TEST_CASE ( "Test specifically for the LongestPrefix", "[TernaryTree]") {
    std::vector<std::string> treeStrings {"cat", "catch", "cation", "catheter", "catching", "dog"};
    tree::TernaryTree root;
    SECTION ("Testing longest prefix for true matches") {
        REQUIRE( root.LongestPrefix("cater", true) == "" );
    }

   root.BuildFromVec(treeStrings);
   SECTION ("Testing longest prefix for true matches") {
        REQUIRE( root.LongestPrefix("cater", true) == "cat" );
        REQUIRE( root.LongestPrefix("catholic", false) == "cath" );
    }
}

TEST_CASE ( "Test specifically for the CollectKeys", "[TernaryTree]") {
    std::vector<std::string> treeStrings {"cat", "catch", "cation", "catheter", "catching", "dog"};
    tree::TernaryTree root;

   root.BuildFromVec(treeStrings);
   SECTION ("Testing longest prefix for true matches") {
        std::vector<std::string> ans = root.CollectKeys("ca");
        REQUIRE( ans.size() == 5 );
        REQUIRE( root.LongestPrefix("catholic", false) == "cath" );
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
