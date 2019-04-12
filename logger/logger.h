/**
 * @author <va.yastrebov>
 * @description
 * <pre>
 *    This header should be included into the source and header files of C++/C/ObjectiveC
 *    code in order to access logger stuff
 * </pre>
 *
 * @file logger.h
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_

// ANSI C does not know anythying about std::stringstream,
// but we use it in logging from C++ files
#ifdef __cplusplus
#include<sstream>
#endif

typedef enum
{
   llDEBUG = 0,
   llINFO = 1,
   llWARN = 2,
   llERROR = 3,
   llFATAL = 4,
   llNEVER = 5
} eLogLevel;

/*
 * Structures in C can not have functions, however can have pointers to functions
 * It means structures in C either can not be initialised using constructor
 */
struct LoggerBase
{
        void   ( *DoLogFuncPtr )( const eLogLevel level, const char *loc_str, const char *str, ... );
   eLogLevel   ( *DoGetVerboseLevelFuncPtr )();
#ifdef UNIT_TEST_LOGGER_IMPL
 const char*   ( *DoGetLatestLogMsgFuncPtr )();
#endif
};

int   InitLoggerImpl( const char *p_fname_log_full, const eLogLevel log_level );

#ifdef __cplusplus
extern "C" {
#endif
   // ANSI C do not have references, thus we have to use pointer for singleton class
   struct LoggerBase*  LoggerBaseInst();
#ifdef __cplusplus
}
#endif

// Remove this macro if you do not need to log anything
#define LOGS_ENABLE

// Set of instructions that is used for describing location in format (__FILE:__LINE__)
#define RH_LOC_LINEN(x) #x
#define RH_LOC_LINE(x) RH_LOC_LINEN(x)
#define RH_LOC_STR __FILE__ ":" RH_LOC_LINE(__LINE__)

#ifdef LOGS_ENABLE

// this macros is actually responsible for logging stuff
#define CPP_LOG_COMMON( level_param, msg ) \
try \
{ \
 if( (level_param) >= LoggerBaseInst()->DoGetVerboseLevelFuncPtr() ) \
 { \
    std::stringstream _ss; \
    _ss << msg; \
    LoggerBaseInst()->DoLogFuncPtr( (level_param), RH_LOC_STR, _ss.str().c_str() ); \
 } \
} \
catch( ... ) {}

#define C_LOG_COMMON( level_param, ... ) \
if( (level_param) >= LoggerBaseInst()->DoGetVerboseLevelFuncPtr() ) \
{ \
   LoggerBaseInst()->DoLogFuncPtr( (level_param), RH_LOC_STR, __VA_ARGS__ ); \
} \

// }}
#else

#define CPP_LOG_COMMON( unit, level, msg ) do {} while( 0 )
#define C_LOG_COMMON( level_param, msg ) do {} while( 0 )

#endif

// auxillary macroses for different log levels
#define CPP_DISABLED( msg ) do {} while( 0 )
#define CPP_DEBUG( msg ) CPP_LOG_COMMON( llDEBUG, msg )
#define CPP_INFO( msg ) CPP_LOG_COMMON( llINFO, msg )
#define CPP_WARN( msg ) CPP_LOG_COMMON( llWARN, msg )
#define CPP_ERROR( msg ) CPP_LOG_COMMON( llERROR, msg )

#define C_DISABLED( ... ) do {} while( 0 )
#define C_DEBUG( ... ) C_LOG_COMMON( llDEBUG, __VA_ARGS__ );
#define C_INFO( ... ) C_LOG_COMMON( llINFO, __VA_ARGS__ );
#define C_WARN( ... ) C_LOG_COMMON( llWARN, __VA_ARGS__ )
#define C_ERROR( ... ) C_LOG_COMMON( llERROR, __VA_ARGS__ )


#ifdef UNIT_TEST_LOGGER_IMPL
#define GET_LATEST_LOG_MSG (LoggerBaseInst()->DoGetLatestLogMsgFuncPtr());
#endif

#endif // _LOGGER_H_