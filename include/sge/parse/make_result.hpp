/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PARSE_MAKE_RESULT_HPP_INCLUDED
#define SGE_PARSE_MAKE_RESULT_HPP_INCLUDED

#include <sge/parse/result_code.hpp>
#include <sge/parse/result.hpp>


namespace sge
{
namespace parse
{

template<
	typename In,
	typename Grammar
>
sge::parse::result const
make_result(
	bool const _retval,
	In &_begin,
	In const &_end,
	Grammar const &_grammar
)
{
	return
		sge::parse::result(
			_retval
			?
				_begin
				==
				_end
				?
					sge::parse::result_code::ok
				:
					sge::parse::result_code::partial
			:
				sge::parse::result_code::failure
			,
			_grammar.error_string()
		);
}

}
}

#endif
