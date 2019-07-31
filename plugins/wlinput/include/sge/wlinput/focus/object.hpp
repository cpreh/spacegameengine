//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_FOCUS_OBJECT_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_OBJECT_HPP_INCLUDED

#include <sge/input/focus/object.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/wlinput/xkb_context_fwd.hpp>
#include <sge/wlinput/focus/data.hpp>
#include <sge/wlinput/focus/holder.hpp>
#include <sge/wlinput/focus/object_fwd.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace wlinput
{
namespace focus
{

class object
:
	public
		sge::input::focus::object,
	public
		fcppt::enable_shared_from_this<
			sge::wlinput::focus::object
		>
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		fcppt::log::object &,
		sge::window::object &,
		sge::wlinput::xkb_context const &,
		awl::backends::wayland::window::object const &,
		awl::event::container_reference,
		awl::backends::wayland::seat const &
	);

	~object()
	override;

	sge::window::object &
	window() const
	override;

	sge::input::focus::shared_ptr
	get_shared_ptr();
private:
	awl::event::container
	on_key_repeat();

	sge::wlinput::focus::holder const impl_;

	sge::wlinput::focus::data data_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}
}

#endif
