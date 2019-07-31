//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_PLATFORM_DEVICE_STATE_HPP_INCLUDED
#define SGE_OPENGL_PLATFORM_DEVICE_STATE_HPP_INCLUDED

#include <sge/opengl/platform/device_state_fwd.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace platform
{

class device_state
{
	FCPPT_NONCOPYABLE(
		device_state
	);
protected:
	device_state();
public:
	virtual
	~device_state();

	virtual
	sge::renderer::display_mode::optional_object
	display_mode() const = 0;

	virtual
	void
	fullscreen(
		sge::renderer::display_mode::optional_fullscreen const &
	) = 0;
};

}
}
}

#endif
