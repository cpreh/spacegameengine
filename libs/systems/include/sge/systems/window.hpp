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


#ifndef SGE_SYSTEMS_WINDOW_HPP_INCLUDED
#define SGE_SYSTEMS_WINDOW_HPP_INCLUDED

#include <sge/systems/window_fwd.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace systems
{

class window
{
	FCPPT_NONASSIGNABLE(
		window
	);
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	explicit
	window(
		sge::systems::window_source const &
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::window &
	dont_show();

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::window &
	dont_quit();

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::window &
	hide_cursor();

	sge::systems::window_source const &
	source() const;

	bool
	show() const;

	bool
	quit() const;
private:
	sge::systems::window_source const source_;

	bool show_;

	bool quit_;
};

}
}

#endif
