/**
 * @author <va.yastrebov>
 * @description
 * <pre>
 *    Implementation of logic for logging from C++/C/ObjectiveC code
 * </pre>
 *
 * @file logger_impl.h
 */

#pragma once

#include<string>

// MinGW 4.8.3 on Windows do not have support for std::mutex
#ifdef __MINGW32__
#include"mingw.mutex.h"
#else
#include<thread>
#include<mutex>
#include<stdarg.h> // for va_start / va_end
#endif

#include<fstream>

#ifdef _MSC_VER
#include<windows.h>   // for DWORD on Visual Studio compiler
#endif

#include"logger.h"

class LoggerImpl
{
public:
                 LoggerImpl();
                ~LoggerImpl();
                 // Disable copy constructor and assignment operator - we do not need them
                 LoggerImpl( const LoggerImpl& ) = delete;
                 LoggerImpl& operator=( const LoggerImpl& ) = delete;
          void   DoLog( const eLogLevel e_level, const char *loc_str, const char *buffer );
          bool   SetParams( const std::string &s_fname, const eLogLevel log_level );
     eLogLevel   GetVerboseLevel() const;

// Is used for unit-testing only
#ifdef UNIT_TEST_LOGGER_IMPL
   const char*   DoGetLatestLogMsg();
#endif

private:
      std::mutex   mutWriteToLog;
            FILE  *pLogFile;
     std::string   sLogName;
       eLogLevel   llVerboseLevel;
#ifdef _WIN32
     const DWORD   dwCurrentProcess;
#else
     const pid_t   pidCurrentProcess;
#endif

// Is used for unit-testing only
#ifdef UNIT_TEST_LOGGER_IMPL
    std::string   sLastLogMsg;
#endif

    std::string   FormatData( const eLogLevel e_level, const std::string &s_loc_str ) const;
    std::string   ExtractFileNameWithLineNo( const std::string &s_full_path ) const;
    std::string   AddProcessAndThreadInfo() const;
};