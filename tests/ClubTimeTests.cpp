#include <gtest/gtest.h>
#include "ClubTime.h"
#include <sstream>
#include <stdexcept>

TEST(ClubTimeTest, DefaultConstructor) {
    ClubTime time = ClubTime();
    EXPECT_EQ(time.hours, 0);
    EXPECT_EQ(time.minutes, 0);
}

TEST(ClubTimeTest, StringConstructorValid) {
    ClubTime time("09:30");
    EXPECT_EQ(time.hours, 9);
    EXPECT_EQ(time.minutes, 30);

    ClubTime time2("23:59");
    EXPECT_EQ(time2.hours, 23);
    EXPECT_EQ(time2.minutes, 59);

    ClubTime time3("00:00");
    EXPECT_EQ(time3.hours, 0);
    EXPECT_EQ(time3.minutes, 0);
}

TEST(ClubTimeTest, StringConstructorInvalid) {
    EXPECT_THROW(ClubTime("09:"), std::invalid_argument);
    EXPECT_THROW(ClubTime(""), std::invalid_argument);
}


TEST(ClubTimeTest, LessThanOperator) {
    ClubTime t1("09:30");
    ClubTime t2("10:00");
    ClubTime t3("09:30");
    ClubTime t4("09:31");
    
    EXPECT_TRUE(t1 < t2);
    EXPECT_FALSE(t2 < t1);
    EXPECT_FALSE(t1 < t3);
    EXPECT_TRUE(t1 < t4);
}

TEST(ClubTimeTest, GreaterThanOrEqualOperator) {
    ClubTime t1("09:30");
    ClubTime t2("10:00");
    ClubTime t3("09:30");
    ClubTime t4("09:29");
    
    EXPECT_TRUE(t2 >= t1);
    EXPECT_TRUE(t1 >= t3);
    EXPECT_FALSE(t1 >= t2);
    EXPECT_TRUE(t1 >= t4);
}