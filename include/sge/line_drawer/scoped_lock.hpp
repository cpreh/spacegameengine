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


#ifndef SGE_LINE_DRAWER_SCOPED_LOCK_HPP_INCLUDED
#define SGE_LINE_DRAWER_SCOPED_LOCK_HPP_INCLUDED

#include <sge/line_drawer/line_sequence.hpp>
#include <sge/line_drawer/object_fwd.hpp>
#include <sge/line_drawer/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace line_drawer
{
class scoped_lock
{
FCPPT_NONCOPYABLE(
	scoped_lock);
public:
	SGE_LINE_DRAWER_SYMBOL explicit
	scoped_lock(
		object &);

	SGE_LINE_DRAWER_SYMBOL line_sequence &
	value() const;

	SGE_LINE_DRAWER_SYMBOL ~scoped_lock();
private:
	object &object_;
};
}
}

#endif
