#ifndef MAJUTSU_SUBELEMENTS_HPP_INCLUDED
#define MAJUTSU_SUBELEMENTS_HPP_INCLUDED

#include <majutsu/detail/copy_subelements.hpp>
#include <majutsu/is_role.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>

namespace majutsu
{

template<
	typename Dest,
	typename Src
>
Dest const
subelements(
	Src const &src
)
{
	Dest ret;

	boost::mpl::for_each<
		typename boost::mpl::remove_if<
			typename Src::memory_type::types,
			boost::mpl::not_<
				is_role<
					boost::mpl::_1
				>
			>
		>::type
	>(
		detail::copy_subelements<
			Dest,
			Src
		>(
			ret,
			src
		)
	);

	return ret;
}

}

#endif
