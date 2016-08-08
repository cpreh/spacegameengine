/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/cegui/impl/batch.hpp>
#include <sge/cegui/impl/from_cegui_rect.hpp>
#include <sge/cegui/impl/from_cegui_vector2.hpp>
#include <sge/cegui/impl/from_cegui_vector3.hpp>
#include <sge/cegui/impl/geometry_buffer.hpp>
#include <sge/cegui/impl/make_rasterizer_parameters.hpp>
#include <sge/cegui/impl/matrix_from_quaternion.hpp>
#include <sge/cegui/impl/optional_render_context_ref.hpp>
#include <sge/cegui/impl/texture.hpp>
#include <sge/cegui/impl/to_blend_parameters.hpp>
#include <sge/cegui/impl/vf/color.hpp>
#include <sge/cegui/impl/vf/format.hpp>
#include <sge/cegui/impl/vf/position.hpp>
#include <sge/cegui/impl/vf/texcoord.hpp>
#include <sge/cegui/impl/vf/vertex_view.hpp>
#include <sge/image/mizuiro_color.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/state/core/blend/alpha_variant.hpp>
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
#include <sge/renderer/target/scissor_area.hpp>
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
#include <fcppt/const.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_comparison.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/math/box/null.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/from_pointer.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_pointer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/Quaternion.h>
#include <CEGUI/Rect.h>
#include <CEGUI/RenderEffect.h>
#include <CEGUI/Vector.h>
#include <CEGUI/Vertex.h>
#include <boost/range/iterator_range.hpp>
#include <fcppt/config/external_end.hpp>


sge::cegui::impl::geometry_buffer::geometry_buffer(
	fcppt::log::object &_log,
	sge::renderer::device::ffp &_renderer,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sge::cegui::impl::optional_render_context_ref const &_render_context
)
:
	log_{
		_log,
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("geometry_buffer")
			}
		)
	},
	batches_(),
	renderer_(
		_renderer
	),
	vertex_declaration_(
		_vertex_declaration
	),
	active_texture_{},
	translation_(
		fcppt::math::vector::null<
			sge::renderer::vector3
		>()
	),
	pivot_(
		fcppt::math::vector::null<
			sge::renderer::vector3
		>()
	),
	rotation_(
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),
	scissor_area_(
		fcppt::math::box::null<
			sge::renderer::pixel_rect
		>()
	),
	render_context_(
		_render_context
	),
	clip_(
		true
	),
	render_effect_{},
	rasterizer_scissor_on_(
		renderer_.create_rasterizer_state(
			sge::cegui::impl::make_rasterizer_parameters(
				sge::renderer::state::core::rasterizer::enable_scissor_test(
					true
				)
			)
		)
	),
	rasterizer_scissor_off_(
		renderer_.create_rasterizer_state(
			sge::cegui::impl::make_rasterizer_parameters(
				sge::renderer::state::core::rasterizer::enable_scissor_test(
					false
				)
			)
		)
	)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("geometry_buffer(")
			<< this
			<< FCPPT_TEXT(")::geometry_buffer")
	);
}

sge::cegui::impl::geometry_buffer::~geometry_buffer()
{
}

void
sge::cegui::impl::geometry_buffer::draw() const
{
	sge::renderer::context::ffp &render_context(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			render_context_
		).get()
	);

	FCPPT_LOG_DEBUG(
		log_,
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
				sge::cegui::impl::matrix_from_quaternion(
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
		render_context,
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
				sge::renderer::state::core::blend::alpha_variant{
					sge::cegui::impl::to_blend_parameters(
						this->getBlendMode()
					)
				},
				sge::renderer::state::core::blend::write_mask_all()
			)
		)
	);

	sge::renderer::state::core::blend::scoped const scoped_blend(
		render_context,
		*blend_state
	);

	sge::renderer::target::base &current_target(
		render_context.target()
	);

	sge::renderer::target::scoped_scissor_area const scoped_scissor_area(
		current_target,
		scissor_area_
	);

	sge::renderer::vertex::scoped_declaration const scoped_vdecl(
		render_context,
		vertex_declaration_
	);

	int const pass_count(
		fcppt::optional::maybe(
			render_effect_,
			fcppt::const_(
				1
			),
			[](
				fcppt::reference<
					CEGUI::RenderEffect
				> const _effect
			)
			{
				return
					_effect.get().getPassCount();
			}
		)
	);

	sge::renderer::state::core::rasterizer::const_optional_object_ref prev_rasterizer;

	for(
		int const pass
		:
		fcppt::make_int_range_count(
			pass_count
		)
	)
	{
		fcppt::optional::maybe_void(
			render_effect_,
			[
				pass
			](
				fcppt::reference<
					CEGUI::RenderEffect
				> const _effect
			)
			{
				_effect.get().performPreRenderFunctions(
					pass
				);
			}
		);

		for(
			sge::cegui::impl::batch const &batch
			:
			batches_
		)
		{
			sge::renderer::vertex::scoped_buffer const scoped_vb(
				render_context,
				batch.vertex_buffer()
			);

			sge::renderer::texture::scoped const scoped_texture(
				render_context,
				batch.texture(),
				sge::renderer::texture::stage(
					0u
				)
			);

			{
				sge::renderer::state::core::rasterizer::const_optional_object_ref new_state(
					fcppt::make_cref(
						batch.clip().get()
						?
							*rasterizer_scissor_on_
						:
							*rasterizer_scissor_off_
					)
				);

				if(
					new_state
					!=
					prev_rasterizer
				)
				{
					prev_rasterizer = new_state;

					render_context.rasterizer_state(
						new_state
					);
				}
			}

			render_context.render_nonindexed(
				sge::renderer::vertex::first(
					0u
				),
				sge::renderer::vertex::count(
					batch.vertex_buffer().linear_size()
				),
				sge::renderer::primitive_type::triangle_list
			);
		}
	}

	render_context.rasterizer_state(
		sge::renderer::state::core::rasterizer::const_optional_object_ref()
	);

	fcppt::optional::maybe_void(
		render_effect_,
		[](
			fcppt::reference<
				CEGUI::RenderEffect
			> const _effect
		)
		{
			_effect.get().performPostRenderFunctions();
		}
	);
}

void
sge::cegui::impl::geometry_buffer::setTranslation(
	CEGUI::Vector3f const &_vec
)
{
	translation_ =
		sge::cegui::impl::from_cegui_vector3(
			_vec
		);
}

void
sge::cegui::impl::geometry_buffer::setRotation(
	CEGUI::Quaternion const &_rotation
)
{
	rotation_ =
		_rotation;
}

void
sge::cegui::impl::geometry_buffer::setPivot(
	CEGUI::Vector3f const &_vec
)
{
	pivot_ =
		sge::cegui::impl::from_cegui_vector3(
			_vec
		);
}

void
sge::cegui::impl::geometry_buffer::setClippingRegion(
	CEGUI::Rectf const &_rect
)
{
	sge::renderer::pixel_rect const converted(
		fcppt::math::box::structure_cast<
			sge::renderer::pixel_rect,
			fcppt::cast::float_to_int_fun
		>(
			sge::cegui::impl::from_cegui_rect(
				_rect
			)
		)
	);

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("geometry_buffer(")
			<< this
			<< FCPPT_TEXT(")::setClippingRegion(")
			<< converted
			<< FCPPT_TEXT(')')
	);

	scissor_area_ =
		sge::renderer::target::scissor_area{
			converted
		};
}

void
sge::cegui::impl::geometry_buffer::appendVertex(
	CEGUI::Vertex const &_vertex
)
{
	this->appendGeometry(
		&_vertex,
		1u
	);
}

void
sge::cegui::impl::geometry_buffer::appendGeometry(
	CEGUI::Vertex const *const _vertices,
	CEGUI::uint const _vertex_count
)
{
	sge::cegui::impl::texture &active_texture{
		FCPPT_ASSERT_OPTIONAL_ERROR(
			active_texture_
		).get()
	};

	batches_.push_back(
		sge::cegui::impl::batch{
			renderer_,
			vertex_declaration_,
			FCPPT_ASSERT_OPTIONAL_ERROR(
				active_texture.impl()
			).get(),
			sge::renderer::vertex::count(
				_vertex_count
			),
			clip_
		}
	);

	sge::renderer::vertex::scoped_lock const vblock(
		batches_.back().vertex_buffer(),
		sge::renderer::lock_mode::writeonly
	);

	sge::cegui::impl::vf::vertex_view const vertex_view(
		vblock.value()
	);

	sge::cegui::impl::vf::vertex_view::iterator vb_it(
		vertex_view.begin()
	);

	// TODO: Algorithm
	for(
		CEGUI::Vertex const &vertex
		:
		boost::make_iterator_range(
			_vertices,
			_vertices + _vertex_count
		)
	)
	{
		vb_it->set<
			sge::cegui::impl::vf::position
		>(
			sge::cegui::impl::from_cegui_vector3(
				vertex.position
			)
		);

		vb_it->set<
			sge::cegui::impl::vf::texcoord
		>(
			sge::cegui::impl::from_cegui_vector2(
				vertex.tex_coords
			)
		);

		vb_it->set<
			sge::cegui::impl::vf::color
		>(
			sge::image::color::rgba8(
				(sge::image::color::init::red() %= vertex.colour_val.getRed())
				(sge::image::color::init::green() %= vertex.colour_val.getGreen())
				(sge::image::color::init::blue() %= vertex.colour_val.getBlue())
				(sge::image::color::init::alpha() %= vertex.colour_val.getAlpha())
			)
		);

		++vb_it;
	}
}

void
sge::cegui::impl::geometry_buffer::setActiveTexture(
	CEGUI::Texture *const _tex
)
{
	FCPPT_ASSERT_PRE(
		_tex
		!=
		nullptr
	);

	active_texture_ =
		sge::cegui::impl::geometry_buffer::optional_texture_ref{
			fcppt::make_ref(
				dynamic_cast<
					sge::cegui::impl::texture &
				>(
					*_tex
				)
			)
		};
}

void
sge::cegui::impl::geometry_buffer::reset()
{
	batches_.clear();

	active_texture_ =
		sge::cegui::impl::geometry_buffer::optional_texture_ref{};
}

CEGUI::Texture *
sge::cegui::impl::geometry_buffer::getActiveTexture() const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("The method is never called by anyone, so it's unimplemented here")
	);
}

CEGUI::uint
sge::cegui::impl::geometry_buffer::getVertexCount() const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("The method is never called by anyone, so it's unimplemented here")
	);
}

CEGUI::uint
sge::cegui::impl::geometry_buffer::getBatchCount() const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("The method is never called by anyone, so it's unimplemented here")
	);
}

void
sge::cegui::impl::geometry_buffer::setRenderEffect(
	CEGUI::RenderEffect *const _render_effect
)
{
	render_effect_ =
		fcppt::optional::from_pointer(
			_render_effect
		);
}

CEGUI::RenderEffect *
sge::cegui::impl::geometry_buffer::getRenderEffect()
{
	return
		fcppt::optional::to_pointer(
			render_effect_
		);
}

void
sge::cegui::impl::geometry_buffer::setClippingActive(
	bool const _active
)
{
	clip_ =
		sge::cegui::impl::clip{
			_active
		};
}

bool
sge::cegui::impl::geometry_buffer::isClippingActive() const
{
	return
		clip_.get();
}
