//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_SDL_BACKEND_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_SDL_BACKEND_SYSTEM_HPP_INCLUDED

#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/sdl/library.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/sdl/system/init.hpp>
#include <awl/backends/sdl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace sdl
{

class backend_system
:
	public
		sge::opengl::backend::system
{
	FCPPT_NONCOPYABLE(
		backend_system
	);
public:
	explicit
	backend_system(
		awl::backends::sdl::system::object &
	);

	~backend_system()
	override;

	awl::visual::object_unique_ptr
	create_visual(
		sge::renderer::pixel_format::object const &
	)
	override;

	sge::opengl::backend::context_unique_ptr
	create_context(
		sge::window::object &
	)
	override;
private:
	awl::backends::sdl::system::init const init_video_;

	sge::opengl::sdl::library const library_;
};

}
}
}

#endif
