#include <catch2/catch_test_macros.hpp>
#include <lib/node.cpp>

TEST_CASE( "Strings exists in TernaryTree", "[node]" ) {
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
