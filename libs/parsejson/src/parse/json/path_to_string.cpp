//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>


sge::charconv::utf8_string
sge::parse::json::path_to_string(
	sge::parse::json::path const &_path
)
{
	sge::charconv::utf8_string result{};

	// TODO
	for(auto i = _path.get().begin(); i != _path.get().end(); ++i)
	{
		result += *i;
		if(i != --_path.get().end())
			result += "/";
	}

	return result;
}
