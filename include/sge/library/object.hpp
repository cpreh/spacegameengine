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


#ifndef SGE_LIBRARY_OBJECT_HPP_INCLUDED
#define SGE_LIBRARY_OBJECT_HPP_INCLUDED

#include <sge/config.h>
#include <sge/library/function_string.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>
#include <sge/filesystem/path.hpp>
#ifdef SGE_WINDOWS_PLATFORM
#include <sge/scoped_ptr.hpp>
#endif

namespace sge
{
namespace library
{

class object {
	SGE_NONCOPYABLE(object)
public:
	SGE_SYMBOL explicit object(
		filesystem::path const &);
	SGE_SYMBOL ~object();

	template<typename Fun>
	Fun load_function(
		function_string const &fun);

	SGE_SYMBOL filesystem::path const &
	name() const;
private:
	typedef void*(*base_fun)();
	SGE_SYMBOL base_fun
	load_address_base(
		function_string const &fun);

	void *const handle;
#ifdef SGE_WINDOWS_PLATFORM
	struct destroyer;
	scoped_ptr<
		destroyer
	> destroyer_;
#endif
	filesystem::path const name_;
};

}
}

#endif
