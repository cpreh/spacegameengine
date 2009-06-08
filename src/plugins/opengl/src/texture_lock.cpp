/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../texture_lock.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::texture_lock::texture_lock()
{}

sge::ogl::texture_lock::~texture_lock()
{}

sge::ogl::texture_lock::pointer
sge::ogl::texture_lock::write_pointer() const
{
	throw exception(
		SGE_TEXT("Can't get a write pointer to a lock!"));
}

sge::ogl::texture_lock::pointer
sge::ogl::texture_lock::read_pointer() const
{
	throw exception(
		SGE_TEXT("Can't get a read pointer to a lock!"));
}

sge::ogl::texture_lock::pointer
sge::ogl::texture_lock::real_write_pointer()
{
	throw exception(
		SGE_TEXT("Can't get a real write pointer to a lock!"));
}

sge::ogl::texture_lock::const_pointer
sge::ogl::texture_lock::real_read_pointer() const
{
	throw exception(
		SGE_TEXT("Can't get a real read pointer to a lock!"));
}
