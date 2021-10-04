//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_RENDER_BINDING_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_RENDER_BINDING_HPP_INCLUDED

#include <sge/opengl/texture/active_level_fwd.hpp>
#include <sge/opengl/texture/binding.hpp>
#include <sge/opengl/texture/render_binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::opengl::texture
{

class render_binding
:
	public sge::opengl::texture::binding
{
	FCPPT_NONMOVABLE(
		render_binding
	);
public:
	render_binding(
		sge::opengl::texture::active_level const &,
		sge::opengl::texture::type
	);

	~render_binding()
	override;

	[[nodiscard]]
	sge::renderer::texture::stage
	stage() const
	override;

	[[nodiscard]]
	sge::opengl::texture::type
	type() const
	override;
private:
	sge::renderer::texture::stage const stage_;

	sge::opengl::texture::type const type_;
};

}

#endif
