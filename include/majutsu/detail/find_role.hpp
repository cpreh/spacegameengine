#ifndef MAJUTSU_DETAIL_FIND_ROLE_HPP_INCLUDED
#define MAJUTSU_DETAIL_FIND_ROLE_HPP_INCLUDED

#include <majutsu/detail/unwrap_role.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>

namespace majutsu
{
namespace detail
{

template<
	typename Elements,
	typename Role
>
struct find_role
:
boost::mpl::find_if<
	Elements,
	boost::is_same<
		unwrap_role<
			boost::mpl::_1
		>,
		Role
	>
>
{};

}
}

#endif
