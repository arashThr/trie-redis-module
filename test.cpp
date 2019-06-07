#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "trie.h"

TEST_CASE("Trie search", "[trie]") {
    SECTION("Search for string in Trie - No more or less") {
        Trie trie;
        trie.insert("hi");
        REQUIRE(trie.search("hi") == true);
        REQUIRE(trie.search("h") == false);
        REQUIRE(trie.search("hii") == false);
    }

    SECTION("Uppercase will be replaced with lowercase") {
        Trie trie;
        trie.insert("H");
        REQUIRE(trie.search("h") == true);
        REQUIRE(trie.search("H") == true);
    }

    SECTION("Only alphabetic characters are acceptable") {
        Trie trie;
        trie.insert("09");
        REQUIRE(trie.search("09") == true);
    }

    SECTION("Dots are acceptable") {
        Trie trie;
        trie.insert("a.b");
        REQUIRE(trie.search("a.b") == true);
    }

    SECTION("Undefined characters throw exception") {
        Trie trie;
        REQUIRE_THROWS(trie.insert("-"));
    }

    SECTION("Remove a key from Trie") {
        Trie trie;
        trie.insert("h");
        REQUIRE(trie.search("h") == true);
        trie.remove("h");
        REQUIRE(trie.search("h") == false);
    }

    SECTION("After removal bigger and smaller keys must not be affected") {
        Trie trie;
        trie.insert("h");
        trie.insert("he");
        trie.insert("hey");
        trie.remove("he");
        REQUIRE(trie.search("h") == true);
        REQUIRE(trie.search("he") == false);
        REQUIRE(trie.search("hey") == true);
    }
}
