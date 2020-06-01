//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_OPENGL_BUFFER_BASE_HPP_INCLUDED
#define SGE_RENDERER_OPENGL_BUFFER_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/opengl/buffer/base_fwd.hpp>
#include <sge/renderer/opengl/buffer/id.hpp>
#include <sge/renderer/opengl/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace renderer
{
namespace opengl
{
namespace buffer
{

class SGE_CORE_DETAIL_CLASS_SYMBOL base
{
	FCPPT_NONMOVABLE(
		base
	);
protected:
	SGE_RENDERER_OPENGL_DETAIL_SYMBOL
	base();
public:
	SGE_RENDERER_OPENGL_DETAIL_SYMBOL
	virtual
	~base();

	[[nodiscard]]
	virtual
	sge::renderer::opengl::buffer::id
	id() const = 0;

	[[nodiscard]]
	virtual
	bool
	native() const = 0;
};

}
}
}
}

#endif
