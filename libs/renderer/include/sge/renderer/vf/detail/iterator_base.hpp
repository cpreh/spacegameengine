//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DETAIL_ITERATOR_BASE_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_ITERATOR_BASE_HPP_INCLUDED

#include <sge/renderer/vf/iterator_fwd.hpp>
#include <sge/renderer/vf/vertex_difference.hpp>
#include <sge/renderer/vf/vertex_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace detail
{

template<
	typename Part,
	typename Constness
>
using iterator_base
=
boost::iterator_facade<
	sge::renderer::vf::iterator<
		Part,
		Constness
	>,
	sge::renderer::vf::vertex<
		Part,
		Constness
	>,
	std::random_access_iterator_tag,
	sge::renderer::vf::vertex<
		Part,
		Constness
	>,
	sge::renderer::vf::vertex_difference
>;

}
}
}
}

#endif

