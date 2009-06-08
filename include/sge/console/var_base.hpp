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


#ifndef SGE_CONSOLE_VAR_BASE_HPP_INCLUDED
#define SGE_CONSOLE_VAR_BASE_HPP_INCLUDED

#include <sge/console/object_fwd.hpp>
#include <sge/string.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace console
{
class SGE_CLASS_SYMBOL var_base
{
	SGE_NONCOPYABLE(var_base)
	public:
	SGE_SYMBOL var_base(
		object &,
		sge::string const &);
	
	virtual void string(sge::string const &) = 0;
	virtual sge::string const string() const = 0;

	SGE_SYMBOL sge::string const name() const;
	
	virtual ~var_base();
	private:
	object &object_;
	sge::string name_;
};
}
}

#endif
