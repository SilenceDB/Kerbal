/**
 * @file       system.hpp
 * @brief
 * @date       2021-05-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONFIG_SYSTEM_HPP
#define KERBAL_CONFIG_SYSTEM_HPP

#include <kerbal/config/compiler_id.hpp>


#ifndef KERBAL_SYSTEM_UNKNOWN
#	define KERBAL_SYSTEM_UNKNOWN -1
#endif

#ifndef KERBAL_SYSTEM_FREESTANDING
#	define KERBAL_SYSTEM_FREESTANDING 0
#endif

#ifndef KERBAL_SYSTEM_WINDOWS
#	define KERBAL_SYSTEM_WINDOWS 1
#endif

#ifndef KERBAL_SYSTEM_LINUX
#	define KERBAL_SYSTEM_LINUX 2
#endif

#ifndef KERBAL_SYSTEM_APPLE
#	define KERBAL_SYSTEM_APPLE 3
#endif

#ifndef KERBAL_SYSTEM_ANDROID
#	define KERBAL_SYSTEM_ANDROID 4
#endif



#ifndef KERBAL_SYSTEM

#	include <kerbal/config/system/_0_freestanding.hpp>
#	include <kerbal/config/system/_1_windows.hpp>
#	include <kerbal/config/system/_2_linux.hpp>
#	include <kerbal/config/system/_3_apple.hpp>
#	include <kerbal/config/system/_4_android.hpp>


#	ifndef KERBAL_SYSTEM

#		define KERBAL_SYSTEM KERBAL_SYSTEM_UNKNOWN

#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#			pragma message ("Kerbal Warning: " "Unknown system")
#		else
#			warning "Kerbal Warning: " "Unknown system"
#		endif

#	endif

#endif


#endif // KERBAL_CONFIG_SYSTEM_HPP
