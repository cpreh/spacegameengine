#ifndef MAJUTSU_EXTRACT_CONSTANT_HPP_INCLUDED
#define MAJUTSU_EXTRACT_CONSTANT_HPP_INCLUDED

#include <majutsu/detail/find_role.hpp>
#include <majutsu/flatten.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/integral_c.hpp>

namespace majutsu
{

template<
	typename Types,
	typename Role
>
struct extract_constant {
private:
	typedef typename flatten<
		Types
	>::type flattened_types;

	typedef typename boost::mpl::deref<
		typename detail::find_role<
			flattened_types,
			Role
		>::type
	>::type found_role;
public:
	typedef boost::mpl::integral_c<
		typename found_role::type,
		found_role::value
	> type;
};

}

#endif
