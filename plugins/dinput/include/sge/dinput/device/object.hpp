//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_DEVICE_OBJECT_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_OBJECT_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/dinput_device_unique_ptr.hpp>
#include <sge/dinput/device/object_fwd.hpp>
#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace dinput
{
namespace device
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	awl::event::container
	dispatch();

	virtual
	~object() = 0;

	void
	acquire();

	void
	unacquire();
protected:
	object(
		sge::dinput::device::parameters const &,
		DIDATAFORMAT const &
	);

	IDirectInputDevice8 &
	get();

	sge::window::object &
	sge_window() const;
private:
	bool
	acquire_impl();

	void
	set_data_format(
		DIDATAFORMAT const &
	);

	void
	set_property(
		REFGUID,
		LPCDIPROPHEADER
	);

	void
	set_event_handle(
		HANDLE
	);

	virtual
	awl::event::optional_base_unique_ptr
	on_dispatch(
		DIDEVICEOBJECTDATA const &
	) = 0;

	sge::window::object &window_;

	sge::dinput::dinput_device_unique_ptr const device_;
};

}
}
}

#endif
