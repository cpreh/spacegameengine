/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_RENDER_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_D3D9_RENDER_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/d3d9/render_context/parameters.hpp>
#include <sge/d3d9/render_context/scoped_target.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/primitive_type_fwd.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
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
#include <sge/renderer/state/ffp/transform/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/transform/mode_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/offscreen_fwd.hpp>
#include <sge/renderer/texture/const_optional_base_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/d3d9/cg/scoped_device.hpp>
#include <sge/renderer/cg/loaded_program_fwd.hpp>
#include <sge/renderer/cg/loaded_texture_fwd.hpp>
#endif


namespace sge
{
namespace d3d9
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
	explicit
	object(
		sge::d3d9::render_context::parameters const &
	);

	~object();

	bool
	needs_present() const;
private:
	sge::renderer::target::base &
	target();

	void
	clear(
		sge::renderer::clear::parameters const &
	);

	void
	offscreen_target(
		sge::renderer::target::optional_offscreen_ref const &
	);

	void
	render_indexed(
		sge::renderer::index::buffer const &,
		sge::renderer::vertex::first,
		sge::renderer::vertex::count,
		sge::renderer::primitive_type,
		sge::renderer::index::first,
		sge::renderer::index::count
	);

	void
	render_nonindexed(
		sge::renderer::vertex::first,
		sge::renderer::vertex::count,
		sge::renderer::primitive_type
	);

	void
	activate_vertex_buffer(
		sge::renderer::vertex::buffer const &
	);

	void
	deactivate_vertex_buffer(
		sge::renderer::vertex::buffer const &
	);

	void
	vertex_declaration(
		sge::renderer::vertex::const_optional_declaration_ref const &
	);

	void
	texture(
		sge::renderer::texture::const_optional_base_ref const &,
		sge::renderer::texture::stage
	) ;

	void
	blend_state(
		sge::renderer::state::core::blend::const_optional_object_ref const &
	);

	void
	depth_stencil_state(
		sge::renderer::state::core::depth_stencil::const_optional_object_ref const &
	);

	void
	rasterizer_state(
		sge::renderer::state::core::rasterizer::const_optional_object_ref const &
	);

	void
	sampler_state(
		sge::renderer::state::core::sampler::const_optional_object_ref_map const &
	);

#if defined(SGE_RENDERER_HAVE_CG)
	void
	set_cg_program(
		sge::renderer::cg::loaded_program const &
	);

	void
	unset_cg_program(
		sge::renderer::cg::loaded_program const &
	);

	sge::renderer::texture::stage const
	set_cg_texture(
		sge::renderer::cg::loaded_texture const &
	);

	void
	unset_cg_texture(
		sge::renderer::cg::loaded_texture const &
	);
#endif

	void
	alpha_test_state(
		sge::renderer::state::ffp::alpha_test::const_optional_object_ref const &
	);

	void
	clip_plane_state(
		sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &
	);

	void
	fog_state(
		sge::renderer::state::ffp::fog::const_optional_object_ref const &
	);

	void
	lighting_state(
		sge::renderer::state::ffp::lighting::const_optional_object_ref const &
	);

	void
	lights_state(
		sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &
	);

	void
	material_state(
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref const &
	);

	void
	misc_state(
		sge::renderer::state::ffp::misc::const_optional_object_ref const &
	);

	void
	sampler_ffp_state(
		sge::renderer::state::ffp::sampler::const_object_ref_vector const &
	);

	void
	transform(
		sge::renderer::state::ffp::transform::mode,
		sge::renderer::state::ffp::transform::const_optional_object_ref const &
	);

	sge::d3d9::render_context::parameters const parameters_;

	sge::d3d9::render_context::scoped_target const scoped_target_;

	typedef fcppt::optional<
		sge::d3d9::target::base &
	> optional_target_base_ref;

	optional_target_base_ref offscreen_target_;

#if defined(SGE_RENDERER_HAVE_CG)
	sge::d3d9::cg::scoped_device const scoped_cg_device_;
#endif
};

}
}
}

#endif
