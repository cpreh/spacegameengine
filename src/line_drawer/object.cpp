/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/line_drawer/object.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/scoped.hpp>
#include <sge/renderer/state/core/blend/source.hpp>
#include <sge/renderer/state/core/blend/write_mask_all.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/src/line_drawer/vf/color.hpp>
#include <sge/src/line_drawer/vf/format.hpp>
#include <sge/src/line_drawer/vf/position.hpp>
#include <sge/src/line_drawer/vf/vertex_view.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sge::line_drawer::object::object(
	sge::renderer::device::core &_renderer)
:
	renderer_(
		_renderer),
	vertex_declaration_(
		renderer_.create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>())),
	blend_state_(
		renderer_.create_blend_state(
			sge::renderer::state::core::blend::parameters(
				sge::renderer::state::core::blend::alpha_enabled(
					sge::renderer::state::core::blend::combined(
						sge::renderer::state::core::blend::source::src_alpha,
						sge::renderer::state::core::blend::dest::inv_src_alpha)),
				sge::renderer::state::core::blend::write_mask_all()))),
	vb_(),
	lines_()
{
}

void
sge::line_drawer::object::render(
	sge::renderer::context::core &_render_context
)
{
	if (!vb_ || lines_.empty())
		return;

	sge::renderer::state::core::blend::scoped const scoped_blend(
		_render_context,
		*blend_state_
	);

	sge::renderer::scoped_vertex_declaration const scoped_decl(
		_render_context,
		*vertex_declaration_);

	sge::renderer::scoped_vertex_buffer const scoped_vb(
		_render_context,
		*vb_);

	_render_context.render_nonindexed(
		sge::renderer::first_vertex(
			0u),
		sge::renderer::vertex_count(
			vb_->size()),
		sge::renderer::primitive_type::line_list);
}

sge::line_drawer::object::~object()
{
}

void
sge::line_drawer::object::lock()
{
}

void
sge::line_drawer::object::unlock()
{
	if (lines_.empty())
		return;

	if (!vb_ || vb_->size().get() < static_cast<sge::renderer::size_type>(lines_.size()*2))
		vb_.take(
			renderer_.create_vertex_buffer(
				*vertex_declaration_,
				sge::renderer::vf::dynamic::part_index(
					0u),
				sge::renderer::vertex_count(
					lines_.size()*2),
				sge::renderer::resource_flags_field::null()));

	sge::renderer::scoped_vertex_lock const vblock(
		*vb_,
		sge::renderer::lock_mode::writeonly);

	vf::vertex_view const vertices(
		vblock.value());

	vf::vertex_view::iterator vb_it(
		vertices.begin());

	for(
		line_sequence::const_iterator it(
			lines_.begin()
		);
		it != lines_.end();
		++it
	)
	{
		(vb_it)->set<vf::position>(
			fcppt::math::vector::structure_cast<vf::position::packed_type>(
				it->begin()));
		(vb_it++)->set<vf::color>(
			it->begin_color());
		(vb_it)->set<vf::position>(
			fcppt::math::vector::structure_cast<vf::position::packed_type>(
				it->end()));
		(vb_it++)->set<vf::color>(
			it->end_color());
	}
}
