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


#ifndef SGE_CG_PARAMETER_DETAIL_CHECK_BASE_TYPE_HPP_INCLUDED
#define SGE_CG_PARAMETER_DETAIL_CHECK_BASE_TYPE_HPP_INCLUDED

#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/detail/pp_types.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{
namespace detail
{

template<
	typename Type
>
SGE_CG_DETAIL_SYMBOL
void
check_base_type(
	sge::cg::parameter::object const &
);

}
}
}
}

#define SGE_CG_PARAMETER_DETAIL_DECLARE_CHECK_BASE_TYPE(\
	seq,\
	_,\
	base_type\
)\
extern \
template \
SGE_CG_DETAIL_SYMBOL \
void \
sge::cg::parameter::detail::check_base_type<\
	base_type\
>(\
	sge::cg::parameter::object const &\
);\

BOOST_PP_SEQ_FOR_EACH(
	SGE_CG_PARAMETER_DETAIL_DECLARE_CHECK_BASE_TYPE,
	_,
	SGE_CG_PARAMETER_DETAIL_PP_TYPES
)

#endif
