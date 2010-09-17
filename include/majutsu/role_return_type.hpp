#ifndef MAJUTSU_ROLE_RETURN_TYPE_HPP_INCLUDED
#define MAJUTSU_ROLE_RETURN_TYPE_HPP_INCLUDED

#include <majutsu/detail/find_role.hpp>
#include <boost/mpl/deref.hpp>

namespace majutsu
{

template<
	typename Elements,
	typename Role
>
struct role_return_type
:
boost::mpl::deref<
	typename detail::find_role<
		Elements,
		Role
	>::type
>::type
{};

}

#endif
