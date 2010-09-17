#ifndef MAJUTSU_BIND_HPP_INCLUDED
#define MAJUTSU_BIND_HPP_INCLUDED

#include <majutsu/placeholder.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>

namespace majutsu
{

template<
	typename Base,
	typename Binders
>
struct bind {
	typedef typename boost::mpl::transform<
		typename Base::type,
		typename Binders::type,
		boost::mpl::if_<
			boost::is_same<
				boost::mpl::_2,
				placeholder
			>,
			boost::mpl::_1,
			boost::mpl::_2
		>
	>::type type;
};

}

#endif
