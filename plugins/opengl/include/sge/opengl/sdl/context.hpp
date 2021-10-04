//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_SDL_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_SDL_CONTEXT_HPP_INCLUDED

#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/sdl/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::sdl
{

class context
:
	public
		sge::opengl::backend::context
{
	FCPPT_NONMOVABLE(
		context
	);
public:
	explicit
	context(
		sge::window::object_ref
	);

	~context()
	override;

	[[nodiscard]]
	sge::opengl::backend::current_unique_ptr
	activate()
	override;

	void
	deactivate(
		sge::opengl::backend::current_unique_ptr &&
	)
	override;
private:
	awl::backends::sdl::window::object_ref const window_;

	SDL_GLContext const context_; // NOLINT(misc-misplaced-const)
};

}

#endif
