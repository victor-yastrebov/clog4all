/**
 * @author <va.yastrebov>
 * @description
 * <pre>
 *    File for unit-testing of logging from C code
 * </pre>
 *
 * @file logger_c_test_ground
 */

#include"logger.h"

void LogFromCFunction( const char *p_msg )
{
   C_INFO( "%s", p_msg );
}