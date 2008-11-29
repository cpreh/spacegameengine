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


#ifndef SGE_LIBRARY_HPP_INCLUDED
#define SGE_LIBRARY_HPP_INCLUDED

#include <string>
#include <boost/noncopyable.hpp>
#include "exception.hpp"
#include "export.hpp"
#include "path.hpp"

namespace sge
{

class library : boost::noncopyable {
private:
	void* handle;
public:
	SGE_SYMBOL explicit library(
		path const &);
	SGE_SYMBOL ~library();

	template<typename Fun>
	Fun load_function(const std::string& fun);

	SGE_SYMBOL const path& name() const;
private:
	typedef void*(*base_fun)();
	SGE_SYMBOL base_fun load_address_base(const std::string& fun);

	static string liberror();

	path name_;
public:
	struct load_function_exception : public exception {
		string lib;
		std::string func;
		SGE_SYMBOL load_function_exception(
			const string &lib,
			const std::string &fun);
	};
};

}

#endif
