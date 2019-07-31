//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_VISUAL_BASE_HPP_INCLUDED
#define SGE_OPENGL_EGL_VISUAL_BASE_HPP_INCLUDED

#include <sge/opengl/egl/visual/base_fwd.hpp>
#include <sge/renderer/visual_base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{
namespace visual
{

class base
:
	public sge::renderer::visual_base
{
	FCPPT_NONCOPYABLE(
		base
	);
public:
	base(
		fcppt::log::object &,
		EGLDisplay,
		sge::renderer::pixel_format::object const &
	);

	virtual
	~base() = 0;

	EGLConfig
	config() const;
private:
	EGLConfig const config_;
};

}
}
}
}

#endif
