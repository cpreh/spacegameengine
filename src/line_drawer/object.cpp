/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "vf/format.hpp"
#include "vf/position.hpp"
#include "vf/vertex_view.hpp"
#include "vf/color.hpp"
#include <sge/line_drawer/object.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/no_texture.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/dest_blend_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/source_blend_func.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <boost/foreach.hpp>
#include <iostream>

sge::line_drawer::object::object(
	sge::renderer::device_ptr const _renderer)
:
	renderer_(
		_renderer),
	vertex_declaration_(
		renderer_->create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>())),
	vb_(),
	lines_()
{
}

void
sge::line_drawer::object::render()
{
	if (!vb_ || lines_.empty())
		return;

	sge::renderer::state::scoped scoped_state(
		renderer_,
		sge::renderer::state::list
			(sge::renderer::state::bool_::enable_alpha_blending = true)
			(sge::renderer::state::source_blend_func::src_alpha)
			(sge::renderer::state::dest_blend_func::inv_src_alpha)
			(sge::renderer::state::cull_mode::off)
			(sge::renderer::state::depth_func::off)
			(sge::renderer::state::stencil_func::off)
			(sge::renderer::state::draw_mode::fill));

	sge::renderer::scoped_vertex_declaration scoped_decl(
		renderer_,
		vertex_declaration_);

	sge::renderer::scoped_vertex_buffer scoped_vb(
		renderer_,
		vb_);

	sge::renderer::texture::scoped scoped_tex(
		renderer_,
		sge::renderer::no_texture(),
		static_cast<sge::renderer::stage_type>(
			0));

	renderer_->render(
		sge::renderer::first_vertex(
			0),
		sge::renderer::vertex_count(
			vb_->size()),
		sge::renderer::nonindexed_primitive_type::line);
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

	if (!vb_ || vb_->size() < static_cast<sge::renderer::size_type>(lines_.size()*2))
		vb_ = 
			renderer_->create_vertex_buffer(
				vertex_declaration_,
				sge::renderer::vf::dynamic::part_index(
					0u),
				static_cast<sge::renderer::size_type>(
					lines_.size()*2),
				sge::renderer::resource_flags::none);

	sge::renderer::scoped_vertex_lock const vblock(
		vb_,
		sge::renderer::lock_mode::writeonly);

	vf::vertex_view const vertices(
		vblock.value());

	vf::vertex_view::iterator vb_it(
		vertices.begin());

	BOOST_FOREACH(
		line const &l,
		lines_)
	{
		(vb_it)->set<vf::position>(
			fcppt::math::vector::structure_cast<vf::position::packed_type>(
				l.begin()));
		(vb_it++)->set<vf::color>(
			l.begin_color());
		(vb_it)->set<vf::position>(
			fcppt::math::vector::structure_cast<vf::position::packed_type>(
				l.end()));
		(vb_it++)->set<vf::color>(
			l.end_color());
	}
}
