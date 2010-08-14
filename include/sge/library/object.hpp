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


#ifndef SGE_LIBRARY_OBJECT_HPP_INCLUDED
#define SGE_LIBRARY_OBJECT_HPP_INCLUDED

#include <sge/library/function_string.hpp>
#include <sge/symbol.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config.hpp>
#ifdef FCPPT_WINDOWS_PLATFORM
#include <fcppt/scoped_ptr.hpp>
#endif

namespace sge
{
namespace library
{

class object
{
	FCPPT_NONCOPYABLE(object)
public:
	SGE_SYMBOL explicit object(
		fcppt::filesystem::path const &
	);

	SGE_SYMBOL ~object();

	template<
		typename Fun
	>
	Fun
	load_function(
		function_string const &
	);

	SGE_SYMBOL fcppt::filesystem::path const &
	name() const;
private:
	typedef void *(*base_fun)();

	SGE_SYMBOL base_fun
	load_address_base(
		function_string const &
	);

	void *const handle;
#ifdef FCPPT_WINDOWS_PLATFORM
	struct destroyer;
	fcppt::scoped_ptr<
		destroyer
	> destroyer_;
#endif
	fcppt::filesystem::path const name_;
};

}
}

#endif
