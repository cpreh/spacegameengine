//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BASE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASE_HPP_INCLUDED

#include <sge/opengl/texture/base_fwd.hpp>
#include <sge/opengl/texture/holder.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/opengl/texture/base.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::opengl::texture
{

class base
:
	public sge::renderer::opengl::texture::base
{
	FCPPT_NONMOVABLE(
		base
	);
public:
	[[nodiscard]]
	sge::opengl::texture::type
	type() const
	override;

	[[nodiscard]]
	sge::opengl::texture::id
	id() const
	override;

	~base()
	override = 0;
protected:
	explicit
	base(
		sge::opengl::texture::type
	);
private:
	sge::opengl::texture::type const type_;

	sge::opengl::texture::holder const holder_;
};

}

#endif
