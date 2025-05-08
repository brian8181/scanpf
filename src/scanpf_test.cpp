// # File Name:  ./rx_test.cpp
// # Build Date: Wed Nov  8 08:33:47 AM CST 2023
// # Version:    0.1

#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>
#include <string.h>
#include "scanpf_test.hpp"

using namespace CppUnit;
using namespace std;

//HACK!
int parse_options(int argc, char* argv[]);

void RxTest::setUp()
{
}

void RxTest::tearDown()
{
}

void RxTest::testNoOptions()
{
    m_argv[1] = const_cast<char*>("a{3}b{2}c");
    m_argv[2] = const_cast<char*>("aaabbc");

    m_argv[1] = const_cast<char*>("a\\\\b");
    m_argv[2] = const_cast<char*>("a\\b");

    m_argv[1] = const_cast<char*>("a\\*b");
    m_argv[2] = const_cast<char*>("a*b");

    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);

    m_argv[1] = const_cast<char*>("a\\=b");
    m_argv[2] = const_cast<char*>("a=b");
    m_argv[1] = const_cast<char*>("a\\+b");
    m_argv[2] = const_cast<char*>("a+b");

    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);

    m_argv[1] = const_cast<char*>("a~b");
    m_argv[2] = const_cast<char*>("a~b");

    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void RxTest::testOptionHelp()
{
    m_argc = 2;
    m_argv[0] = const_cast<char*>("src/rx");
    m_argv[1] = const_cast<char*>("-h");

    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void RxTest::testOptionHelpLong()
{
    m_argc = 2;
    m_argv[0] = const_cast<char*>("src/rx");
    m_argv[1] = const_cast<char*>("--help");

    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void RxTest::testOptionVerbose()
{
    int i = 0;
    m_argv[i++] = const_cast<char*>("src/rx");
    m_argv[i++] = const_cast<char*>("-v");
    m_argv[i++] = const_cast<char*>("abc");
    m_argv[i++] = const_cast<char*>("abc");

    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void RxTest::testOptionVerboseLong()
{
    int i = 0;
    m_argv[i++] = const_cast<char*>("src/rx");
    m_argv[i++] = const_cast<char*>("--verbose");
    m_argv[i++] = const_cast<char*>("abc");
    m_argv[i++] = const_cast<char*>("abc");
    m_argc = i;
    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void RxTest::testPrettyOption()
{
    int i = 0;
    m_argv[i++] = const_cast<char*>("src/rx");
    m_argv[i++] = const_cast<char*>("abc");
    m_argv[i++] = const_cast<char*>("abc");
    m_argc = i;

    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void RxTest::testSingleOption()
{
    int i = 0;
    m_argv[i++] = const_cast<char*>("src/rx");
    m_argv[i++] = const_cast<char*>("abc");
    m_argv[i++] = const_cast<char*>("abc");
    m_argc = i;

    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void RxTest::testIgnoreCaseOption()
{
    int i = 0;
    m_argv[i++] = const_cast<char*>("src/rx");
    m_argv[i++] = const_cast<char*>("abc");
    m_argv[i++] = const_cast<char*>("abc");
    m_argc = i;

    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void RxTest::testOptionOption_IgnoreCase()
{
    int i = 0;
    m_argv[i++] = const_cast<char*>("src/rx");
    m_argv[i++] = const_cast<char*>("-o 'icase'");
    m_argv[i++] = const_cast<char*>("abc");
    m_argv[i++] = const_cast<char*>("abc");
    m_argc = i;

    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);

}

void RxTest::execute()
{
    // on head
    char** pstr = new char*;
    *pstr = (char*)"test";    // on the heap

    char** argv = new char*[1] {*pstr};
    //argv[0] = *pstr;

    execute(1, argv);

    delete pstr;
    delete [] argv;

    // on stack
    //char* argv_[3] {(char*)"./rx", (char*)"abc", (char*)"abc"};
}

void RxTest::execute(int argc, char* argv[])
{

}


CPPUNIT_TEST_SUITE_REGISTRATION( RxTest );

int main(int argc, char* argv[])
{
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry#include <stdio.h>
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);

    // output resint* pn = new int;ults in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();

    // Output XML for Jenkins CPPunit plugin
    ofstream xmlFileOut("cppRxTestResults.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}
