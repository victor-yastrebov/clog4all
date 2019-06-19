/**
 * @author <va.yastrebov>
 * @description
 * <pre>
 *    Implementation of logic for logging from C++/C/ObjectiveC code
 * </pre>
 *
 * @file logger_impl.h
 */

#include"logger_impl.h"

#include<sstream>
#include<iostream>
#include<chrono>

#if defined(__linux__) || defined(__APPLE__)
#include<sys/types.h>
#include<unistd.h>
#else
#include<ctime> // for std::time_t
#endif

/**
 * CONSTRUCTOR
 */
LoggerImpl::LoggerImpl() :

   pLogFile( nullptr ),
#ifdef _WIN32
   dwCurrentProcess( GetCurrentProcessId() )
#else
   pidCurrentProcess( getpid() )
#endif
{

}

/**
 * DESTRUCTOR
 */
LoggerImpl::~LoggerImpl()
{
   fclose( pLogFile );
}

/**
 * Set logger params
 *
 * @param {const std::string} s_fname - log file name
 * @param {const eLogLevel} log_level - log level
 */
bool LoggerImpl::SetParams( const std::string &s_fname, const eLogLevel log_level )
{
   sLogName = s_fname;

   // set log level
   llVerboseLevel = log_level;

   std::lock_guard<std::mutex> lg( mutWriteToLog );
   pLogFile = fopen( s_fname.c_str(), "a+" );

   if( nullptr == pLogFile ) return false;

   return true;
}

/**
 * Write data to the file
 *
 * @param {const char *} loc_str - location of log call in source file
 * @param {const char *} unit_name - module name where the logging was called from
 * @param {const char *} msg - log message
 */
void LoggerImpl::DoLog( const eLogLevel e_level, const char *loc_str, const char *p_msg )
{
#ifdef UNIT_TEST_LOGGER_IMPL
   // silence the compiler warnings about unused variables
   (void)e_level;
   (void)loc_str;
   (void)p_msg;

   sLastLogMsg.assign( p_msg );
   return;
#else
   // several threads can try to write to the file simultaneously,
   // so prevent it
   std::lock_guard<std::mutex> lg( mutWriteToLog );

   std::string s( AddProcessAndThreadInfo() );
   if( pLogFile ) fwrite( s.c_str(), s.size(), 1, pLogFile );

   s.assign( FormatData( e_level, loc_str ) );
   if( pLogFile ) fwrite( s.c_str(), s.size(), 1, pLogFile );

   s.assign( p_msg, strlen( p_msg ) );
   s.push_back( '\n' );
   if( pLogFile ) fwrite( s.c_str(), s.size(), 1, pLogFile );

#endif // end of #ifdef UNIT_TEST_LOGGER_IMPL
}

/**
 * Add information about process and thread from which the logger was called
 */
std::string LoggerImpl::AddProcessAndThreadInfo() const
{
   // reset previously used stringstream
   stringStream.clear();
   stringStream.str( std::string() );

   stringStream << "[";

#ifdef WIN32
   stringStream << dwCurrentProcess;
#else
   stringStream << pidCurrentProcess;
#endif

   stringStream << ", " << std::this_thread::get_id() <<  "] ";

   return stringStream.str();
}

/**
 * Do formatting of parameters in string that will be written to the log-file 
 *
 * @param {const LoggerBase::eLogLevel} e_level - message log level
 * @param {const char* } loc_str - location information (file name and line number)
 * @returns {std::string} - formatted string
 */
std::string LoggerImpl::FormatData( const eLogLevel e_level, const std::string &s_loc_str ) const
{
   std::tm timeinfo;
   std::time_t timenow = time( nullptr );

   // get rid of possible race condition if using localtime().
   // and yes, in this implementation we acquire mutex before entering
   // this function :)
#ifdef WIN32
   localtime_s( &timeinfo, &timenow );
#else
   localtime_r( &timenow, &timeinfo );
#endif

   // get timestampt in following format: "YYYY-MM-DD HH:MM:SS"
   const size_t buf_size = 80;
   char buf_date_time[buf_size];
   strftime( buf_date_time, buf_size, "%Y-%m-%d %H:%M:%S", &timeinfo );

   // display log level enum in human-readable form in log file
   std::string s_level_str;
   switch( e_level )
   {
      case eLogLevel::llDEBUG:
         s_level_str = "DEBUG";
         break;
      case eLogLevel::llINFO:
         s_level_str = "INFO";
         break;
      case eLogLevel::llWARN:
         s_level_str = "WARN";
         break;
      case eLogLevel::llERROR:
         s_level_str = "ERROR";
         break;
      case eLogLevel::llFATAL:
         s_level_str = "FATAL";
         break;
      default:
         s_level_str = "UNKN";
         break;
   }

   const std::string s_fname_with_line_no =
      ExtractFileNameWithLineNo( s_loc_str );

   // reset previously used stringstream
   stringStream.clear();
   stringStream.str( std::string() );

   stringStream << buf_date_time << " ";
   stringStream << "<" << s_level_str << ">\t";
   stringStream << "[" << s_fname_with_line_no << "]\t";

   return stringStream.str();
}

/**
 * Get the file name and line number from full path
 * Example of processing line:
 * C:\path\to\file\main.cpp:64
 */
std::string LoggerImpl::ExtractFileNameWithLineNo( const std::string &s_full_path ) const
{
   const std::string sep( "/\\" );
   const size_t fname_start_pos = s_full_path.find_last_of( sep );

   if( fname_start_pos != std::string::npos )
   {
      return( s_full_path.substr( fname_start_pos + 1, s_full_path.length() - fname_start_pos ) );
   }

   return std::string();
}

/**
 * Get current verbose level
 */
eLogLevel LoggerImpl::GetVerboseLevel() const
{
   return llVerboseLevel;
}

#ifdef UNIT_TEST_LOGGER_IMPL
/**
 * Get the last message that was written by the logger
 */
const char* LoggerImpl::DoGetLatestLogMsg()
{
   return sLastLogMsg.c_str();
}
#endif