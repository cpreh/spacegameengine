/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_WINDOW_SIMPLE_PARAMETERS_HPP_INCLUDED
#define SGE_WINDOW_SIMPLE_PARAMETERS_HPP_INCLUDED

#include <sge/window/simple_parameters_fwd.hpp>
#include <sge/window/dim_type.hpp>
#include <sge/symbol.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace window
{

class simple_parameters
{
public:
	SGE_SYMBOL
	explicit simple_parameters(
		fcppt::string const &title,
		sge::window::dim_type const &
	);

	SGE_SYMBOL
	simple_parameters &
	class_name(
		fcppt::string const &
	);

	SGE_SYMBOL
	fcppt::string const &
	title() const;

	SGE_SYMBOL
	sge::window::dim_type const &
	dim() const;

	SGE_SYMBOL
	fcppt::string const &
	class_name() const;
private:
	fcppt::string title_;

	sge::window::dim_type dim_;

	fcppt::string class_name_;
};

}
}

#endif
