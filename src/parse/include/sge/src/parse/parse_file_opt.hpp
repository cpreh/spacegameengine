/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_PARSE_PARSE_FILE_OPT_HPP_INCLUDED
#define SGE_SRC_PARSE_PARSE_FILE_OPT_HPP_INCLUDED

#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>
#include <sge/parse/result_with_value.hpp>
#include <sge/src/parse/parse_file.hpp>


namespace sge
{
namespace parse
{

template<
	typename Result
>
sge::parse::result_with_value<
	Result
>
parse_file_opt(
	boost::filesystem::path const &_path
)
{
	Result value;

	sge::parse::result const result(
		sge::parse::parse_file(
			_path,
			value
		)
	);

	typedef sge::parse::result_with_value<
		Result
	> result_type;

	typedef typename result_type::optional_start optional_start;

	return
		sge::parse::result_with_value<
			Result
		>(
			result.result_code()
			==
			sge::parse::result_code::ok
			?
				optional_start(
					value
				)
			:
				optional_start()
			,
			result
		);
}

}
}

#endif
