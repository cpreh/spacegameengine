//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_MOUSE_DEVICE_HPP_INCLUDED
#define SGE_SDLINPUT_MOUSE_DEVICE_HPP_INCLUDED

#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sdlinput
{
namespace mouse
{

class device
:
	public
		sge::input::mouse::device
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	explicit
	device(
		sge::window::object &
	);

	~device()
	override;

	sge::window::object &
	window() const
	override;

	sge::input::mouse::info const &
	info() const
	override;
private:
	sge::window::object &window_;

	sge::input::mouse::info const info_;
};

}
}
}

#endif
