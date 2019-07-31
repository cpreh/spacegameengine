//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CG_TEXTURE_LOADED_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_CG_TEXTURE_LOADED_OBJECT_HPP_INCLUDED

#include <sge/cg/parameter/object.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/base_fwd.hpp>
#include <sge/opengl/texture/bind_context_fwd.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace cg
{
namespace texture
{

class loaded_object
:
	public sge::renderer::cg::loaded_texture
{
	FCPPT_NONCOPYABLE(
		loaded_object
	);
public:
	loaded_object(
		fcppt::log::object &,
		sge::opengl::context::object &,
		sge::cg::parameter::object const &,
		sge::renderer::texture::base &
	);

	~loaded_object()
	override;

	sge::renderer::texture::stage
	enable() const;

	void
	disable() const;
private:
	fcppt::log::object &log_;

	sge::opengl::context::object &context_;

	sge::opengl::texture::bind_context &bind_context_;

	sge::cg::parameter::object const parameter_;

	sge::opengl::texture::base const &texture_;

	sge::renderer::texture::stage const stage_;
};

}
}
}
}

#endif
