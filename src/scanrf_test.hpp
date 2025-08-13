// # File Name:  ./scanpf_test.hpp
// # Build Date: Wed Nov  8 08:33:47 AM CST 2023
// # Version:    0.1

#ifndef _SCANPF_TEST_H
#define _SCANPF_TEST_H

#include <cppunit/Test.h>

class scanpfTest : public CppUnit::TestFixture
{
private:
    CPPUNIT_TEST_SUITE(scanpfTest);
    CPPUNIT_TEST(testNoOptions);
    CPPUNIT_TEST(testOptionHelp);
    CPPUNIT_TEST(testOptionHelpLong);
    CPPUNIT_TEST(testOptionVerbose);
    CPPUNIT_TEST(testOptionVerboseLong);
    CPPUNIT_TEST(testPrettyOption);
    CPPUNIT_TEST(testSingleOption);
    CPPUNIT_TEST(testIgnoreCaseOption);
    CPPUNIT_TEST(testOptionOption_IgnoreCase);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

    // agregate test functions
    void execute();
    void execute(int argc, char* argv[]);

protected:
    void testNoOptions();
    void testOptionHelp();
    void testOptionHelpLong();
    void testOptionVerbose();
    void testOptionVerboseLong();
    void testPrettyOption();
    void testSingleOption();
    void testIgnoreCaseOption();
    void testOptionOption_IgnoreCase();

private:
    int m_argc;
    char* m_argv[10];

};

#endif
