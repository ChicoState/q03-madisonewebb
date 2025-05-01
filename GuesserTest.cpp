/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Tests for match function
TEST(GuesserTest, exact_match) {
    Guesser guesser("test");
    ASSERT_TRUE(guesser.match("test"));
}

TEST(GuesserTest, three_wrong_guesses_enable_lock) {
    Guesser guesser("test");
    guesser.match("tast"); // distance = 1
    guesser.match("tost"); // distance = 1
    guesser.match("tist"); // distance = 1
    ASSERT_FALSE(guesser.match("test")); // now locked
}

TEST(GuesserTest, detects_brute_force) {
    Guesser guesser("test");
    guesser.match("wrong"); // distance > 2, should lock
    ASSERT_FALSE(guesser.match("test"));
}

// Tests for remaining + match function
TEST(GuesserTest, wrong_guess_within_distance_decrements_remaining) {
    Guesser guesser("test");
    guesser.match("tast");  // 1 char different, distance = 1
    ASSERT_EQ(2, guesser.remaining());
}

TEST(GuesserTest, correct_guess_resets_remaining_to_three) {
    Guesser guesser("test");
    guesser.match("tost"); // wrong, 2 remaining
    guesser.match("test"); // correct
    ASSERT_EQ(3, guesser.remaining());
}

TEST(GuesserTest, initial_remaining_is_three) {
    Guesser guesser("test");
    ASSERT_EQ(3, guesser.remaining());
}