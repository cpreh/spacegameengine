#ifndef MAJUTSU_DETAIL_MAKE_ITERATORS_HPP_INCLUDED
#define MAJUTSU_DETAIL_MAKE_ITERATORS_HPP_INCLUDED

#include <boost/mpl/iter_fold.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/placeholders.hpp>

namespace majutsu
{
namespace detail
{

template<
	typename Sequence
>
struct make_iterators
:
boost::mpl::iter_fold<
	Sequence,
	boost::mpl::vector0<>,
	boost::mpl::push_back<
		boost::mpl::_1,
		boost::mpl::_2
	>
>
{};

}
}

#endif
