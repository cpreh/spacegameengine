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


#include <sge/cegui/exception.hpp>
#include <sge/cegui/structure_cast.hpp>
#include <sge/cegui/detail/geometry_buffer.hpp>
#include <sge/cegui/detail/texture.hpp>
#include <sge/cegui/vf/color.hpp>
#include <sge/cegui/vf/format.hpp>
#include <sge/cegui/vf/position.hpp>
#include <sge/cegui/vf/texcoord.hpp>
#include <sge/cegui/vf/vertex_view.hpp>
#include <sge/image/color/init.hpp>
#include <sge/renderer/active_target.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_scissor_area.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/target_base.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_count.hpp>
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
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/pre_message.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/rotation_axis.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range.hpp>
#include <CEGUIVertex.h>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("geometry_buffer"))

sge::cegui::detail::geometry_buffer::geometry_buffer(
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration &_vertex_declaration)
:
	batches_(),
	renderer_(
		_renderer),
	vertex_declaration_(
		_vertex_declaration),
	total_vertex_count_(
		static_cast<CEGUI::uint>(0)),
	active_texture_(
		0),
	blend_mode_(
		CEGUI::BM_NORMAL),
	translation_(
		sge::renderer::vector3::null()),
	rotation_pivot_(
		sge::renderer::vector3::null()),
	rotation_axis_(
		sge::renderer::vector3::null())
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("geometry_buffer(") << this << FCPPT_TEXT(")::geometry_buffer"));
}

void
sge::cegui::detail::geometry_buffer::draw() const
{
	sge::renderer::scoped_transform scoped_world(
		renderer_,
		sge::renderer::matrix_mode::world,
		fcppt::math::matrix::translation(
			translation_ + rotation_pivot_) *
		fcppt::math::matrix::rotation_axis(
			rotation_axis_[2],
			sge::renderer::vector3(
				static_cast<sge::renderer::scalar>(
					0),
				static_cast<sge::renderer::scalar>(
					0),
				static_cast<sge::renderer::scalar>(
					1))) *
		fcppt::math::matrix::rotation_axis(
			rotation_axis_[1],
			sge::renderer::vector3(
				static_cast<sge::renderer::scalar>(
					0),
				static_cast<sge::renderer::scalar>(
					1),
				static_cast<sge::renderer::scalar>(
					0))) *
		fcppt::math::matrix::rotation_axis(
			rotation_axis_[0],
			sge::renderer::vector3(
				static_cast<sge::renderer::scalar>(
					1),
				static_cast<sge::renderer::scalar>(
					0),
				static_cast<sge::renderer::scalar>(
					0))) *
		fcppt::math::matrix::translation(
			-rotation_pivot_));

	sge::renderer::state::source_blend_func::type sbf =
		sge::renderer::state::source_blend_func::src_alpha;
	sge::renderer::state::dest_blend_func::type dbf =
		sge::renderer::state::dest_blend_func::inv_src_alpha;

	switch(
		blend_mode_)
	{
		case CEGUI::BM_RTT_PREMULTIPLIED:
			sbf = sge::renderer::state::source_blend_func::one;
			dbf = sge::renderer::state::dest_blend_func::inv_src_alpha;
			break;
		case CEGUI::BM_INVALID:
			throw exception(FCPPT_TEXT("We got an invalid blend mode o_O"));
		case CEGUI::BM_NORMAL:
			sbf = sge::renderer::state::source_blend_func::src_alpha;
			dbf = sge::renderer::state::dest_blend_func::inv_src_alpha;
			break;
	}

	sge::renderer::state::scoped scoped_state(
		renderer_,
		sge::renderer::state::list
			(sbf)
			(dbf));

	sge::renderer::target_base &current_target =
		sge::renderer::active_target(
			renderer_);

	sge::renderer::scoped_scissor_area _scoped_scissor_area(
		current_target,
		scissor_area_);

	sge::renderer::scoped_vertex_declaration scoped_vdecl(
		renderer_,
		vertex_declaration_);

	for(
		batch_sequence::const_iterator it(
			batches_.begin()
		);
		it != batches_.end();
		++it
	)
	{
		sge::renderer::scoped_vertex_buffer scoped_vb(
			renderer_,
			it->vertex_buffer());

		sge::renderer::texture::scoped scoped_texture(
			renderer_,
			it->texture(),
			sge::renderer::stage(
				0u));

		renderer_.render_nonindexed(
			sge::renderer::first_vertex(
				0),
			sge::renderer::vertex_count(
				it->vertex_buffer().size()),
			sge::renderer::nonindexed_primitive_type::triangle);
	}
}

void
sge::cegui::detail::geometry_buffer::setTranslation(
	CEGUI::Vector3 const &v)
{
	translation_ =
		sge::renderer::vector3(
			static_cast<sge::renderer::scalar>(
				v.d_x),
			static_cast<sge::renderer::scalar>(
				v.d_y),
			static_cast<sge::renderer::scalar>(
				v.d_z));
}

void
sge::cegui::detail::geometry_buffer::setRotation(
	CEGUI::Vector3 const &v)
{
	rotation_axis_ =
		sge::renderer::vector3(
			static_cast<sge::renderer::scalar>(
				v.d_x),
			static_cast<sge::renderer::scalar>(
				v.d_y),
			static_cast<sge::renderer::scalar>(
				v.d_z));
}

void
sge::cegui::detail::geometry_buffer::setPivot(
	CEGUI::Vector3 const &v)
{
	rotation_pivot_ =
		sge::renderer::vector3(
			static_cast<sge::renderer::scalar>(
				v.d_x),
			static_cast<sge::renderer::scalar>(
				v.d_y),
			static_cast<sge::renderer::scalar>(
				v.d_z));
}

void
sge::cegui::detail::geometry_buffer::setClippingRegion(
	CEGUI::Rect const &r)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("geometry_buffer(") << this << FCPPT_TEXT(")::setClippingRegion(")
			<< structure_cast<sge::renderer::pixel_rect>(r) << FCPPT_TEXT(")"));
	scissor_area_ =
		structure_cast<sge::renderer::pixel_rect>(
			r);
}

void
sge::cegui::detail::geometry_buffer::appendVertex(
	CEGUI::Vertex const &v)
{
	appendGeometry(
		&v,
		1);
}

void
sge::cegui::detail::geometry_buffer::appendGeometry(
	CEGUI::Vertex const * const vertices,
	CEGUI::uint const vertex_count)
{
	FCPPT_ASSERT_PRE_MESSAGE(
		active_texture_,
		FCPPT_TEXT("I got geometry without an active texture, how should I handle this? :/"));

	total_vertex_count_ =
		static_cast<CEGUI::uint>(
			total_vertex_count_ + vertex_count);

	batches_.push_back(
		batch(
			active_texture_->impl(),
			renderer_.create_vertex_buffer(
				vertex_declaration_,
				sge::renderer::vf::dynamic::part_index(
					0u),
				static_cast<sge::renderer::size_type>(
					vertex_count),
				sge::renderer::resource_flags::none)));

	sge::renderer::scoped_vertex_lock const vblock(
		batches_.back().vertex_buffer(),
		sge::renderer::lock_mode::writeonly);

	vf::vertex_view const vertex_view(
		vblock.value());

	vf::vertex_view::iterator vb_it(
		vertex_view.begin());

	typedef
	vf::position::packed_type
	position_vector;

	typedef
	vf::texcoord::packed_type
	texcoord_vector;

	typedef boost::iterator_range<
		CEGUI::Vertex const *
	> vertex_iterator_range;

	vertex_iterator_range const range(
		boost::make_iterator_range(
			vertices,
			vertices + vertex_count));

	for(
		vertex_iterator_range::const_iterator it(
			range.begin()
		);
		it != range.end();
		++it
	)
	{
		vb_it->set<vf::position>(
			position_vector(
				it->position.d_x,
				it->position.d_y,
				it->position.d_z));
		vb_it->set<vf::texcoord>(
			texcoord_vector(
				it->tex_coords.d_x,
				it->tex_coords.d_y));
		vb_it->set<vf::color>(
			(sge::image::color::init::red() %= it->colour_val.getRed())
			(sge::image::color::init::green() %= it->colour_val.getGreen())
			(sge::image::color::init::blue() %= it->colour_val.getBlue())
			(sge::image::color::init::alpha() %= it->colour_val.getAlpha()));

		vb_it++;
	}
}

void
sge::cegui::detail::geometry_buffer::setActiveTexture(
	CEGUI::Texture * const tex)
{
	FCPPT_ASSERT_PRE(
		tex);
	active_texture_ =
		&dynamic_cast<texture &>(
			*tex);
}

void
sge::cegui::detail::geometry_buffer::reset()
{
	batches_.clear();
	active_texture_ = 0;
	total_vertex_count_ = 0;
}

CEGUI::Texture*
sge::cegui::detail::geometry_buffer::getActiveTexture() const
{
	return active_texture_;
}

CEGUI::uint
sge::cegui::detail::geometry_buffer::getVertexCount() const
{
	return total_vertex_count_;
}

CEGUI::uint
sge::cegui::detail::geometry_buffer::getBatchCount() const
{
	return
		static_cast<CEGUI::uint>(
			batches_.size());
}

void
sge::cegui::detail::geometry_buffer::setRenderEffect(
	CEGUI::RenderEffect*)
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("Render effects are not implemented yet"));
}

CEGUI::RenderEffect*
sge::cegui::detail::geometry_buffer::getRenderEffect()
{
	return 0;
}

void
sge::cegui::detail::geometry_buffer::setBlendMode(
	CEGUI::BlendMode const _blend_mode)
{
	blend_mode_ =
		_blend_mode;
}

CEGUI::BlendMode
sge::cegui::detail::geometry_buffer::getBlendMode() const
{
	return blend_mode_;
}

sge::cegui::detail::geometry_buffer::~geometry_buffer()
{
}
