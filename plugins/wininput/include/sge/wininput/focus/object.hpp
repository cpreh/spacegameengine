//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WININPUT_FOCUS_OBJECT_HPP_INCLUDED
#define SGE_WININPUT_FOCUS_OBJECT_HPP_INCLUDED

#include <sge/input/focus/object.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/wininput/focus/object_fwd.hpp>
#include <awl/backends/windows/window/event/generic_fwd.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace wininput
{
namespace focus
{

class object
:
	public
		sge::input::focus::object,
	public
		fcppt::enable_shared_from_this<
			sge::wininput::focus::object
		>
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::window::object_ref
	);

	~object()
	override;

	sge::window::object &
	window() const
	override;
private:
	awl::event::container
	on_event(
		awl::window::event::base const &
	);

	awl::event::optional_base_unique_ptr
	on_window_event(
		awl::backends::windows::window::event::generic const &
	);

	awl::event::base_unique_ptr
	on_key(
		awl::backends::windows::window::event::generic const &,
		sge::input::key::pressed
	);

	sge::window::object_ref const window_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}
}

#endif
