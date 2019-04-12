#include <iostream>

#include"logger.h"

int main( void )
{
   std::cout << "Hello World!" << std::endl;

   InitLoggerImpl( "c://myLog.log", eLogLevel::llDEBUG );

   CPP_INFO( "This is a test log string" );

   return 0;
}
