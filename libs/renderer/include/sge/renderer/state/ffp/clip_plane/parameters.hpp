//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_CLIP_PLANE_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_CLIP_PLANE_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/clip_plane/area.hpp>
#include <sge/renderer/state/ffp/clip_plane/parameters_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace clip_plane
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	parameters(
		sge::renderer::state::ffp::clip_plane::area
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::clip_plane::area const &
	area() const;
private:
	sge::renderer::state::ffp::clip_plane::area area_;
};

}
}
}
}
}

#endif
