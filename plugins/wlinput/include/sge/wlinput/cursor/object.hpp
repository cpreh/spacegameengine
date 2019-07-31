//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_WLINPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/input/cursor/mode_fwd.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/wlinput/cursor/data.hpp>
#include <sge/wlinput/cursor/holder.hpp>
#include <sge/wlinput/cursor/object_fwd.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace wlinput
{
namespace cursor
{

class object
:
	public
		sge::input::cursor::object,
	public
		fcppt::enable_shared_from_this<
			sge::wlinput::cursor::object
		>
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::window::object &,
		awl::backends::wayland::window::object const &,
		awl::event::container_reference,
		awl::backends::wayland::seat const &
	);

	~object()
	override;

	sge::window::object &
	window() const
	override;

	sge::input::cursor::optional_position
	position() const
	override;

	void
	mode(
		sge::input::cursor::mode
	)
	override;

	sge::input::cursor::shared_ptr
	get_shared_ptr();
private:
	sge::window::object &window_;

	sge::wlinput::cursor::holder const impl_;

	sge::wlinput::cursor::data data_;
};

}
}
}

#endif
