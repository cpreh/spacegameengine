//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_SDL_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_SDL_CONTEXT_HPP_INCLUDED

#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace sdl
{

class context
:
	public
		sge::opengl::backend::context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	explicit
	context(
		sge::window::object &
	);

	~context()
	override;

	sge::opengl::backend::current_unique_ptr
	activate()
	override;

	void
	deactivate(
		sge::opengl::backend::current_unique_ptr &&
	)
	override;
private:
	awl::backends::sdl::window::object &window_;

	SDL_GLContext const context_;
};

}
}
}

#endif
