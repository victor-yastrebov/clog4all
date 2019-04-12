/**
 *
 * @author <va.yastrebov>
 * @description
 * <pre>
 *    Unit-tests for logger
 * </pre>
 *
 * @class LoggerTest
 */

#include"gtest/gtest.h"

#include"logger_cpp_test_ground.h"
#include"logger.h"

extern "C" {
#include"logger_c_test_ground.h"
}

#ifdef __APPLE__
#include"logger_objc_test_ground.h"
#endif

class LoggerTest: public ::testing::Test
{};

TEST_F( LoggerTest, DoLog_FromNotConstFunctionThatIsDefinedInCpp_IsSuccesfullyCalled )
{
   const std::string s_etalon_msg = "Test from not const .cpp function";
   InitLoggerImpl( "dummy_path_to_file", eLogLevel::llDEBUG );

   LoggerCppTestGround ltg;
   ltg.LogFromNotConstCppFunction( s_etalon_msg );

   const std::string s_test_msg = ltg.GetLatestLogMsg();
   ASSERT_EQ( s_etalon_msg, s_test_msg );
}

TEST_F( LoggerTest, DoLog_FromConstFunctionThatIsDefinedInCpp_IsSuccesfullyCalled )
{
   const std::string s_etalon_msg = "Test from const .cpp function";
   InitLoggerImpl( "dummy_path_to_file", eLogLevel::llDEBUG );

   LoggerCppTestGround ltg;
   ltg.LogFromConstCppFunction( s_etalon_msg );

   const std::string s_test_msg = ltg.GetLatestLogMsg();
   ASSERT_EQ( s_etalon_msg, s_test_msg );
}

TEST_F( LoggerTest, DoLog_FromStaticFunctionThatIsDefinedInCpp_IsSuccesfullyCalled )
{
   const std::string s_etalon_msg = "Test from static .cpp function";
   InitLoggerImpl( "dummy_path_to_file", eLogLevel::llDEBUG );

   LoggerCppTestGround ltg;
   LoggerCppTestGround::LogFromStaticCppFunction( s_etalon_msg );

   const std::string s_test_msg = ltg.GetLatestLogMsg();
   ASSERT_EQ( s_etalon_msg, s_test_msg );
}

TEST_F( LoggerTest, DoLog_FromNotConstFunctionThatIsDefinedInHeader_IsSuccesfullyCalled )
{
   const std::string s_etalon_msg = "Test from not const .h function";
    InitLoggerImpl( "dummy_path_to_file", eLogLevel::llDEBUG );

   LoggerCppTestGround ltg;
   ltg.LogFromNotConstHeaderFunction( s_etalon_msg );

   const std::string s_test_msg = ltg.GetLatestLogMsg();
   ASSERT_EQ( s_etalon_msg, s_test_msg );
}

TEST_F( LoggerTest, DoLog_FromConstFunctionThatIsDefinedInHeader_IsSuccesfullyCalled )
{
   const std::string s_etalon_msg = "Test from const .h function";
    InitLoggerImpl( "dummy_path_to_file", eLogLevel::llDEBUG );

   LoggerCppTestGround ltg;
   ltg.LogFromConstHeaderFunction( s_etalon_msg );

   const std::string s_test_msg = ltg.GetLatestLogMsg();
   ASSERT_EQ( s_etalon_msg, s_test_msg );
}

TEST_F( LoggerTest, DoLog_FromFunctionThatIsDefinedInC_IsSuccesfullyCalled )
{
   const std::string s_etalon_msg = "Test from .c function";
   InitLoggerImpl( "dummy_path_to_file", eLogLevel::llDEBUG );

   LogFromCFunction( s_etalon_msg.c_str() );

   LoggerCppTestGround ltg;
   const std::string s_test_msg = ltg.GetLatestLogMsg();
   ASSERT_EQ( s_etalon_msg, s_test_msg );
}

#ifdef __APPLE__

TEST_F( LoggerTest, DoLog_FromFunctionThatIsDefinedInObjC_IsSuccesfullyCalled )
{
   const std::string s_etalon_msg = "Test from .objc function";
   InitLoggerImpl( "dummy_path_to_file", eLogLevel::llDEBUG );

   LogFromObjCFunction( s_etalon_msg.c_str() );

   LoggerCppTestGround ltg;
   const std::string s_test_msg = ltg.GetLatestLogMsg();
   ASSERT_EQ( s_etalon_msg, s_test_msg );
}

#endif