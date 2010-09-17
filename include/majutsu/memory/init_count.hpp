#ifndef MAJUTSU_MEMORY_INIT_COUNT_HPP_INCLUDED
#define MAJUTSU_MEMORY_INIT_COUNT_HPP_INCLUDED

#include <majutsu/memory/needs_init.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/placeholders.hpp>

namespace majutsu
{
namespace memory
{

template<
	typename Memory
>
struct init_count
:
boost::mpl::size<
	boost::mpl::filter_view<
		typename Memory::types,
		needs_init<
			boost::mpl::_1
		>
	>
>
{};

}
}

#endif
