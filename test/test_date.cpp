#include <gtest/gtest.h>
#include "dateTime.h"

// Test the default constructor
TEST(DateTimeTest, DefaultConstructor) {
    DateTime dt;
    std::string result = dt.toString();
    // Check if the result is a non-empty string
    EXPECT_FALSE(result.empty());
    time_t now = time(nullptr);

    // Check if the time represented by DateTime is less than or equal to the current time
    EXPECT_LE(dt.getTime(), now);
}

// Test the constructor with a valid HTTP date string
TEST(DateTimeTest, ConstructorWithPattern1) {
    std::string http_date = "Sun, 06 Nov 1994 08:49:37 GMT";
    DateTime dt(http_date);
    std::string result = dt.toString();
    // Check if the result matches the expected string
    EXPECT_EQ(result, "Sun Nov 6 08:49:37 1994\n");
}

// Test the constructor with an invalid HTTP date string
TEST(DateTimeTest, ConstructorWithInvalidHttpDate) {
    std::string http_date = "Invalid Date";
    EXPECT_THROW(DateTime dt(http_date), DateTimeException);
}

// Test parsing a valid HTTP date string
TEST(DateTimeTest, ConstructorWithPattern2) {
    std::string http_date = "Sunday, 06-Nov-94 08:49:37 GMT";
    DateTime dt(http_date);
    
    std::string result = dt.toString();
    EXPECT_EQ(result, "Sun Nov 6 08:49:37 1994\n");
    // You can add more checks here to validate the parsed time
}

TEST(DateTimeTest, ConstructorWithPattern3) {
    std::string http_date = "Sun Nov  6 08:49:37 1994";
    DateTime dt(http_date);
    
    std::string result = dt.toString();
    EXPECT_EQ(result, "Sun Nov 6 08:49:37 1994\n");
    // You can add more checks here to validate the parsed time
}




