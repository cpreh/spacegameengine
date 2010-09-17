#ifndef MAJUTSU_CONSTANT_HPP_INCLUDED
#define MAJUTSU_CONSTANT_HPP_INCLUDED

#include <majutsu/concepts/static_size.hpp>

namespace majutsu
{

template<
	typename T,
	typename T::type Value
>
struct constant
:
T
{
	static typename T::type const value = Value;
};

template<
	typename T,
	typename T::type Value
>
typename T::type const
constant<T, Value>::value;


namespace concepts
{

template<
	typename T,
	typename T::type Value
>
struct static_size<
	majutsu::constant<
		T,
		Value
	>
>
:
static_size<
	T
>
{};

}
}

#endif
