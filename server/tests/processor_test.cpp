#include <catch2/catch_test_macros.hpp>
#include <lib/processor.hpp>
#include <fstream>

TEST_CASE( "Test for the processor class.", "[Processor]" ) {
    // Build a tree from a vector of strings
    std::vector<std::string> treeStrings {"cat", "catch", "cation", "dog"};
    std::string to_annotate = "This string is about how a cat can catch a dog that chases a cation.";

    tree::TernaryTree root;
    root.BuildFromVec(treeStrings);

    process::Processor pro(&root);

    SECTION ("Test that the annotations are returned as expected.") {
        REQUIRE( pro.longest_substring() == root.depth() );
        nlohmann::json temp = pro.Annotate(to_annotate, 0);
        REQUIRE( temp["keys"]["cat"][0] == 1);
    }
}
