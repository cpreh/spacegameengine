#ifndef MAJUTSU_IS_CONSTANT_HPP_INCLUDED
#define MAJUTSU_IS_CONSTANT_HPP_INCLUDED

#include <majutsu/constant.hpp>
#include <majutsu/role.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace majutsu
{

template<
	typename T
>
struct is_constant
:
boost::false_type
{};

template<
	typename T,
	typename T::type Value
>
struct is_constant<
	constant<
		T,
		Value
	>
>
:
boost::true_type
{};

template<
	typename T,
	typename T::type Value,
	typename A
>
struct is_constant<
	role<
		constant<
			T,
			Value
		>,
		A
	>
>
:
boost::true_type
{};

}

#endif
