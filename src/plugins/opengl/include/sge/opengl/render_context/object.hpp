/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_RENDER_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_RENDER_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/target/scoped.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/primitive_type_fwd.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/optional_offscreen_ref_fwd.hpp>
#include <sge/renderer/state/core/blend/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/state/ffp/alpha_test/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/fog/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/material/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/misc/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/transform/mode_fwd.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/texture/const_optional_base_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/unique_ptr_decl.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/renderer/cg/loaded_program_fwd.hpp>
#include <sge/renderer/cg/loaded_texture_fwd.hpp>
#endif


namespace sge
{
namespace opengl
{
namespace render_context
{

class object
:
	public sge::renderer::context::ffp
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::opengl::context::object &,
		sge::renderer::target::base &
	);

	~object()
	override;

	void
	end_rendering();
private:
	sge::renderer::target::base &
	target()
	override;

	void
	clear(
		sge::renderer::clear::parameters const &
	)
	override;

	void
	offscreen_target(
		sge::renderer::target::optional_offscreen_ref const &
	)
	override;

	void
	render_indexed(
		sge::renderer::index::buffer const &,
		sge::renderer::vertex::first,
		sge::renderer::vertex::count,
		sge::renderer::primitive_type,
		sge::renderer::index::first,
		sge::renderer::index::count
	)
	override;

	void
	render_nonindexed(
		sge::renderer::vertex::first,
		sge::renderer::vertex::count,
		sge::renderer::primitive_type
	)
	override;

	void
	activate_vertex_buffer(
		sge::renderer::vertex::buffer const &
	)
	override;

	void
	deactivate_vertex_buffer(
		sge::renderer::vertex::buffer const &
	)
	override;

	void
	vertex_declaration(
		sge::renderer::vertex::const_optional_declaration_ref const &
	)
	override;

	void
	texture(
		sge::renderer::texture::const_optional_base_ref const &,
		sge::renderer::texture::stage
	)
	override;

	void
	blend_state(
		sge::renderer::state::core::blend::const_optional_object_ref const &
	)
	override;

	void
	depth_stencil_state(
		sge::renderer::state::core::depth_stencil::const_optional_object_ref const &
	)
	override;

	void
	rasterizer_state(
		sge::renderer::state::core::rasterizer::const_optional_object_ref const &
	)
	override;

	void
	sampler_state(
		sge::renderer::state::core::sampler::const_optional_object_ref_map const &
	)
	override;

	void
	alpha_test_state(
		sge::renderer::state::ffp::alpha_test::const_optional_object_ref const &
	)
	override;

	void
	clip_plane_state(
		sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &
	)
	override;

	void
	fog_state(
		sge::renderer::state::ffp::fog::const_optional_object_ref const &
	)
	override;

	void
	lighting_state(
		sge::renderer::state::ffp::lighting::const_optional_object_ref const &
	)
	override;

	void
	lights_state(
		sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &
	)
	override;

	void
	material_state(
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref const &
	)
	override;

	void
	misc_state(
		sge::renderer::state::ffp::misc::const_optional_object_ref const &
	)
	override;

	void
	sampler_ffp_state(
		sge::renderer::state::ffp::sampler::const_object_ref_vector const &
	)
	override;

	void
	transform(
		sge::renderer::state::ffp::transform::mode,
		sge::renderer::state::ffp::transform::const_optional_object_ref const &
	)
	override;

#if defined(SGE_RENDERER_HAVE_CG)
	void
	set_cg_program(
		sge::renderer::cg::loaded_program const &
	)
	override;

	void
	unset_cg_program(
		sge::renderer::cg::loaded_program const &
	)
	override;

	sge::renderer::texture::stage
	set_cg_texture(
		sge::renderer::cg::loaded_texture const &
	)
	override;

	void
	unset_cg_texture(
		sge::renderer::cg::loaded_texture const &
	)
	override;
#endif

	sge::opengl::context::object &context_;

	sge::renderer::target::base &target_;

	sge::opengl::target::scoped const scoped_target_;

	typedef
	fcppt::unique_ptr<
		sge::opengl::target::scoped
	>
	scoped_offscreen_target_ptr;

	typedef
	fcppt::optional<
		scoped_offscreen_target_ptr
	>
	optional_scoped_offscreen_target_ptr;

	optional_scoped_offscreen_target_ptr scoped_offscreen_target_;
};

}
}
}

#endif
