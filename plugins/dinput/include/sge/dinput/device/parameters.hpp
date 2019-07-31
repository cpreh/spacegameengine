//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_DEVICE_PARAMETERS_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_PARAMETERS_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/windows/system/event/handle_fwd.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace dinput
{
namespace device
{

class parameters
{
public:
	parameters(
		IDirectInput8 &,
		GUID,
		sge::window::object &,
		awl::backends::windows::window::object &,
		awl::backends::windows::system::event::handle &
	);

	IDirectInput8 &
	instance() const;

	GUID
	guid() const;

	sge::window::object &
	sge_window() const;

	awl::backends::windows::window::object &
	window() const;

	awl::backends::windows::system::event::handle &
	event_handle() const;
private:
	fcppt::reference<
		IDirectInput8
	> instance_;

	GUID guid_;

	fcppt::reference<
		sge::window::object
	> sge_window_;

	fcppt::reference<
		awl::backends::windows::window::object
	> window_;

	fcppt::reference<
		awl::backends::windows::system::event::handle
	> event_handle_;
};

}
}
}

#endif
