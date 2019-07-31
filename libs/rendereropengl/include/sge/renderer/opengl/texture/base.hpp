//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_OPENGL_TEXTURE_BASE_HPP_INCLUDED
#define SGE_RENDERER_OPENGL_TEXTURE_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/opengl/detail/symbol.hpp>
#include <sge/renderer/opengl/texture/base_fwd.hpp>
#include <sge/renderer/opengl/texture/id.hpp>
#include <sge/renderer/opengl/texture/type.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace opengl
{
namespace texture
{

class SGE_CORE_DETAIL_CLASS_SYMBOL base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	SGE_RENDERER_OPENGL_DETAIL_SYMBOL
	base();
public:
	virtual
	sge::renderer::opengl::texture::id
	id() const = 0;

	virtual
	sge::renderer::opengl::texture::type
	type() const = 0;

	SGE_RENDERER_OPENGL_DETAIL_SYMBOL
	virtual
	~base();
};

}
}
}
}

#endif
