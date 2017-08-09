/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_X11INPUT_EVENT_DEMUXER_DECL_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_DEMUXER_DECL_HPP_INCLUDED

#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/demuxer_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
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
