#ifndef MAJUTSU_ACCESS_ROLE_HPP_INCLUDED
#define MAJUTSU_ACCESS_ROLE_HPP_INCLUDED

#include <majutsu/role.hpp>

namespace majutsu
{

template<
	typename
>
struct access_role;

template<
	typename T,
	typename Alias
>
struct access_role<
	role<
		T,
		Alias
	>
>
{
	typedef T type;
};

}

#endif
