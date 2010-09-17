#ifndef MAJUTSU_DETAIL_WRAPPED_TYPE_HPP_INCLUDED
#define MAJUTSU_DETAIL_WRAPPED_TYPE_HPP_INCLUDED

#include <majutsu/role.hpp>
#include <majutsu/access_role.hpp>

namespace majutsu
{
namespace detail
{

template<
	typename T
>
struct wrapped_type
{
	typedef T type;
};

template<
	typename Wrapped,
	typename Alias
>
struct wrapped_type<
	role<
		Wrapped,
		Alias
	>
>
:
access_role<
	role<
		Wrapped,
		Alias
	>
>
{};

}
}

#endif
