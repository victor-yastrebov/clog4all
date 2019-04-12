# CLog4All - CrossPlatfrom C++/C/ObjectiveC logger

**CLog4All** can be used in complex projects that have source code in C++, C and ObjectiveC.
It is cross-platfrom so it can be used on Windows (from Windows XP till Windows 10), Mac OS-X and Unix (tested on CentOS 7.5, Ubuntu 12.04 - see "Supported operation systems / compilers section" for details). It is thread-safe - you can safely do log from different threads.

## Getting Started
It is easy to integrate **CLog4All** into existing project or start new one using it. All you need is to ```#include"logger.h``` to log from any source file. In order to set up path for log file (it should be exising path) and set verbosity level call the the following function (example for windows): ```InitLoggerImpl( "c://myLog.log", eLogLevel::llDEBUG );```. First argument - is path for log file, the second one is the verbose level.
See ```main.cpp``` for example of starting with logger.

### Basic usage example

```
#include"logger.h"

int main( void )
{
   InitLoggerImpl( "c://myLog.log", eLogLevel::llDEBUG );

   CPP_INFO( "This is a test log string" );

   return 0;
}
```

After running this code on Windows the file "myLog.log" will be created in path "C://". If not - check whether you have enough rights for creating file on this disk ;)

After that the log file will contain the following line:

```
[32112, 33152] 2019-04-11 19:56:28 <INFO>	[main.cpp:7]	This is a test log string
```
 
The first number in square bracket is process-id, the second one - is thread-id. These numbers can be used for analysing logs from multithreaded applications.
In angle brackets the level of log message is presented. The current logging level is set via call to ```InitLoggerImpl()``` function mentioned above. Lets see the available logging levels closer.

### C++ logging syntax

There are several verbosing levels that you can use in C++ (in order of incresing the severity level):

```
CPP_DISABLED( msg );
CPP_DEBUG( msg );
CPP_INFO( msg );
CPP_WARN( msg );
CPP_ERROR( msg );
```

You can add to the log message objects of any type that supports ```operator<<``` according to ```std::stringstream```  syntax.

For example:
```
#include"logger.h"

int main(int argc, char *argv[])
{
   InitLoggerImpl( "c://myLog.log", eLogLevel::llDEBUG );

   std::string str( "Hello" );
   int var = 42;
   CPP_INFO( "Phrase is: " << str << ", and var is: " << var );

   return 0;
}
```
 It will produce the following output:
```
[17008, 6644] 19-03-18 18:12:10:930 <INFO>	[main.cpp:9]	Phrase is: Hello, and var is: 42
```
 
 ### C/ObjectiveC logging syntax
 
 There are several verbosing levels that you can use in C/ObjectiveC (in order of incresing the severity level):

```
C_DISABLED( msg );
C_DEBUG( msg );
C_INFO( msg );
C_WARN( msg );
C_ERROR( msg );
```
 
 You can add to the log message object of any type using ```printf```-like syntax.
 For example:
```
#include"logger.h"

int main(int argc, char *argv[])
{
   InitLoggerImpl( "c://myLog.log", eLogLevel::llDEBUG );

   char* str = "Hello";
   int var = 42;
   C_INFO( "Phrase is: %s, var is: %d",  str, var );

   return 0;
}
 
 ```
 It will produce the following output:
```
[17008, 6644] 19-03-18 18:12:10:930 <INFO>	[main.c:9]	Phrase is: Hello, and var is: 42
```
 
## Running the tests

The **CLog4All** project contains automated unit-tests that are used to prove its capabilities to successfully log from C++, C and ObjectiveC code.
The tests are created using Google Test framework (https://github.com/google/googletest)
You can find tests in *"tests"* folder

The Google Test project is supported on Windows using MinGW, CentOS and MacOS.
On Windows using Visual Studio and on Ubuntu Google Test project is not supported.

In order to turn off test project generation set ```gen_test_project``` option in main ```CMakeList.txt``` to *OFF*

## Supported operation systems / compilers
**CLog4All** was tested on the following operation systems / compilers
* Windows: MinGW 4.8.3, Visual Studio 2015
* CentOS 4.7: g++ 4.8.5
* Ubuntu 12.04: g++ 6.2.0
* MacOS X: Clang-1000.11.45.5

However it should work on other operation systems/compilers too, but it should be tested.

## How to use logger in my project?
Just add the following files to the project (located in *"logger"* folder):
* logger.h, logger.cpp
* logger_impl.h, logger_impl.cpp

If you are using Visual Studio than just add these files into existing solution.

## Cautions

Logging using **CLog4All** from destructors of static or global objects has undefined behaviour.
However if you really need it than you can compile using ```DELETE_SINGLETON_OBJ_BY_OS``` compile definition in order to grant operation system to free memory allocated by the process. You can enable this flag in manually in source code or using ```CMakeLists.txt```.

Usually operation systems perform freeing resources that were managed by the finished process. However for using this flag you should check your OS specification in oder to avoid memory leaks.

## Requirements

* A C++11-standard-compliant compiler
* [mingw-std-threads] (https://github.com/meganz/mingw-std-threads) -- for building on Windows using MinGW GCC compiler (already presented in the repo)
* [google-test] (https://github.com/google/googletest) - this library is used only for unit-testing

## Authors

* **Victor Yastrebov** - *Initial work* - [github](https://github.com/victor-yastrebov/clog4all)

## License

This project is licensed under the BSD2 License - see the [LICENSE](LICENSE.md) file for details

## Acknowledgments

* Feel free to use it
* Any comments, proposals and merge requests are wellcome