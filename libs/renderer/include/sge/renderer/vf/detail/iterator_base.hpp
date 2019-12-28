//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DETAIL_ITERATOR_BASE_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_ITERATOR_BASE_HPP_INCLUDED

#include <sge/renderer/vf/iterator_fwd.hpp>
#include <sge/renderer/vf/proxy_fwd.hpp>
#include <sge/renderer/vf/vertex_difference.hpp>
#include <fcppt/iterator/base_decl.hpp>
#include <fcppt/iterator/types.hpp>
#include <fcppt/config/external_begin.hpp>
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
using
iterator_base
=
fcppt::iterator::base<
	fcppt::iterator::types<
		sge::renderer::vf::iterator<
			Part,
			Constness
		>,
		// TODO: Should this be renderer::vf::vertex?
		sge::renderer::vf::proxy<
			Part,
			Constness
		>,
		sge::renderer::vf::proxy<
			Part,
			Constness
		>,
		sge::renderer::vf::vertex_difference,
		// TODO: output_iterator?
		std::input_iterator_tag
	>
>;

}
}
}
}

#endif

