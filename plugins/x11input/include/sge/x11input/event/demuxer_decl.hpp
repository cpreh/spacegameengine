//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_EVENT_DEMUXER_DECL_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_DEMUXER_DECL_HPP_INCLUDED

#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/demuxer_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
#include <awl/event/container.hpp>
#include <fcppt/function_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef_std_hash.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/unregister/base_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace event
{

template<
	typename Event
>
class demuxer
{
	FCPPT_NONCOPYABLE(
		demuxer
	);
public:
	using
	function_type
	=
	awl::event::container (
		Event const &
	);

	typedef
	fcppt::function<
		function_type
	>
	function;

	explicit
	demuxer(
		awl::backends::x11::window::base const &
	);

	~demuxer();

	awl::backends::x11::window::base const &
	window() const;

	fcppt::signal::auto_connection
	on_event(
		sge::x11input::device::id,
		function
	);

	awl::event::container
	call(
		Event const &
	);
private:
	awl::backends::x11::window::base const &window_;

	typedef
	fcppt::signal::object<
		function_type,
		fcppt::signal::unregister::base
	>
	signal_type;

	typedef
	std::unordered_map<
		sge::x11input::device::id,
		signal_type
	>
	signal_map;

	signal_map signals_;
};


}
}
}

#endif
