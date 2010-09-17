#ifndef MAJUTSU_MEMORY_DETAIL_EXPAND_FUSION_INITLIST_HPP_INCLUDED
#define MAJUTSU_MEMORY_DETAIL_EXPAND_FUSION_INITLIST_HPP_INCLUDED

#include <majutsu/memory/detail/init_fusion_element.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/adapted/mpl.hpp>

namespace majutsu
{
namespace memory
{
namespace detail
{

template<
	typename Types,
	typename Tuple,
	typename Arguments
>
Tuple const
expand_fusion_initlist(
	Arguments const &arguments_
)
{
	return boost::fusion::transform(
		Types(),
		init_fusion_element<
			Types,
			Arguments
		>(
			arguments_
		)
	);
}

}
}
}

#endif
