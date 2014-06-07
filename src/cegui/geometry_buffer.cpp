/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/image/mizuiro_color.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/state/core/blend/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/scoped.hpp>
#include <sge/renderer/state/core/blend/write_mask_all.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/rasterizer/enable_scissor_test.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/scoped_scissor_area.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/src/cegui/batch.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <sge/src/cegui/from_cegui_rect.hpp>
#include <sge/src/cegui/from_cegui_vector2.hpp>
#include <sge/src/cegui/from_cegui_vector3.hpp>
#include <sge/src/cegui/geometry_buffer.hpp>
#include <sge/src/cegui/make_rasterizer_parameters.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/texture.hpp>
#include <sge/src/cegui/to_blend_parameters.hpp>
#include <sge/src/cegui/vf/color.hpp>
#include <sge/src/cegui/vf/format.hpp>
#include <sge/src/cegui/vf/position.hpp>
#include <sge/src/cegui/vf/texcoord.hpp>
#include <sge/src/cegui/vf/vertex_view.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_ref_compare.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/pre_message.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/quaternion/to_matrix.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/Quaternion.h>
#include <CEGUI/Rect.h>
#include <CEGUI/RenderEffect.h>
#include <CEGUI/Vector.h>
#include <CEGUI/Vertex.h>
#include <boost/range/iterator_range.hpp>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("geometry_buffer")
)

sge::cegui::geometry_buffer::geometry_buffer(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sge::cegui::optional_render_context_ref const &_render_context
)
:
	batches_(),
	renderer_(
		_renderer
	),
	vertex_declaration_(
		_vertex_declaration
	),
	active_texture_(
		nullptr
	),
	translation_(
		sge::renderer::vector3::null()
	),
	pivot_(
		sge::renderer::vector3::null()
	),
	rotation_(
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),
	scissor_area_(
		sge::renderer::pixel_rect::null()
	),
	render_context_(
		_render_context
	),
	clip_(
		true
	),
	render_effect_(
		nullptr
	),
	rasterizer_scissor_on_(
		renderer_.create_rasterizer_state(
			sge::cegui::make_rasterizer_parameters(
				sge::renderer::state::core::rasterizer::enable_scissor_test(
					true
				)
			)
		)
	),
	rasterizer_scissor_off_(
		renderer_.create_rasterizer_state(
			sge::cegui::make_rasterizer_parameters(
				sge::renderer::state::core::rasterizer::enable_scissor_test(
					false
				)
			)
		)
	)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("geometry_buffer(")
			<< this
			<< FCPPT_TEXT(")::geometry_buffer")
	);
}

sge::cegui::geometry_buffer::~geometry_buffer()
{
}

void
sge::cegui::geometry_buffer::draw() const
{
	FCPPT_ASSERT_PRE(
		render_context_
	);

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("geometry_buffer(")
			<< this
			<< FCPPT_TEXT(")::draw()")
	);

	sge::renderer::state::ffp::transform::object_unique_ptr const transform_state(
		renderer_.create_transform_state(
			sge::renderer::state::ffp::transform::parameters(
				fcppt::math::matrix::translation(
					translation_
					+
					pivot_
				)
				*
				fcppt::math::quaternion::to_matrix(
					rotation_
				)
				*
				fcppt::math::matrix::translation(
					-pivot_
				)
			)
		)
	);

	sge::renderer::state::ffp::transform::scoped const scoped_world(
		*render_context_,
		sge::renderer::state::ffp::transform::mode::world,
		*transform_state
	);

	FCPPT_ASSERT_ERROR(
		this->getBlendMode()
		!=
		CEGUI::BM_INVALID
	);

	sge::renderer::state::core::blend::object_unique_ptr const blend_state(
		renderer_.create_blend_state(
			sge::renderer::state::core::blend::parameters(
				sge::cegui::to_blend_parameters(
					this->getBlendMode()
				),
				sge::renderer::state::core::blend::write_mask_all()
			)
		)
	);

	sge::renderer::state::core::blend::scoped const scoped_blend(
		*render_context_,
		*blend_state
	);

	sge::renderer::target::base &current_target(
		render_context_->target()
	);

	sge::renderer::target::scoped_scissor_area const scoped_scissor_area(
		current_target,
		scissor_area_
	);

	sge::renderer::vertex::scoped_declaration const scoped_vdecl(
		*render_context_,
		vertex_declaration_
	);

	int const pass_count(
		render_effect_
		?
			render_effect_->getPassCount()
		:
			1
	);

	sge::renderer::state::core::rasterizer::const_optional_object_ref prev_rasterizer;

	for(
		int pass(
			0
		);
		pass < pass_count;
		++pass
	)
	{
		if(
			render_effect_
		)
			render_effect_->performPreRenderFunctions(
				pass
			);

		for(
			sge::cegui::geometry_buffer::batch_sequence::const_iterator it(
				batches_.begin()
			);
			it != batches_.end();
			++it
		)
		{
			sge::renderer::vertex::scoped_buffer const scoped_vb(
				*render_context_,
				it->vertex_buffer()
			);

			sge::renderer::texture::scoped const scoped_texture(
				*render_context_,
				it->texture(),
				sge::renderer::texture::stage(
					0u
				)
			);

			{
				sge::renderer::state::core::rasterizer::const_optional_object_ref new_state(
					it->clip().get()
					?
						*rasterizer_scissor_on_
					:
						*rasterizer_scissor_off_
				);

				if(
					!fcppt::optional_ref_compare(
						new_state,
						prev_rasterizer
					)
				)
				{
					prev_rasterizer = new_state;

					render_context_->rasterizer_state(
						new_state
					);
				}
			}

			render_context_->render_nonindexed(
				sge::renderer::vertex::first(
					0u
				),
				sge::renderer::vertex::count(
					it->vertex_buffer().size()
				),
				sge::renderer::primitive_type::triangle_list
			);
		}
	}

	render_context_->rasterizer_state(
		sge::renderer::state::core::rasterizer::const_optional_object_ref()
	);

	if(
		render_effect_
	)
		render_effect_->performPostRenderFunctions();
}

void
sge::cegui::geometry_buffer::setTranslation(
	CEGUI::Vector3f const &_vec
)
{
	translation_ =
		sge::cegui::from_cegui_vector3<
			sge::renderer::vector3
		>(
			_vec
		);
}

void
sge::cegui::geometry_buffer::setRotation(
	CEGUI::Quaternion const &_rotation
)
{
	rotation_ =
		sge::cegui::geometry_buffer::quaternion(
			_rotation.d_w,
			_rotation.d_x,
			_rotation.d_y,
			_rotation.d_z
		);
}

void
sge::cegui::geometry_buffer::setPivot(
	CEGUI::Vector3f const &_vec
)
{
	pivot_ =
		sge::cegui::from_cegui_vector3<
			sge::renderer::vector3
		>(
			_vec
		);
}

void
sge::cegui::geometry_buffer::setClippingRegion(
	CEGUI::Rectf const &_rect
)
{
	sge::renderer::pixel_rect const converted(
		sge::cegui::from_cegui_rect<
			sge::renderer::pixel_rect
		>(
			_rect
		)
	);

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("geometry_buffer(")
			<< this
			<< FCPPT_TEXT(")::setClippingRegion(")
			<< converted
			<< FCPPT_TEXT(')')
	);

	scissor_area_ =
		converted;
}

void
sge::cegui::geometry_buffer::appendVertex(
	CEGUI::Vertex const &_vertex
)
{
	this->appendGeometry(
		&_vertex,
		1u
	);
}

void
sge::cegui::geometry_buffer::appendGeometry(
	CEGUI::Vertex const *const _vertices,
	CEGUI::uint const _vertex_count
)
{
	FCPPT_ASSERT_PRE_MESSAGE(
		active_texture_,
		FCPPT_TEXT("I got geometry without an active texture, how should I handle this? :/")
	);

	fcppt::container::ptr::push_back_unique_ptr(
		batches_,
		fcppt::make_unique_ptr<
			sge::cegui::batch
		>(
			renderer_,
			vertex_declaration_,
			active_texture_->impl(),
			sge::renderer::vertex::count(
				_vertex_count
			),
			clip_
		)
	);

	sge::renderer::vertex::scoped_lock const vblock(
		batches_.back().vertex_buffer(),
		sge::renderer::lock_mode::writeonly
	);

	sge::cegui::vf::vertex_view const vertex_view(
		vblock.value()
	);

	sge::cegui::vf::vertex_view::iterator vb_it(
		vertex_view.begin()
	);

	typedef
	sge::cegui::vf::position::packed_type
	position_vector;

	typedef
	sge::cegui::vf::texcoord::packed_type
	texcoord_vector;

	typedef boost::iterator_range<
		CEGUI::Vertex const *
	> vertex_iterator_range;

	vertex_iterator_range const range(
		boost::make_iterator_range(
			_vertices,
			_vertices + _vertex_count
		)
	);

	for(
		vertex_iterator_range::const_iterator it(
			range.begin()
		);
		it != range.end();
		++it
	)
	{
		vb_it->set<
			sge::cegui::vf::position
		>(
			sge::cegui::from_cegui_vector3<
				position_vector
			>(
				it->position
			)
		);

		vb_it->set<
			sge::cegui::vf::texcoord
		>(
			sge::cegui::from_cegui_vector2<
				texcoord_vector
			>(
				it->tex_coords
			)
		);

		vb_it->set<
			sge::cegui::vf::color
		>(
			sge::image::color::rgba8(
				(sge::image::color::init::red() %= it->colour_val.getRed())
				(sge::image::color::init::green() %= it->colour_val.getGreen())
				(sge::image::color::init::blue() %= it->colour_val.getBlue())
				(sge::image::color::init::alpha() %= it->colour_val.getAlpha())
			)
		);

		vb_it++;
	}
}

void
sge::cegui::geometry_buffer::setActiveTexture(
	CEGUI::Texture *const _tex
)
{
	FCPPT_ASSERT_PRE(
		_tex
	);

	active_texture_ =
		&dynamic_cast<
			sge::cegui::texture &
		>(
			*_tex
		);
}

void
sge::cegui::geometry_buffer::reset()
{
	batches_.clear();

	active_texture_ = nullptr;
}

CEGUI::Texture *
sge::cegui::geometry_buffer::getActiveTexture() const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("The method is never called by anyone, so it's unimplemented here")
	);
}

CEGUI::uint
sge::cegui::geometry_buffer::getVertexCount() const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("The method is never called by anyone, so it's unimplemented here")
	);
}

CEGUI::uint
sge::cegui::geometry_buffer::getBatchCount() const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("The method is never called by anyone, so it's unimplemented here")
	);
}

void
sge::cegui::geometry_buffer::setRenderEffect(
	CEGUI::RenderEffect *const _render_effect
)
{
	render_effect_ =
		_render_effect;
}

CEGUI::RenderEffect *
sge::cegui::geometry_buffer::getRenderEffect()
{
	return
		render_effect_;
}

void
sge::cegui::geometry_buffer::setClippingActive(
	bool const _active
)
{
	clip_ =
		sge::cegui::clip(
			_active
		);
}

bool
sge::cegui::geometry_buffer::isClippingActive() const
{
	return
		clip_.get();
}
