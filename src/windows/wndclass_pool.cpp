/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2007       Simon Stienen    (s.stienen@slashlife.org)

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


#include <sge/windows/wndclass_pool.hpp>
#include <sge/windows/wndclass.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <map>

// TODO: we have to somehow free the weak_ptrs

namespace
{

typedef std::map<
	sge::string,
	boost::weak_ptr<
		sge::windows::wndclass
	>
> wndclass_map;

wndclass_map wndclasses;

}

wndclass_ptr const
wndclass_pool(
	string const &name,
	WNDPROC const proc)
{
	boost::weak_ptr &ptr(
		wndclasses[name]);
	
	{
		wndclass_ptr const ref(
			ptr.lock());
		if(ref)
			return ref;
	}

	wndclass_ptr const nref(
		make_shared_ptr<
			wndclass
		>(
			name,
			proc));
	ptr = nref.boost_ptr();

	return nref;
}
