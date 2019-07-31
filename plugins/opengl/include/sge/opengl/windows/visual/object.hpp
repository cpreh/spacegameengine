//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_WINDOWS_VISUAL_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_WINDOWS_VISUAL_OBJECT_HPP_INCLUDED

#include <sge/opengl/wgl/visual/config_fwd.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/visual/object.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace windows
{
namespace visual
{

class object
:
	public awl::backends::windows::visual::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::opengl::wgl::visual::config const &,
		sge::renderer::pixel_format::object const &
	);

	~object()
	override;
private:
	void
	apply(
		HWND
	) const
	override;

	sge::opengl::wgl::visual::config const &config_;

	sge::renderer::pixel_format::object const format_;
};

}
}
}
}

#endif
