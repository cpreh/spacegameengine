//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_SURFACE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_SURFACE_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/texture/surface_config.hpp>
#include <sge/opengl/texture/surface_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class surface_context
:
	public sge::opengl::context::base
{
	FCPPT_NONMOVABLE(
		surface_context
	);
public:
	using
	parameter
	=
	void;

	surface_context();

	~surface_context()
	override;

	[[nodiscard]]
	sge::opengl::texture::surface_config const &
	config() const;

	static sge::opengl::context::id const static_id;
private:
	sge::opengl::texture::surface_config const config_;
};

}
}
}

#endif
