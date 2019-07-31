//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_WGL_CONTEXT_HOLDER_HPP_INCLUDED
#define SGE_OPENGL_WGL_CONTEXT_HOLDER_HPP_INCLUDED

#include <sge/opengl/wgl/context_holder_fwd.hpp>
#include <sge/opengl/windows/gdi_device_fwd.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace wgl
{

class context_holder
{
	FCPPT_NONCOPYABLE(
		context_holder
	);
public:
	explicit
	context_holder(
		sge::opengl::windows::gdi_device const &
	);

	~context_holder();

	HGLRC
	get() const;
private:
	HGLRC const glrc_;
};

}
}
}

#endif
