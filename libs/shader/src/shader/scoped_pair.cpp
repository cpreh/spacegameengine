//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/core_ref.hpp>
#include <sge/shader/context.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/scoped_pair.hpp>
#include <sge/shader/parameter/planar_texture.hpp>
#include <fcppt/make_cref.hpp>


sge::shader::scoped_pair::scoped_pair(
	sge::renderer::context::core_ref const _render_context,
	pair_ref const _parent
)
:
	parent_(
		_parent
	),
	scoped_vertex_program_(
		_render_context,
		fcppt::make_cref(
			parent_.get().loaded_vertex_program()
		)
	),
	scoped_pixel_program_(
		_render_context,
		fcppt::make_cref(
			parent_.get().loaded_pixel_program()
		)
	)
{
	for(
		sge::shader::parameter::planar_texture *const ptr
		:
		parent_.get().planar_textures_
	)
	{
		ptr->activate(
			_render_context
		);
	}
}

sge::shader::scoped_pair::~scoped_pair()
{
	for(
		sge::shader::parameter::planar_texture *const ptr
		:
		parent_.get().planar_textures_
	)
	{
		ptr->deactivate();
	}
}
