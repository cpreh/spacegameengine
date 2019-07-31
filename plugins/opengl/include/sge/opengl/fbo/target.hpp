//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_TARGET_HPP_INCLUDED
#define SGE_OPENGL_FBO_TARGET_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/fbo/attachment_fwd.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/attachment_unique_ptr.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/context_fwd.hpp>
#include <sge/opengl/fbo/last_context_fwd.hpp>
#include <sge/opengl/fbo/object.hpp>
#include <sge/opengl/fbo/render_buffer_fwd.hpp>
#include <sge/opengl/fbo/target_fwd.hpp>
#include <sge/opengl/target/basic.hpp>
#include <sge/opengl/texture/buffer_base_fwd.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/optional_surface_ref_fwd.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef_std_hash.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

class target
:
	public sge::opengl::target::basic<
		sge::renderer::target::offscreen
	>
{
	FCPPT_NONCOPYABLE(
		target
	);
public:
	typedef
	sge::opengl::target::basic<
		sge::renderer::target::offscreen
	>
	base;

	explicit
	target(
		sge::opengl::context::object &
	);

	~target()
	override;
private:
	void
	on_bind()
	override;

	void
	on_unbind()
	override;

	void
	end_rendering()
	override;

	void
	color_surface(
		sge::renderer::color_buffer::optional_surface_ref const &,
		sge::renderer::target::surface_index
	)
	override;

	void
	depth_stencil_surface(
		sge::renderer::depth_stencil_buffer::optional_surface_ref const &
	)
	override;

	sge::renderer::screen_unit
	height() const
	override;

	sge::opengl::fbo::attachment_unique_ptr
	create_texture_binding(
		sge::opengl::texture::buffer_base &,
		sge::opengl::fbo::attachment_type
	);

	sge::opengl::fbo::attachment_unique_ptr
	create_buffer_binding(
		sge::opengl::fbo::render_buffer const &,
		sge::opengl::fbo::attachment_type
	);

	void
	check();

	sge::opengl::fbo::context &context_;

	sge::opengl::fbo::config const &config_;

	sge::opengl::fbo::last_context &last_context_;

	sge::opengl::fbo::object fbo_;

	typedef fcppt::optional::object<
		sge::renderer::screen_unit
	> optional_screen_unit;

	optional_screen_unit height_;

	typedef
	std::unordered_map<
		sge::renderer::target::surface_index,
		sge::opengl::fbo::attachment_unique_ptr
	>
	attachment_map;

	attachment_map color_attachments_;

	typedef
	fcppt::optional::object<
		sge::opengl::fbo::attachment_unique_ptr
	>
	optional_attachment_unique_ptr;

	optional_attachment_unique_ptr depth_stencil_attachment_;
};

}
}
}

#endif
