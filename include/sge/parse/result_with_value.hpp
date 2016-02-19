/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PARSE_RESULT_WITH_VALUE_HPP_INCLUDED
#define SGE_PARSE_RESULT_WITH_VALUE_HPP_INCLUDED

#include <sge/parse/result.hpp>
#include <sge/parse/result_with_value_fwd.hpp>
#include <sge/parse/detail/symbol.hpp>
#include <fcppt/optional/object_impl.hpp>


namespace sge
{
namespace parse
{

template<
	typename Start
>
class result_with_value
{
public:
	typedef fcppt::optional::object<
		Start
	> optional_start;

	SGE_PARSE_DETAIL_SYMBOL
	result_with_value(
		optional_start const &,
		sge::parse::result const &
	);

	SGE_PARSE_DETAIL_SYMBOL
	optional_start const &
	start() const;

	SGE_PARSE_DETAIL_SYMBOL
	sge::parse::result const &
	result() const;
private:
	optional_start start_;

	sge::parse::result result_;
};

}
}

#endif
