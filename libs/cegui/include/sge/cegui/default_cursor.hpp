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


#ifndef SGE_CEGUI_DEFAULT_CURSOR_HPP_INCLUDED
#define SGE_CEGUI_DEFAULT_CURSOR_HPP_INCLUDED

#include <sge/cegui/syringe_fwd.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace cegui
{

class default_cursor
{
	FCPPT_NONCOPYABLE(
		default_cursor
	);
public:
	SGE_CEGUI_DETAIL_SYMBOL
	explicit
	default_cursor(
		sge::cegui::syringe &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	~default_cursor();

	SGE_CEGUI_DETAIL_SYMBOL
	void
	process_event(
		sge::input::event_base const &
	);
private:
	sge::cegui::syringe &syringe_;
};

}
}

#endif
