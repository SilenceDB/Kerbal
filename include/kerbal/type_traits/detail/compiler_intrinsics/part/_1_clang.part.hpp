/**
 * @file       _1_clang.part.hpp
 * @brief
 * @date       2021-06-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_PART__1_CLANG_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_PART__1_CLANG_PART_HPP

#include <kerbal/config/compiler_private.hpp>
#include <kerbal/config/cxx_stdlib.hpp>


// https://clang.llvm.org/docs/LanguageExtensions.html#type-trait-primitives

#ifndef KERBAL_HAS_INTRINSIC_IS_ABSTRACT_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_abstract)
#		define KERBAL_INTRINSIC_IS_ABSTRACT(T) __is_abstract(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_abstract)
#		define KERBAL_INTRINSIC_IS_ABSTRACT(T) __is_abstract(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_ABSTRACT
#	define KERBAL_HAS_INTRINSIC_IS_ABSTRACT_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_AGGREGATE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_aggregate)
#		define KERBAL_INTRINSIC_IS_AGGREGATE(T) __is_aggregate(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_AGGREGATE
#	define KERBAL_HAS_INTRINSIC_IS_AGGREGATE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_ARITHMETIC_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_arithmetic)
#		define KERBAL_INTRINSIC_IS_ARITHMETIC(T) __is_arithmetic(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_ARITHMETIC
#	define KERBAL_HAS_INTRINSIC_IS_ARITHMETIC_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_ARRAY_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_array)
#		define KERBAL_INTRINSIC_IS_ARRAY(T) __is_array(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_ARRAY
#	define KERBAL_HAS_INTRINSIC_IS_ARRAY_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_ASSIGNABLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_assignable)
#		define KERBAL_INTRINSIC_IS_ASSIGNABLE(T, U) __is_assignable(T, U)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_ASSIGNABLE
#	define KERBAL_HAS_INTRINSIC_IS_ASSIGNABLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_BASE_OF_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_base_of)
#		define KERBAL_INTRINSIC_IS_BASE_OF(BASE, DERIVED) __is_base_of(BASE, DERIVED)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_base_of)
#		define KERBAL_INTRINSIC_IS_BASE_OF(BASE, DERIVED) __is_base_of(BASE, DERIVED)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_BASE_OF
#	define KERBAL_HAS_INTRINSIC_IS_BASE_OF_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_BOUNDED_ARRAY_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_bounded_array)
#		define KERBAL_INTRINSIC_IS_BOUNDED_ARRAY(T) __is_bounded_array(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_BOUNDED_ARRAY
#	define KERBAL_HAS_INTRINSIC_IS_BOUNDED_ARRAY_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_CLASS_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_class)
#		define KERBAL_INTRINSIC_IS_CLASS(T) __is_class(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_class)
#		define KERBAL_INTRINSIC_IS_CLASS(T) __is_class(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_CLASS
#	define KERBAL_HAS_INTRINSIC_IS_CLASS_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_COMPLETE_TYPE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_complete_type)
#		define KERBAL_INTRINSIC_IS_COMPLETE_TYPE(T) __is_complete_type(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_COMPLETE_TYPE
#	define KERBAL_HAS_INTRINSIC_IS_COMPLETE_TYPE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_COMPOUND_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_compound)
#		define KERBAL_INTRINSIC_IS_COMPOUND(T) __is_compound(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_COMPOUND
#	define KERBAL_HAS_INTRINSIC_IS_COMPOUND_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_CONST_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_const)
#		define KERBAL_INTRINSIC_IS_CONST(T) __is_const(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_CONST
#	define KERBAL_HAS_INTRINSIC_IS_CONST_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_CONSTRUCTIBLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_constructible)
#		define KERBAL_INTRINSIC_IS_CONSTRUCTIBLE(...) __is_constructible(__VA_ARGS__)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_constructible)
#		define KERBAL_INTRINSIC_IS_CONSTRUCTIBLE(...) __is_constructible(__VA_ARGS__)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_CONSTRUCTIBLE
#	define KERBAL_HAS_INTRINSIC_IS_CONSTRUCTIBLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_CONVERTIBLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_convertible)
#		define KERBAL_INTRINSIC_IS_CONVERTIBLE(FROM, TO) __is_convertible(FROM, TO)
#	elif KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_convertible_to)
#		define KERBAL_INTRINSIC_IS_CONVERTIBLE(FROM, TO) __is_convertible_to(FROM, TO)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_convertible_to)
#		define KERBAL_INTRINSIC_IS_CONVERTIBLE(FROM, TO) __is_convertible_to(FROM, TO)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_CONVERTIBLE
#	define KERBAL_HAS_INTRINSIC_IS_CONVERTIBLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_DESTRUCTIBLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_destructible)
#		define KERBAL_INTRINSIC_IS_DESTRUCTIBLE(T) __is_destructible(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_destructible)
#		define KERBAL_INTRINSIC_IS_DESTRUCTIBLE(T) __is_destructible(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_DESTRUCTIBLE
#	define KERBAL_HAS_INTRINSIC_IS_DESTRUCTIBLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_EMPTY_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_empty)
#		define KERBAL_INTRINSIC_IS_EMPTY(T) __is_empty(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_empty)
#		define KERBAL_INTRINSIC_IS_EMPTY(T) __is_empty(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_EMPTY
#	define KERBAL_HAS_INTRINSIC_IS_EMPTY_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_ENUM_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_enum)
#		define KERBAL_INTRINSIC_IS_ENUM(T) __is_enum(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_enum)
#		define KERBAL_INTRINSIC_IS_ENUM(T) __is_enum(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_ENUM
#	define KERBAL_HAS_INTRINSIC_IS_ENUM_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_FINAL_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_final)
#		define KERBAL_INTRINSIC_IS_FINAL(T) __is_final(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_final) // >= 3.1
#		define KERBAL_INTRINSIC_IS_FINAL(T) __is_final(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_FINAL
#	define KERBAL_HAS_INTRINSIC_IS_FINAL_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_FLOATING_POINT_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_floating_point)
#		define KERBAL_INTRINSIC_IS_FLOATING_POINT(T) __is_floating_point(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_FLOATING_POINT
#	define KERBAL_HAS_INTRINSIC_IS_FLOATING_POINT_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_FUNCTION_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_function)
#		define KERBAL_INTRINSIC_IS_FUNCTION(T) __is_function(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_FUNCTION
#	define KERBAL_HAS_INTRINSIC_IS_FUNCTION_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_FUNDAMENTAL_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_fundamental)
#		define KERBAL_INTRINSIC_IS_FUNDAMENTAL(T) __is_fundamental(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_FUNDAMENTAL
#	define KERBAL_HAS_INTRINSIC_IS_FUNDAMENTAL_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_INTEGRAL_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_integral)
#		define KERBAL_INTRINSIC_IS_INTEGRAL(T) __is_integral(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_INTEGRAL
#	define KERBAL_HAS_INTRINSIC_IS_INTEGRAL_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_LITERAL_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_literal)
#		define KERBAL_INTRINSIC_IS_LITERAL(T) __is_literal(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_literal)
#		define KERBAL_INTRINSIC_IS_LITERAL(T) __is_literal(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_literal_type)
#		define KERBAL_INTRINSIC_IS_LITERAL(T) __is_literal_type(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_LITERAL
#	define KERBAL_HAS_INTRINSIC_IS_LITERAL_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_LVALUE_REFERENCE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_lvalue_reference)
#		define KERBAL_INTRINSIC_IS_LVALUE_REFERENCE(T) __is_lvalue_reference(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_LVALUE_REFERENCE
#	define KERBAL_HAS_INTRINSIC_IS_LVALUE_REFERENCE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_MEMBER_OBJECT_POINTER_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_member_object_pointer)
#		define KERBAL_INTRINSIC_IS_MEMBER_OBJECT_POINTER(T) __is_member_object_pointer(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_MEMBER_OBJECT_POINTER
#	define KERBAL_HAS_INTRINSIC_IS_MEMBER_OBJECT_POINTER_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_MEMBER_FUNCTION_POINTER_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_member_function_pointer)
#		define KERBAL_INTRINSIC_IS_MEMBER_FUNCTION_POINTER(T) __is_member_function_pointer(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_MEMBER_FUNCTION_POINTER
#	define KERBAL_HAS_INTRINSIC_IS_MEMBER_FUNCTION_POINTER_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_MEMBER_POINTER_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_member_pointer)
#		define KERBAL_INTRINSIC_IS_MEMBER_POINTER(T) __is_member_pointer(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_MEMBER_POINTER
#	define KERBAL_HAS_INTRINSIC_IS_MEMBER_POINTER_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_NOTHROW_ASSIGNABLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_nothrow_assignable)
#		define KERBAL_INTRINSIC_IS_NOTHROW_ASSIGNABLE(T, U) __is_nothrow_assignable(T, U)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_NOTHROW_ASSIGNABLE
#	define KERBAL_HAS_INTRINSIC_IS_NOTHROW_ASSIGNABLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_NOTHROW_CONSTRUCTIBLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_nothrow_constructible)
#		define KERBAL_INTRINSIC_IS_NOTHROW_CONSTRUCTIBLE(...) __is_nothrow_constructible(__VA_ARGS__)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_NOTHROW_CONSTRUCTIBLE
#	define KERBAL_HAS_INTRINSIC_IS_NOTHROW_CONSTRUCTIBLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_NOTHROW_DESTRUCTIBLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_nothrow_destructible)
#		define KERBAL_INTRINSIC_IS_NOTHROW_DESTRUCTIBLE(T) __is_nothrow_destructible(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_NOTHROW_DESTRUCTIBLE
#	define KERBAL_HAS_INTRINSIC_IS_NOTHROW_DESTRUCTIBLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_NULLPTR_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_nullptr)
#		define KERBAL_INTRINSIC_IS_NULLPTR(T) __is_nullptr(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_NULLPTR
#	define KERBAL_HAS_INTRINSIC_IS_NULLPTR_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_OBJECT_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_object)
#		define KERBAL_INTRINSIC_IS_OBJECT(T) __is_object(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_OBJECT
#	define KERBAL_HAS_INTRINSIC_IS_OBJECT_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_POD_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_pod)
#		define KERBAL_INTRINSIC_IS_POD(T) __is_pod(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_pod)
#		define KERBAL_INTRINSIC_IS_POD(T) __is_pod(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_POD
#	define KERBAL_HAS_INTRINSIC_IS_POD_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_POINTER_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_pointer)
#		define KERBAL_INTRINSIC_IS_POINTER(T) __is_pointer(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_POINTER
#	define KERBAL_HAS_INTRINSIC_IS_POINTER_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_POLYMORPHIC_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_polymorphic)
#		define KERBAL_INTRINSIC_IS_POLYMORPHIC(T) __is_polymorphic(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_polymorphic)
#		define KERBAL_INTRINSIC_IS_POLYMORPHIC(T) __is_polymorphic(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_POLYMORPHIC
#	define KERBAL_HAS_INTRINSIC_IS_POLYMORPHIC_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_REFERENCE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_reference)
#		define KERBAL_INTRINSIC_IS_REFERENCE(T) __is_reference(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_REFERENCE
#	define KERBAL_HAS_INTRINSIC_IS_REFERENCE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_REFERENCEABLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_referenceable)
#		define KERBAL_INTRINSIC_IS_REFERENCEABLE(T) __is_referenceable(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_REFERENCEABLE
#	define KERBAL_HAS_INTRINSIC_IS_REFERENCEABLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_RVALUE_REFERENCE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_rvalue_reference)
#		define KERBAL_INTRINSIC_IS_RVALUE_REFERENCE(T) __is_rvalue_reference(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_RVALUE_REFERENCE
#	define KERBAL_HAS_INTRINSIC_IS_RVALUE_REFERENCE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_SAME_AS_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_same)
#		define KERBAL_INTRINSIC_IS_SAME_AS(T) __is_same(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_same_as)
#		define KERBAL_INTRINSIC_IS_SAME_AS(T) __is_same_as(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_SAME_AS
#	define KERBAL_HAS_INTRINSIC_IS_SAME_AS_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_SCALAR_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_scalar)
#		if KERBAL_CXX_STDLIB != KERBAL_CXX_STDLIB_LIBSTDCXX // under libstdc++, internal header <bits/cpp_type_traits.h> defined a class named __is_scalar
#			define KERBAL_INTRINSIC_IS_SCALAR(T) __is_scalar(T)
#		endif
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_SCALAR
#	define KERBAL_HAS_INTRINSIC_IS_SCALAR_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_SCOPED_ENUM_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_scoped_enum)
#		define KERBAL_INTRINSIC_IS_SCOPED_ENUM(T) __is_scoped_enum(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_SCOPED_ENUM
#	define KERBAL_HAS_INTRINSIC_IS_SCOPED_ENUM_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_SIGNED_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_signed)
#		define KERBAL_INTRINSIC_IS_SIGNED(T) __is_signed(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_SIGNED
#	define KERBAL_HAS_INTRINSIC_IS_SIGNED_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_STANDARD_LAYOUT_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_standard_layout)
#		define KERBAL_INTRINSIC_IS_STANDARD_LAYOUT(T) __is_standard_layout(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_standard_layout)
#		define KERBAL_INTRINSIC_IS_STANDARD_LAYOUT(T) __is_standard_layout(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_STANDARD_LAYOUT
#	define KERBAL_HAS_INTRINSIC_IS_STANDARD_LAYOUT_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIAL_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_trivial)
#		define KERBAL_INTRINSIC_IS_TRIVIAL(T) __is_trivial(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_trivial)
#		define KERBAL_INTRINSIC_IS_TRIVIAL(T) __is_trivial(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_TRIVIAL
#	define KERBAL_HAS_INTRINSIC_IS_TRIVIAL_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_trivially_assignable)
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE(T, U) __is_trivially_assignable(T, U)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_trivially_assignable)
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE(T, U) __is_trivially_assignable(T, U)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE
#	define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_ASSIGNABLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_trivially_constructible)
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE(...) __is_trivially_constructible(__VA_ARGS__)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_trivially_constructible)
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE(...) __is_trivially_constructible(__VA_ARGS__)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE
#	define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_CONSTRUCTIBLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_COPYABLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_trivially_copyable)
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_COPYABLE(T, U) __is_trivially_copyable(T, U)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_trivially_copyable)
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_COPYABLE(T, U) __is_trivially_copyable(T, U)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_COPYABLE
#	define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_COPYABLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_trivially_destructible)
#		define KERBAL_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE(T) __is_trivially_destructible(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE
#	define KERBAL_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_UNBOUNDED_ARRAY_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_unbounded_array)
#		define KERBAL_INTRINSIC_IS_UNBOUNDED_ARRAY(T) __is_unbounded_array(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_UNBOUNDED_ARRAY
#	define KERBAL_HAS_INTRINSIC_IS_UNBOUNDED_ARRAY_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_UNION_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_union)
#		define KERBAL_INTRINSIC_IS_UNION(T) __is_union(T)
#	elif KERBAL_CLANG_PRIVATE_HAS_FEATURE(is_union)
#		define KERBAL_INTRINSIC_IS_UNION(T) __is_union(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_UNION
#	define KERBAL_HAS_INTRINSIC_IS_UNION_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_UNSIGNED_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_unsigned)
#		define KERBAL_INTRINSIC_IS_UNSIGNED(T) __is_unsigned(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_UNSIGNED
#	define KERBAL_HAS_INTRINSIC_IS_UNSIGNED_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_VOID_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_void)
#		define KERBAL_INTRINSIC_IS_VOID(T) __is_void(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_VOID
#	define KERBAL_HAS_INTRINSIC_IS_VOID_SUPPORT 1
#endif



#ifndef KERBAL_HAS_INTRINSIC_IS_VOLATILE_SUPPORT
#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__is_volatile)
#		define KERBAL_INTRINSIC_IS_VOLATILE(T) __is_volatile(T)
#	endif
#endif

#ifdef KERBAL_INTRINSIC_IS_VOLATILE
#	define KERBAL_HAS_INTRINSIC_IS_VOLATILE_SUPPORT 1
#endif


#endif // KERBAL_TYPE_TRAITS_DETAIL_COMPILER_INTRINSICS_PART__1_CLANG_PART_HPP
