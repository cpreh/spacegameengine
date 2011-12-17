/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_WINDOW_PARAMETERS_HPP_INCLUDED
#define SGE_WINDOW_PARAMETERS_HPP_INCLUDED

#include <sge/window/dim.hpp>
#include <sge/window/parameters_fwd.hpp>
#include <sge/window/size_hints.hpp>
#include <sge/window/symbol.hpp>
#include <sge/window/title.hpp>
#include <fcppt/string.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


namespace sge
{
namespace window
{

class parameters
{
public:
	SGE_WINDOW_SYMBOL
	parameters(
		sge::window::title const &,
		sge::window::dim const &
	);

	SGE_WINDOW_SYMBOL
	parameters &
	class_name(
		fcppt::string const &
	);

	SGE_WINDOW_SYMBOL
	parameters &
	size_hints(
		window::size_hints const &
	);

	SGE_WINDOW_SYMBOL
	sge::window::title const &
	title() const;

	SGE_WINDOW_SYMBOL
	sge::window::dim const &
	dim() const;

	SGE_WINDOW_SYMBOL
	fcppt::string const &
	class_name() const;

	SGE_WINDOW_SYMBOL
	window::size_hints const &
	size_hints() const;
private:
	sge::window::title title_;

	sge::window::dim dim_;

	fcppt::string class_name_;

	sge::window::size_hints size_hints_;
};

}
}

#endif
