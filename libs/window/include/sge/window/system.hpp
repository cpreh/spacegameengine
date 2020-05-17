//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WINDOW_SYSTEM_HPP_INCLUDED
#define SGE_WINDOW_SYSTEM_HPP_INCLUDED

#include <sge/window/system_event_function.hpp>
#include <sge/window/system_event_function_type.hpp>
#include <sge/window/system_fwd.hpp>
#include <sge/window/detail/symbol.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/system/reference.hpp>
#include <awl/system/event/result_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace window
{

class system
{
	FCPPT_NONMOVABLE(
		system
	);
public:
	SGE_WINDOW_DETAIL_SYMBOL
	explicit
	system(
		awl::system::reference
	);

	SGE_WINDOW_DETAIL_SYMBOL
	~system();

	[[nodiscard]]
	SGE_WINDOW_DETAIL_SYMBOL
	awl::system::event::result
	poll();

	[[nodiscard]]
	SGE_WINDOW_DETAIL_SYMBOL
	awl::system::event::result
	next();

	SGE_WINDOW_DETAIL_SYMBOL
	void
	quit(
		awl::main::exit_code
	);

	[[nodiscard]]
	SGE_WINDOW_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	event_handler(
		sge::window::system_event_function &&
	);

	[[nodiscard]]
	SGE_WINDOW_DETAIL_SYMBOL
	awl::system::object &
	awl_system();
private:
	[[nodiscard]]
	awl::system::event::result
	transform_events(
		awl::system::event::result &&
	);

	awl::system::reference const awl_system_;

	using
	event_signal
	=
	fcppt::signal::object<
		sge::window::system_event_function_type
	>;

	event_signal event_signal_;
};

}
}

#endif
