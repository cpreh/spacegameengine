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


#ifndef SGE_SYSTEMS_ORIGINAL_WINDOW_HPP_INCLUDED
#define SGE_SYSTEMS_ORIGINAL_WINDOW_HPP_INCLUDED

#include <sge/systems/original_window_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <sge/window/dim_fwd.hpp>
#include <sge/window/optional_dim.hpp>
#include <sge/window/size_hints.hpp>
#include <sge/window/title.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace systems
{

class original_window
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	explicit
	original_window(
		sge::window::title const &
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::original_window &
	dim(
		sge::window::dim
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::original_window &
	class_name(
		fcppt::string const &
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::original_window &
	size_hints(
		sge::window::size_hints const &
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::original_window &
	hide_cursor();

	sge::window::title const &
	title() const;

	sge::window::optional_dim const &
	dim() const;

	fcppt::string const &
	class_name() const;

	sge::window::size_hints const &
	size_hints() const;

	bool
	hide_cursor() const;
private:
	sge::window::title title_;

	fcppt::string class_name_;

	sge::window::optional_dim dim_;

	sge::window::size_hints size_hints_;

	bool hide_cursor_;
};

}
}

#endif
