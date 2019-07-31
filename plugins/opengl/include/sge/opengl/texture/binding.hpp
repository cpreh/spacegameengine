//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BINDING_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BINDING_HPP_INCLUDED

#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class binding
{
	FCPPT_NONCOPYABLE(
		binding
	);
protected:
	binding();

	virtual
	~binding();
public:
	virtual
	sge::renderer::texture::stage
	stage() const = 0;

	virtual
	sge::opengl::texture::type
	type() const = 0;
};

}
}
}

#endif
