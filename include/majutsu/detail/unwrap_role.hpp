#ifndef MAJUTSU_DETAIL_UNWRAP_ROLE_HPP_INCLUDED
#define MAJUTSU_DETAIL_UNWRAP_ROLE_HPP_INCLUDED

#include <majutsu/role.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace majutsu
{
namespace detail
{

template<
	typename T
>
struct unwrap_role
:
boost::false_type
{};

template<
	typename T,
	typename Alias
>
struct unwrap_role<
	role<
		T,
		Alias
	>
> {
	typedef Alias type;
};
		

}
}

#endif
