//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_DETAIL_ITERATOR_BASE_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DETAIL_ITERATOR_BASE_HPP_INCLUDED

#include <sge/renderer/index/const_proxy_fwd.hpp>
#include <sge/renderer/index/difference_type.hpp>
#include <sge/renderer/index/iterator_fwd.hpp>
#include <sge/renderer/index/nonconst_tag.hpp>
#include <sge/renderer/index/proxy_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <iterator>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{
namespace detail
{

template<
	typename Format
>
using
iterator_base
=
boost::iterator_facade<
	sge::renderer::index::iterator<
		Format
	>,
	typename
	Format::index_type,
	std::random_access_iterator_tag,
	typename
	std::conditional<
		std::is_same<
			typename
			Format::constness,
			sge::renderer::index::nonconst_tag
		>::value,
		sge::renderer::index::proxy<
			Format
		>,
		sge::renderer::index::const_proxy<
			Format
		>
	>::type,
	sge::renderer::index::difference_type
>;

}
}
}
}

#endif
