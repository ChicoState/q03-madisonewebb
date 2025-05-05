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

TEST(GuesserTest, exact_match) {
    Guesser guesser("test");
    ASSERT_TRUE(guesser.match("test"));
}

TEST(GuesserTest, three_wrong_guesses_enable_lock) {
    Guesser guesser("test");
    guesser.match("tast");
    guesser.match("tost");
    guesser.match("tist"); // 3rd wrong guesses, secret locked
    ASSERT_FALSE(guesser.match("test"));
}

TEST(GuesserTest, guess_after_zero_guesses_remaining) {
    Guesser guesser("test");
    guesser.match("tast");
    guesser.match("tost");
    guesser.match("tist"); // 0 guessest left
    ASSERT_FALSE(guesser.match("test"));
}

TEST(GuesserTest, detects_brute_force) {
    Guesser guesser("test");
    guesser.match("wrong"); // distance > 2, should lock
    ASSERT_FALSE(guesser.match("test"));
}

TEST(GuesserTest, check_remaining_after_one_failure) {
    Guesser guesser("test");
    guesser.match("tast");
    ASSERT_EQ(2, guesser.remaining());
}

TEST(GuesserTest, initial_remaining_is_three) {
    Guesser guesser("test");
    ASSERT_EQ(3, guesser.remaining());
}

TEST(GuesserTest, correct_guess_resets_remaining_to_three) {
    Guesser guesser("test");
    guesser.match("tost"); // wrong, 2 remaining
    guesser.match("test"); // correct
    ASSERT_EQ(3, guesser.remaining());
}

TEST(GuesserTest, remaining_decrements_even_when_locked) {
    Guesser guesser("test");
    guesser.match("bruteforce");
    ASSERT_EQ(2, guesser.remaining());
}