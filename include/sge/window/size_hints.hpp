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


#ifndef SGE_WINDOW_SIZE_HINTS_HPP_INCLUDED
#define SGE_WINDOW_SIZE_HINTS_HPP_INCLUDED

#include <sge/window/size_hints_fwd.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/optional_dim.hpp>
#include <sge/symbol.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>

namespace sge
{
namespace window
{

class size_hints
{
public:
	SGE_SYMBOL
	size_hints();

	SGE_SYMBOL
	size_hints &
	exact_size_hint(
		window::dim const &
	);

	SGE_SYMBOL
	size_hints &
	minimum_size_hint(
		window::dim const &
	);

	SGE_SYMBOL
	size_hints &
	maximum_size_hint(
		window::dim const &
	);

	SGE_SYMBOL
	window::optional_dim const &
	exact_size_hint() const;

	SGE_SYMBOL
	window::optional_dim const &
	minimum_size_hint() const;

	SGE_SYMBOL
	window::optional_dim const &
	maximum_size_hint() const;
private:
	window::optional_dim
		exact_size_hint_,
		minimum_size_hint_,
		maximum_size_hint_;
};

}
}

#endif
