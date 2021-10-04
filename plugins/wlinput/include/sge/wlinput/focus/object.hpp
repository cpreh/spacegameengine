//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_FOCUS_OBJECT_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_OBJECT_HPP_INCLUDED

#include <sge/input/focus/object.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/wlinput/xkb_context_ref.hpp>
#include <sge/wlinput/focus/data.hpp>
#include <sge/wlinput/focus/holder.hpp>
#include <sge/wlinput/focus/object_fwd.hpp>
#include <awl/backends/wayland/seat_ref.hpp>
#include <awl/backends/wayland/window/object_ref.hpp>
#include <awl/event/container.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge::wlinput::focus
{

class object // NOLINT(fuchsia-multiple-inheritance)
:
	public
		sge::input::focus::object,
	public
		fcppt::enable_shared_from_this<
			sge::wlinput::focus::object
		>
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		fcppt::log::object_reference,
		sge::window::object_ref,
		sge::wlinput::xkb_context_ref,
		awl::backends::wayland::window::object_ref,
		awl::event::container_reference,
		awl::backends::wayland::seat_ref
	);

	~object()
	override;

	[[nodiscard]]
	sge::window::object &
	window() const
	override;

	[[nodiscard]]
	sge::input::focus::shared_ptr
	get_shared_ptr();
private:
	[[nodiscard]]
	awl::event::container
	on_key_repeat();

	sge::wlinput::focus::holder const impl_;

	sge::wlinput::focus::data data_;

	fcppt::signal::auto_connection const event_connection_;
};

}

#endif
