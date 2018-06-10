/*
 * auto_free_reply.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef SRC_REDIS_AUTO_FREE_REPLY_HPP_
#define SRC_REDIS_AUTO_FREE_REPLY_HPP_

namespace kerbal
{
	namespace redis
	{
		/**
		 * @brief redis 执行结果类型
		 */
		enum class RedisReplyType
		{
			/** @brief 字符串 */
			STRING = REDIS_REPLY_STRING,

			/** @brief 数组，例如 mget 返回值 */
			ARRAY = REDIS_REPLY_ARRAY,

			/** @brief 数字类型 */
			INTEGER = REDIS_REPLY_INTEGER,

			/** @brief 空 */
			NIL = REDIS_REPLY_NIL,

			/** @brief 状态，例如set成功返回的‘OK’ */
			STATUS = REDIS_REPLY_STATUS,

			/** @brief 执行失败 */
			ERROR = REDIS_REPLY_ERROR

		};

		/**
		 * @brief 一个可以智能释放的 redis reply 指针
		 */
		class AutoFreeReply: public std::unique_ptr<redisReply, void (*)(redisReply *)>
		{
			private:
				static void redisReplyDealloctor(redisReply * reply_ptr)
				{
#if (TRACK_RESOURCE_FREE == true)
					std::cout << "free redisReply   " << reply_ptr << std::endl;
#endif
					freeReplyObject(reply_ptr);
				}

				using supper_t = std::unique_ptr<redisReply, void (*)(redisReply *)>;

			public:
				AutoFreeReply(redisReply * redis_reply = nullptr) :
						supper_t(redis_reply, redisReplyDealloctor)
				{
				}

				enum RedisReplyType replyType() const
				{
					return (RedisReplyType) this->get()->type;
				}
		};


		inline std::ostream& operator <<(std::ostream & out, RedisReplyType type)
		{
			using RedisReplyType = RedisReplyType;
			switch (type) {
				case RedisReplyType::STRING:
					return out << "STRING";
				case RedisReplyType::ARRAY:
					return out << "ARRAY";
				case RedisReplyType::INTEGER:
					return out << "INTEGER";
				case RedisReplyType::NIL:
					return out << "NIL";
				case RedisReplyType::STATUS:
					return out << "STATUS";
				case RedisReplyType::ERROR:
					return out << "ERROR";
				default:
					return out << "OTHER UNKNOWN";
			}
		}

	}
}



#endif /* SRC_REDIS_AUTO_FREE_REPLY_HPP_ */
