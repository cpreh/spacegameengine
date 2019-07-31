//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_INIT_HPP_INCLUDED
#define SGE_OPENGL_EGL_INIT_HPP_INCLUDED

#include <sge/opengl/egl/init_fwd.hpp>
#include <sge/opengl/egl/version.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{

class init
{
	FCPPT_NONCOPYABLE(
		init
	);
public:
	explicit
	init(
		EGLDisplay
	);

	~init();

	sge::opengl::egl::version const
	version() const;
private:
	EGLDisplay const display_;

	sge::opengl::egl::version const version_;
};

}
}
}

#endif
