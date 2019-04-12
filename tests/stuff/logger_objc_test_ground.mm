/**
 * @author <va.yastrebov>
 * @description
 * <pre>
 *    File for unit-testing of logging from ObjectiveC code
 * </pre>
 *
 * @file logger_objc_test_ground
 */

#import<Foundation/Foundation.h>

#include"logger.h"

void LogFromObjCFunction( const char *p_msg )
{
   // just to be sure that it is an ObjectiveC file
   @autoreleasepool {
       NSLog( @"test from objective c file" );
   }

   C_INFO( "%s", p_msg );
}