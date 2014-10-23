/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/systems/original_window.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/wrapped_window.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


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
	typedef
	fcppt::variant::object<
		boost::mpl::vector2<
			sge::systems::original_window,
			sge::systems::wrapped_window
		>
	>
	parameter_variant;

	SGE_SYSTEMS_DETAIL_SYMBOL
	explicit
	window(
		parameter_variant const &
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

	parameter_variant const &
	parameter() const;

	bool
	show() const;

	bool
	quit() const;
private:
	parameter_variant const parameter_;

	bool show_;

	bool quit_;
};

}
}

#endif
