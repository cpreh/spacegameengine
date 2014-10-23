/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PARSE_PARSE_EXCEPTION_HPP_INCLUDED
#define SGE_PARSE_PARSE_EXCEPTION_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/parse/error_string.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/parse_exception_fwd.hpp>
#include <sge/parse/result_code.hpp>
#include <sge/parse/detail/symbol.hpp>


namespace sge
{
namespace parse
{

class SGE_CORE_DETAIL_CLASS_SYMBOL parse_exception
:
	public sge::parse::exception
{
public:
	SGE_PARSE_DETAIL_SYMBOL
	parse_exception(
		sge::parse::result_code,
		sge::parse::error_string const &
	);

	SGE_PARSE_DETAIL_SYMBOL
	sge::parse::result_code
	result_code() const;

	SGE_PARSE_DETAIL_SYMBOL
	sge::parse::error_string const &
	error_string() const;

	SGE_PARSE_DETAIL_SYMBOL
	~parse_exception() throw()
	override;
private:
	sge::parse::result_code result_code_;

	sge::parse::error_string error_string_;
};

}
}

#endif
