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


#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/detail/check_base_type.hpp>
#include <sge/cg/parameter/detail/generate_types.hpp>
#include <sge/src/core/export_function_instantiation.hpp>
#include <sge/src/cg/parameter/get_type.hpp>
#include <sge/src/cg/parameter/get_type_base.hpp>
#include <sge/src/cg/parameter/type_base_enum.hpp>
#include <fcppt/assert/error.hpp>


template<
	typename Type
>
void
sge::cg::parameter::detail::check_base_type(
	sge::cg::parameter::object const &_parameter
)
{
	FCPPT_ASSERT_ERROR(
		sge::cg::parameter::get_type_base(
			sge::cg::parameter::get_type(
				_parameter
			)
		)
		==
		sge::cg::parameter::type_base_enum<
			Type
		>::value
	);
}

#define SGE_CG_INSTANTIATE_PARAMETER_DETAIL_CHECK_BASE_TYPE(\
	type\
)\
template \
SGE_CORE_EXPORT_FUNCTION_INSTANTIATION \
void \
sge::cg::parameter::detail::check_base_type<\
	type\
>(\
	sge::cg::parameter::object const &\
);\

SGE_CG_PARAMETER_DETAIL_GENERATE_TYPES(
	SGE_CG_INSTANTIATE_PARAMETER_DETAIL_CHECK_BASE_TYPE
)
