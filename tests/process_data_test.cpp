#include <catch2/catch_test_macros.hpp>
#include <lib/processData.cpp>

TEST_CASE( "Test tokenize", "[tokenize]" ) {
    std::string dummyString;

    SECTION ( "Testing with a standard sentence." ) {
        dummyString = "Testing the tokenize function.";
        std::vector<std::string> tokenized_string = tokenize(dummyString);

        REQUIRE( tokenized_string.size() == 4);

        // Check that the string is in lower case
        REQUIRE( tokenized_string[0] == "testing" );

        // Check that '.' has been stripped
        REQUIRE( tokenized_string[3] == "function");
    }

    SECTION ( "Testing with a more grammatically complex sentence." ) {
        dummyString = "This is a test with hyphenated-words AND !WEIRD pun//ctua||tion%$";
        std::vector<std::string> tokenized_string = tokenize(dummyString);

        REQUIRE( tokenized_string.size() == 9 );

        // Check that all words are lowercase and punctuation is stripped
        REQUIRE ( tokenized_string[6] == "and" );
        REQUIRE ( tokenized_string[7] == "weird" );
        // Currently chars such as '£' and '€' make it through tokenisation
        REQUIRE ( tokenized_string[8] == "punctuation" );

        // Check the hyphen has been preserved
        REQUIRE ( tokenized_string[5] == "hyphenated-words");
    }
}