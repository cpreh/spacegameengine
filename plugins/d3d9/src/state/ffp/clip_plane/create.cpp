//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/clip_plane/create.hpp>
#include <sge/d3d9/state/ffp/clip_plane/make_states.hpp>
#include <sge/d3d9/state/ffp/clip_plane/object.hpp>
#include <sge/renderer/state/ffp/clip_plane/object.hpp>
#include <sge/renderer/state/ffp/clip_plane/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/clip_plane/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::state::ffp::clip_plane::object_unique_ptr
sge::d3d9::state::ffp::clip_plane::create(
	IDirect3DDevice9 &_device,
	sge::renderer::state::ffp::clip_plane::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::state::ffp::clip_plane::object
		>(
			fcppt::make_unique_ptr<
				sge::d3d9::state::ffp::clip_plane::object
			>(
				_device,
				sge::d3d9::state::ffp::clip_plane::make_states(
					_parameters
				)
			)
		);
}
