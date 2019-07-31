//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_FFP_CLIP_PLANE_OBJECT_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_CLIP_PLANE_OBJECT_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/clip_plane/object_fwd.hpp>
#include <sge/d3d9/state/ffp/clip_plane/state.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <sge/renderer/state/ffp/clip_plane/object.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace clip_plane
{

class object
:
	public sge::renderer::state::ffp::clip_plane::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		IDirect3DDevice9 &,
		sge::d3d9::state::ffp::clip_plane::state const &
	);

	~object();

	void
	set(
		sge::renderer::state::index_count
	) const;
private:
	IDirect3DDevice9 &device_;

	sge::d3d9::state::ffp::clip_plane::state const state_;
};

}
}
}
}
}

#endif
