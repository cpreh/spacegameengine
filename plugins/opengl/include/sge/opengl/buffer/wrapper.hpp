//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_WRAPPER_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_WRAPPER_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/object_fwd.hpp>
#include <sge/renderer/opengl/buffer/base.hpp>
#include <sge/renderer/opengl/buffer/id.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class wrapper
:
	public sge::renderer::opengl::buffer::base
{
	FCPPT_NONMOVABLE(
		wrapper
	);
protected:
	wrapper();

	~wrapper()
	override = 0;

	[[nodiscard]]
	virtual
	sge::opengl::buffer::object const &
	get() const = 0;
private:
	[[nodiscard]]
	sge::renderer::opengl::buffer::id
	id() const
	override;

	[[nodiscard]]
	bool
	native() const
	override;
};

}
}
}

#endif
