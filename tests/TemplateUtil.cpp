#include <gtest/gtest.h>
#include "libEmbedded/TemplateUtil.h"
#include <typeinfo>
#include <string>

using libEmbedded::templateUtil::First;
using libEmbedded::templateUtil::Last;

TEST(TemplateUtilTest, LastOnSimpleSingleType)
{
    typedef int expectedType;
    typedef Last<int>::Type toTestType;
    auto equality = std::is_same<expectedType, toTestType>::value;
    ASSERT_TRUE(equality) << "Resulting type ID was: '" << std::string(typeid(toTestType).name()) << "' while expecting '" << std::string(typeid(expectedType).name()) << "'";
}

TEST(TemplateUtilTest, LastOnMultipleTypes)
{
    typedef std::string expectedType;
    typedef Last<int, short, bool, std::string>::Type toTestType;
    auto equality = std::is_same<expectedType, toTestType>::value;
    ASSERT_TRUE(equality) << "Resulting type ID was: '" << std::string(typeid(toTestType).name()) << "' while expecting '" << std::string(typeid(expectedType).name()) << "'";
}

TEST(TemplateUtilTest, FirstOnMultipleTypes)
{
    typedef int expectedType;
    typedef First<int, short, bool, std::string>::Type toTestType;
    auto equality = std::is_same<expectedType, toTestType>::value;
    ASSERT_TRUE(equality) << "Resulting type ID was: '" << std::string(typeid(toTestType).name()) << "' while expecting '" << std::string(typeid(expectedType).name()) << "'";
}

TEST(TemplateUtilTest, FirstOnSingleType)
{
    typedef std::string expectedType;
    typedef First<std::string>::Type toTestType;
    auto equality = std::is_same<expectedType, toTestType>::value;
    ASSERT_TRUE(equality) << "Resulting type ID was: '" << std::string(typeid(toTestType).name()) << "' while expecting '" << std::string(typeid(expectedType).name()) << "'";
}
