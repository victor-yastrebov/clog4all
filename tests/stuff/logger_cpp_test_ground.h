#pragma once

/**
 * @author <va.yastrebov>
 * @description
 * <pre>
 *    File for unit-testing of logging from C++ code
 * </pre>
 *
 * @class LoggerCppTestGround
 */

#include<string>

#include"logger.h"

class LoggerCppTestGround
{
public:
   LoggerCppTestGround() = default;
  ~LoggerCppTestGround() = default;
   // Для безопасности запрещаем создавать копии объекта
   // т.к. в программе они нам точно не понадобятся
   LoggerCppTestGround( const LoggerCppTestGround& rhs ) = delete;
   LoggerCppTestGround( LoggerCppTestGround&& rhs ) = delete;
   LoggerCppTestGround& operator=( const LoggerCppTestGround& rhs ) = delete;

          void   LogFromNotConstCppFunction( const std::string& s_msg );
          void   LogFromConstCppFunction( const std::string& s_msg ) const;
   static void   LogFromStaticCppFunction( const std::string& s_msg );
   std::string   GetLatestLogMsg();

          void   LogFromConstHeaderFunction( const std::string& s_msg ) const
          {
             CPP_INFO( s_msg );
          }

          void   LogFromNotConstHeaderFunction( const std::string& s_msg )
          {
             CPP_INFO( s_msg );
          }

};