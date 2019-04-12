/**
 * @author <va.yastrebov>
 * @description
 * <pre>
 *    This file provides some basic stuff init, release and for calling log
 *    to file and getting verbose level
 * </pre>
 *
 * @file logger.cpp
 */

#include<string>

#include"logger.h"
#include"logger_impl.h"

#include<memory>

/**
 * Get singleton object of logger class that implements all logic of
 * logging
 */
LoggerImpl* LoggerImplInst()
{
#ifdef DELETE_LOGGER_SINGLETON_BY_OS
   static LoggerImpl* inst = new LoggerImpl();
   return inst;
#else
   static LoggerImpl logger_impl;
   return &logger_impl;
#endif
}

/**
 * @brief InitLoggerImpl - set path for log file and its verbosity level
 * @param p_fname_log_full - path for log file
 * @param log_level - verbosity level
 * @return 0 - on failure, 1 - on success
 */
int InitLoggerImpl( const char *p_fname_log_full, const eLogLevel log_level )
{
   const bool b_status_ok = LoggerImplInst()->SetParams(
      p_fname_log_full, log_level );

   const int n_status_ok = ( true == b_status_ok ) ? 1 : 0;
   return n_status_ok;
}

/**
 * @brief DoLog - log to file implementation
 * @param e_level - logging level
 * @param loc_str - log string location(filename:string no)
 * @param format - first named argument of function with variable number of
 * arguments
 */
void DoLog( const eLogLevel e_level, const char *loc_str, const char *format, ... )
{
   const size_t buf_size = 1024;
   char buffer[buf_size];
   va_list args;

   va_start( args, format );
   vsnprintf( buffer, buf_size, format, args );
   va_end( args );

   LoggerImplInst()->DoLog( e_level, loc_str, buffer );
}

/**
 * @brief DoGetVerboseLevel - get current logging verbose level
 */
eLogLevel DoGetVerboseLevel()
{
   return LoggerImplInst()->GetVerboseLevel();
}

#ifdef UNIT_TEST_LOGGER_IMPL
/*
 * Get last message that was "written" by logger
 * This function is used for unit-testing only
 */
const char *DoGetLatestLogMsg()
{
   return LoggerImplInst()->DoGetLatestLogMsg();
}
#endif

/**
 * Get singleton logger object that can be used in C++/C/ObjectiveC code
 */
LoggerBase* LoggerBaseInst()
{
#ifdef DELETE_LOGGER_SINGLETON_BY_OS
   static LoggerBase *LoggerBaseInst =
      new LoggerBase
#else
   static LoggerBase LoggerBaseInst =
#endif

   // we use designated initializer - for compatibility with C
   // Structs in C can not have any functions, including CTOR and DTOR
   {
      &DoLog
    , &DoGetVerboseLevel
#ifdef UNIT_TEST_LOGGER_IMPL
    , &DoGetLatestLogMsg
#endif
   };

#ifdef DELETE_LOGGER_SINGLETON_BY_OS
   return LoggerBaseInst;
#else
   return &LoggerBaseInst;
#endif
}