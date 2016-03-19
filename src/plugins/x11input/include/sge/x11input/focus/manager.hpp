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


#ifndef SGE_X11INPUT_FOCUS_MANAGER_HPP_INCLUDED
#define SGE_X11INPUT_FOCUS_MANAGER_HPP_INCLUDED

#include <sge/input/focus/discover_event_fwd.hpp>
#include <sge/input/focus/remove_event_fwd.hpp>
#include <sge/x11input/focus/object_fwd.hpp>
#include <sge/x11input/focus/optional_ref_fwd.hpp>
#include <sge/x11input/device/id.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace focus
{

class manager
{
	FCPPT_NONCOPYABLE(
		manager
	);
public:
	manager();

	~manager();

	void
	discover(
		sge::input::focus::discover_event const &
	);

	void
	remove(
		sge::input::focus::remove_event const &
	);

	sge::x11input::focus::optional_ref
	focus(
		sge::x11input::device::id
	);
private:
	typedef
	std::unordered_map<
		sge::x11input::device::id,
		fcppt::reference<
			sge::x11input::focus::object
		>
	>
	object_set;

	object_set objects_;
};

}
}
}

#endif
