#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

#include "binary.hpp"

namespace lab2 {
namespace {

TEST(BinaryTest, DefaultConstructor) {
    Binary bin;
    EXPECT_EQ(bin.GetSize(), 0);
}

TEST(BinaryTest, ConstructorWithSize) {
    Binary bin(5, '1');
    EXPECT_EQ(bin.GetSize(), 5);
    EXPECT_EQ(bin.ToString(), "11111");
}

TEST(BinaryTest, ConstructorWithSizeDefaultZero) {
    Binary bin(4);
    EXPECT_EQ(bin.GetSize(), 4);
    EXPECT_EQ(bin.ToString(), "0000");
}

TEST(BinaryTest, ConstructorFromInitializerList) {
    Binary bin({'1', '0', '1', '0'});
    EXPECT_EQ(bin.ToString(), "1010");
}

TEST(BinaryTest, ConstructorFromString) {
    Binary bin("1101");
    EXPECT_EQ(bin.GetSize(), 4);
    EXPECT_EQ(bin.ToString(), "1101");
}

TEST(BinaryTest, ConstructorFromStringInvalidChar) {
    EXPECT_THROW(Binary bin("102"), std::invalid_argument);
    EXPECT_THROW(Binary bin("abc"), std::invalid_argument);
}

TEST(BinaryTest, ConstructorFromEmptyString) {
    EXPECT_THROW(Binary bin(""), std::invalid_argument);
}

TEST(BinaryTest, CopyConstructor) {
    Binary bin1("1010");
    Binary bin2(bin1);
    EXPECT_EQ(bin2.ToString(), "1010");
    EXPECT_TRUE(bin1.IsEqual(bin2));
}

TEST(BinaryTest, MoveConstructor) {
    Binary bin1("1010");
    Binary bin2(std::move(bin1));
    EXPECT_EQ(bin2.ToString(), "1010");
}

TEST(BinaryTest, AdditionSimple) {
    Binary bin1("101");
    Binary bin2("11");
    Binary result = bin1.Add(bin2);
    EXPECT_EQ(result.ToString(), "1000");
}

TEST(BinaryTest, AdditionWithCarry) {
    Binary bin1("111");
    Binary bin2("1");
    Binary result = bin1.Add(bin2);
    EXPECT_EQ(result.ToString(), "1000");
}

TEST(BinaryTest, AdditionZero) {
    Binary bin1("1010");
    Binary bin2("0");
    Binary result = bin1.Add(bin2);
    EXPECT_EQ(result.ToString(), "1010");
}

TEST(BinaryTest, AdditionDifferentSizes) {
    Binary bin1("1111");
    Binary bin2("1");
    Binary result = bin1.Add(bin2);
    EXPECT_EQ(result.ToString(), "10000");
}

TEST(BinaryTest, SubtractionSimple) {
    Binary bin1("1000");
    Binary bin2("11");
    Binary result = bin1.Subtract(bin2);
    EXPECT_EQ(result.ToString(), "101");
}

TEST(BinaryTest, SubtractionWithBorrow) {
    Binary bin1("1010");
    Binary bin2("11");
    Binary result = bin1.Subtract(bin2);
    EXPECT_EQ(result.ToString(), "111");
}

TEST(BinaryTest, SubtractionEqualNumbers) {
    Binary bin1("1010");
    Binary bin2("1010");
    Binary result = bin1.Subtract(bin2);
    EXPECT_EQ(result.ToString(), "0");
}

TEST(BinaryTest, SubtractionNegativeResult) {
    Binary bin1("10");
    Binary bin2("101");
    EXPECT_THROW(bin1.Subtract(bin2), std::invalid_argument);
}

TEST(BinaryTest, IsEqualTrue) {
    Binary bin1("1010");
    Binary bin2("1010");
    EXPECT_TRUE(bin1.IsEqual(bin2));
}

TEST(BinaryTest, IsEqualFalse) {
    Binary bin1("1010");
    Binary bin2("1011");
    EXPECT_FALSE(bin1.IsEqual(bin2));
}

TEST(BinaryTest, IsGreaterTrue) {
    Binary bin1("1010");
    Binary bin2("101");
    EXPECT_TRUE(bin1.IsGreater(bin2));
}

TEST(BinaryTest, IsGreaterFalse) {
    Binary bin1("101");
    Binary bin2("1010");
    EXPECT_FALSE(bin1.IsGreater(bin2));
}

TEST(BinaryTest, IsGreaterEqual) {
    Binary bin1("1010");
    Binary bin2("1010");
    EXPECT_FALSE(bin1.IsGreater(bin2));
}

TEST(BinaryTest, IsLessTrue) {
    Binary bin1("101");
    Binary bin2("1010");
    EXPECT_TRUE(bin1.IsLess(bin2));
}

TEST(BinaryTest, IsLessFalse) {
    Binary bin1("1010");
    Binary bin2("101");
    EXPECT_FALSE(bin1.IsLess(bin2));
}

TEST(BinaryTest, IsLessEqual) {
    Binary bin1("1010");
    Binary bin2("1010");
    EXPECT_FALSE(bin1.IsLess(bin2));
}

TEST(BinaryTest, CopyMethod) {
    Binary bin1("1010");
    Binary bin2 = bin1.Copy();
    EXPECT_TRUE(bin1.IsEqual(bin2));
    EXPECT_EQ(bin2.ToString(), "1010");
}

TEST(BinaryTest, PrintOutput) {
    Binary bin("1010");
    std::ostringstream oss;
    bin.Print(oss);
    EXPECT_EQ(oss.str(), "1010");
}

TEST(BinaryTest, ImmutabilityAfterAdd) {
    Binary bin1("101");
    Binary bin2("11");
    std::string originalBin1 = bin1.ToString();
    std::string originalBin2 = bin2.ToString();
    Binary result = bin1.Add(bin2);
    EXPECT_EQ(bin1.ToString(), originalBin1);
    EXPECT_EQ(bin2.ToString(), originalBin2);
}

TEST(BinaryTest, ImmutabilityAfterSubtract) {
    Binary bin1("1010");
    Binary bin2("11");
    std::string originalBin1 = bin1.ToString();
    std::string originalBin2 = bin2.ToString();
    Binary result = bin1.Subtract(bin2);
    EXPECT_EQ(bin1.ToString(), originalBin1);
    EXPECT_EQ(bin2.ToString(), originalBin2);
}

TEST(BinaryTest, ComplexArithmeticSequence) {
    Binary bin1("1111");
    Binary bin2("1");
    Binary bin3("1010");
    Binary result = bin1.Add(bin2);
    result = result.Subtract(bin3);
    EXPECT_EQ(result.ToString(), "110");
}

TEST(BinaryTest, LargeNumbers) {
    Binary bin1("11111111");
    Binary bin2("1");
    Binary result = bin1.Add(bin2);
    EXPECT_EQ(result.ToString(), "100000000");
}

}  // namespace
}  // namespace lab2

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
