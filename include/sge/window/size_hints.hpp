/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_WINDOW_SIZE_HINTS_HPP_INCLUDED
#define SGE_WINDOW_SIZE_HINTS_HPP_INCLUDED

#include <sge/window/dim.hpp>
#include <sge/window/optional_dim.hpp>
#include <sge/window/size_hints_fwd.hpp>
#include <sge/window/detail/symbol.hpp>


namespace sge
{
namespace window
{

class size_hints
{
public:
	SGE_WINDOW_DETAIL_SYMBOL
	size_hints();

	SGE_WINDOW_DETAIL_SYMBOL
	sge::window::size_hints &
	exact_size_hint(
		sge::window::dim const &
	);

	SGE_WINDOW_DETAIL_SYMBOL
	sge::window::size_hints &
	minimum_size_hint(
		sge::window::dim const &
	);

	SGE_WINDOW_DETAIL_SYMBOL
	sge::window::size_hints &
	maximum_size_hint(
		sge::window::dim const &
	);

	SGE_WINDOW_DETAIL_SYMBOL
	sge::window::optional_dim const &
	exact_size_hint() const;

	SGE_WINDOW_DETAIL_SYMBOL
	sge::window::optional_dim const &
	minimum_size_hint() const;

	SGE_WINDOW_DETAIL_SYMBOL
	sge::window::optional_dim const &
	maximum_size_hint() const;
private:
	sge::window::optional_dim
		exact_size_hint_,
		minimum_size_hint_,
		maximum_size_hint_;
};

}
}

#endif
