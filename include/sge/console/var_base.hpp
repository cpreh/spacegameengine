/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CON_VAR_BASE_HPP_INCLUDED
#define SGE_CON_VAR_BASE_HPP_INCLUDED

#include "../string.hpp"
#include "../export.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace con
{

class SGE_CLASS_SYMBOL var_base : boost::noncopyable {
	string name_;
public:
	SGE_SYMBOL var_base(const string &);
	SGE_SYMBOL void late_construct();
	SGE_SYMBOL string const name() const;
#ifndef _MSC_VER
	virtual void set(const string &) = 0;
	virtual string const get() const = 0;
#else
	// VC++ is so dumb that it wants to instantiate a class
	// if you bind *this to a reference
	SGE_SYMBOL virtual void set(const string&);
	SGE_SYMBOL virtual string const get() const;
#endif
	SGE_SYMBOL virtual ~var_base();
};

}
}

#endif
