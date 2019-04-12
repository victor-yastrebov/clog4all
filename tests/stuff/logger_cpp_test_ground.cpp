/**
 * @author <va.yastrebov>
 * @description
 * <pre>
 * <pre>
 *    File for unit-testing of logging from C++ code
 * </pre>
 *
 * @class LoggerCppTestGround
 */

#include"logger_cpp_test_ground.h"

void LoggerCppTestGround::LogFromNotConstCppFunction( const std::string& s_msg )
{
   CPP_INFO( s_msg );
}

void LoggerCppTestGround::LogFromConstCppFunction( const std::string& s_msg ) const
{
   CPP_INFO( s_msg );
}

void LoggerCppTestGround::LogFromStaticCppFunction( const std::string& s_msg )
{
   CPP_INFO( s_msg );
}

std::string LoggerCppTestGround::GetLatestLogMsg()
{
   const char *p_msg = GET_LATEST_LOG_MSG;
   // defend against nullptr
   const std::string s_msg =( nullptr == p_msg ) ? "" : p_msg;
   return s_msg;
}