#ifndef MAJUTSU_IS_ROLE_HPP_INCLUDED
#define MAJUTSU_IS_ROLE_HPP_INCLUDED

#include <majutsu/role.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace majutsu
{

template<
	typename T
>
struct is_role
:
boost::false_type
{};

template<
	typename Type,
	typename Alias
>
struct is_role<
	majutsu::role<
		Type,
		Alias
	>
>
:
boost::true_type
{};

}

#endif
