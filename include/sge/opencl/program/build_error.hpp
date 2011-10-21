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


#ifndef SGE_OPENCL_PROGRAM_BUILD_ERROR_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_BUILD_ERROR_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/exception.hpp>
#include <sge/opencl/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace opencl
{
namespace program
{
class SGE_CLASS_SYMBOL build_error
:
	public sge::exception
{
public:
	SGE_OPENCL_SYMBOL explicit build_error(
		fcppt::string const &);

	SGE_OPENCL_SYMBOL fcppt::string const &
	message() const;

	SGE_OPENCL_SYMBOL
	virtual ~build_error() throw();
private:
	fcppt::string message_;
};
}
}
}

#endif
