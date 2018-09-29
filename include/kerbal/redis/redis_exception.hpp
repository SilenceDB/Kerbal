/*
 * redis_exception.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef INCLUDE_REDIS_REDIS_EXCEPTION_HPP_
#define INCLUDE_REDIS_REDIS_EXCEPTION_HPP_

#include <exception>
#include <sstream>

#include <kerbal/redis/redis_reply.hpp>

namespace kerbal
{
	namespace redis
	{
		/**
		 * @brief Base class for redis sub-library.
		 */
		class RedisException: public std::exception
		{
			protected:
				/// @brief Reason for current exception.
				const std::string reason;

			public:
				RedisException(const std::string & reason) :
						reason(reason)
				{
				}

				/**
				 * @brief Returns a C-style character string describing the general cause of the current exception.
				 */
				virtual const char * what() const noexcept
				{
					return reason.c_str();
				}
		};

		/**
		 * @brief Exception occurred when try to fetch a non-existent object.
		 */
		class RedisNilException: public RedisException
		{
			public:
				/// @brief The non-existent object's name that try to fetch.
				const std::string keyName;

				/**
				 * @brief Default constructor of RedisNilException.
				 * @param keyName The non-existent object's name that try to fetch.
				 */
				RedisNilException(const std::string & keyName) :
						RedisException("Try to get nil objects. Key name: " + keyName), keyName(keyName)
				{
				}
		};

		class RedisHgetNilException: public RedisNilException
		{
			public:
				const std::string fieldName;

				RedisHgetNilException(const std::string & keyName, const std::string & fieldName) :
					RedisNilException(keyName), fieldName(fieldName)
				{
				}
		};

		/**
		 * @brief Exception occurred when hiredis returns an unexpected reply type.
		 */
		class RedisUnexpectedCaseException: public RedisException
		{
			public:
				const std::string execute_command;

				RedisUnexpectedCaseException(RedisReplyType unexpectedType,
						const std::string & execute_command = "(unknown command)") :
						RedisException("redis returns an unexpected type: " + redisReplyTypeName(unexpectedType) + " when execute command: " + execute_command), execute_command(execute_command)
				{
				}
		};

		/**
		 * @brief Exception occurred when hiredis command execute failed.
		 */
		class RedisCommandExecuteFailedException: public RedisException
		{
			public:
				RedisCommandExecuteFailedException(const std::string & failedInfo) :
						RedisException("redis command execute failed : " + failedInfo)
				{
				}
		};
	}
}

#endif /* INCLUDE_REDIS_REDIS_EXCEPTION_HPP_ */
