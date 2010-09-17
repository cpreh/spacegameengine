#ifndef MAJUTSU_MEMORY_NEEDS_INIT_HPP_INCLUDED
#define MAJUTSU_MEMORY_NEEDS_INIT_HPP_INCLUDED

#include <majutsu/is_role.hpp>
#include <majutsu/is_constant.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

namespace majutsu
{
namespace memory
{

template<
	typename Element
>
struct needs_init
:
boost::mpl::and_<
	majutsu::is_role<
		Element
	>,
	boost::mpl::not_<
		majutsu::is_constant<
			Element
		>
	>
>
{};

}
}

#endif
