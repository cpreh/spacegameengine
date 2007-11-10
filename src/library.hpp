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

namespace sge
{

class library : boost::noncopyable {
private:
	void* handle;
public:
	SGE_SYMBOL library(const std::string& path);
	SGE_SYMBOL ~library();

	template<typename Fun>
	Fun load_function(const std::string& fun);

	SGE_SYMBOL const std::string& name() const;

private:
	typedef void*(*base_fun)();
	base_fun load_address_base(const std::string& fun);

	static std::string liberror();

	std::string n;
public:
	struct load_function_exception : public exception {
		std::string lib, func;
		load_function_exception(const std::string &lib, const std::string &fun)
		: exception("failed to load function " + fun + " from library " + lib + " : " + liberror())
		, lib(lib)
		, func(fun) {}
		~load_function_exception() throw() {}
	};
};

}

#include "detail/library_impl.hpp"

#endif
