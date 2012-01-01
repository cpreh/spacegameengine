/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_EXCEPTION_HPP_INCLUDED
#define SGE_RENDERER_EXCEPTION_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/exception.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief The base class for every renderer exception
*/
class SGE_CLASS_SYMBOL exception
:
	public sge::exception
{
public:
	/**
	 * \brief Constructs the exception from a string
	 *
	 * Constructs the exception from \a what
	*/
	SGE_RENDERER_SYMBOL
	explicit exception(
		fcppt::string const &what
	);

	/**
	 * \brief Constructs the exception from an assert info
	 *
	 * Constructs the exception from \a info
	*/
	SGE_RENDERER_SYMBOL
	explicit exception(
		fcppt::assert_::information const &info
	);
};

}
}

#endif
