# CLog4All - cross-platform C++/C/Objective-C logger

**CLog4All** can be used in complex projects that have source code in C++, C and Objective-C.
It is cross-platform so it can be used on Windows (from Windows XP till Windows 10), macOS and Unix (tested on CentOS 7.5, Ubuntu 12.04 - see "Supported operation systems / compilers section" for details). It is thread-safe - you can safely do log from different threads.

## Getting Started
It is easy to integrate **CLog4All** into existing project or start new one using it. All you need is to ```#include"logger.h"``` to log from any source file. In order to set up path for log file (it should be an existing path) and set verbosity level call the following function (example for Windows): ```InitLoggerImpl( "c://myLog.log", eLogLevel::llDEBUG );```. First argument - is path for log file, the second one is the verbose level.
See ```main.cpp``` for example of starting with **CLog4All**.

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

After running this code on Windows the file "myLog.log" will be created in the path "C://". If not - check whether you have enough rights for creating file on this disk ;) ```InitLoggerImpl()``` will return ```1``` if initialization is successful and ```0``` otherwise.

After that, the log file will contain the following line:

```
[32112, 33152] 2019-04-11 19:56:28 <INFO>	[main.cpp:7]	This is a test log string
```
 
In square brackets the first number is process-id, the second one - is thread-id. These numbers can be used for analyzing logs from multithread applications.
In angle brackets the level of log message is presented. The current logging level is set via call to ```InitLoggerImpl()``` function mentioned above. Let's see the available logging levels a little bit closer.

### C++ logging syntax

There are several verbose levels that you can use in C++ (in order of increasing the severity level):

```
CPP_DISABLED( msg );
CPP_DEBUG( msg );
CPP_INFO( msg );
CPP_WARN( msg );
CPP_ERROR( msg );
```

You can add to the log message objects of any type that supports ```operator<<``` according to ```std::stringstream```  syntax.

```CPP_DISABLED``` call does not produce logg to the file. However, it can be useful if you wish to save log call in source code for later use.

For example:
```
#include"logger.h"

int main( int argc, char *argv[] )
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
 
 ### C/Objective-C logging syntax
 
 There are several verbose levels that are available in C/Objective-C code (in order of increasing the severity level):

```
C_DISABLED( msg );
C_DEBUG( msg );
C_INFO( msg );
C_WARN( msg );
C_ERROR( msg );
```
 
 You can add to the log message object of any type using ```printf```-like syntax.
 ```C_DISABLED``` call like ```CPP_DISABLED``` mentioned above does not perform log to the file.
 
For example:
```
#include"logger.h"

int main( int argc, char *argv[] )
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

The **CLog4All** project contains automated unit-tests that are used to prove its capabilities to successfully log from C++, C and Objective-C code.
These tests are implemented using Google Test framework (https://github.com/google/googletest).
You can find them in *"tests"* folder.

The **CLog4All** test project is supported on Windows using MinGW, CentOS and macOS.
On Windows using Visual Studio and on Ubuntu this test project is not supported.

In order to turn off test project generation set ```gen_test_project``` option in main ```CMakeList.txt``` to *OFF*

## Supported operation systems / compilers
**CLog4All** was tested on the following operation systems / compilers:
* Windows: MinGW 4.8.3, Visual Studio 2015
* CentOS 4.7: g++ 4.8.5
* Ubuntu 12.04: g++ 6.2.0
* macOS: Clang-1000.11.45.5

However it should work on other operation systems/compilers too, but it should be tested.

## How to use logger in my project?
Just add the following files to the project (located in *"logger"* folder):
* logger.h, logger.cpp
* logger_impl.h, logger_impl.cpp

If you are using Visual Studio than just add these files into the existing solution.

## Cautions

Logging using **CLog4All** from destructors of static or global objects has undefined behavior.
However if you really need it than you can compile **CLog4All** using ```DELETE_SINGLETON_OBJ_BY_OS``` compiler definition in order to grant operation system to free memory allocated by the process. You can enable this flag manually in source code or using ```CMakeLists.txt```.

Usually operation systems perform freeing resources that were managed by the finished process. However, for using this flag you should check your target system specification in order to avoid memory leak.

## Requirements

* A C++11-standard-compliant compiler
* [mingw-std-threads] (https://github.com/meganz/mingw-std-threads) -- for building on Windows using MinGW GCC compiler (already presented in the repo)
* [google-test] (https://github.com/google/googletest) - this library is used only for unit-testing

## Authors

* **Victor Yastrebov** - *Initial work* - [github](https://github.com/victor-yastrebov/clog4all)

## License

This project is licensed under the BSD2 License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Feel free to use it
* Any comments, proposals and merge requests are welcome