//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CG_TEXTURE_LOADED_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_CG_TEXTURE_LOADED_OBJECT_HPP_INCLUDED

#include <sge/cg/parameter/object.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/texture/base_fwd.hpp>
#include <sge/opengl/texture/bind_context_fwd.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/texture/base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_reference.hpp>


namespace sge::opengl::cg::texture
{

class loaded_object
:
	public sge::renderer::cg::loaded_texture
{
	FCPPT_NONMOVABLE(
		loaded_object
	);
public:
	loaded_object(
		fcppt::log::object_reference,
		sge::opengl::context::object_ref,
		sge::cg::parameter::object const &,
		sge::renderer::texture::base_ref
	);

	~loaded_object()
	override;

	[[nodiscard]]
	sge::renderer::texture::stage
	enable() const;

	void
	disable() const;
private:
	fcppt::log::object_reference const log_;

	sge::opengl::context::object_ref const context_;

	fcppt::reference<
		sge::opengl::texture::bind_context
	> const bind_context_;

	sge::cg::parameter::object const parameter_;

	fcppt::reference<
		sge::opengl::texture::base const
	> const texture_;

	sge::renderer::texture::stage const stage_;
};

}

#endif
