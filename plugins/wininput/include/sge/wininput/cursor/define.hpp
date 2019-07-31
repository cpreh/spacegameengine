//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WININPUT_CURSOR_DEFINE_HPP_INCLUDED
#define SGE_WININPUT_CURSOR_DEFINE_HPP_INCLUDED

#include <sge/window/object_fwd.hpp>
#include <sge/wininput/cursor/define_fwd.hpp>
#include <sge/wininput/cursor/pixmap.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/event/generic_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace wininput
{
namespace cursor
{

class define
{
	FCPPT_NONCOPYABLE(
		define
	);
public:
	explicit
	define(
		sge::window::object &
	);

	~define();
private:
	awl::event::container
	on_event(
		awl::window::event::base const &
	);

	void
	on_cursor();

	typedef
	fcppt::optional::object<
		HCURSOR
	>
	optional_hcursor;

	optional_hcursor previous_cursor_;

	sge::wininput::cursor::pixmap const pixmap_;

	fcppt::signal::auto_connection const connection_;
};

}
}
}

#endif
