//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/exception.hpp>
#include <sge/cg/impl/parameter/get_type.hpp>
#include <sge/cg/impl/parameter/get_type_base.hpp>
#include <sge/cg/impl/parameter/type_base_enum.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/detail/check_base_type.hpp>
#include <sge/cg/parameter/detail/pp_types.hpp>
#include <sge/core/impl/export_function_instantiation.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Type
>
void
sge::cg::parameter::detail::check_base_type(
	sge::cg::parameter::object const &_parameter
)
{
	if(
		sge::cg::impl::parameter::get_type_base(
			sge::cg::impl::parameter::get_type(
				_parameter
			)
		)
		!=
		sge::cg::impl::parameter::type_base_enum<
			Type
		>::value
	)
	{
		throw
			sge::cg::exception{
				FCPPT_TEXT("Unexpected base type.")
			};
	}
}

#define SGE_CG_INSTANTIATE_PARAMETER_DETAIL_CHECK_BASE_TYPE(\
	seq,\
	_,\
	base_type\
)\
template \
SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
void \
sge::cg::parameter::detail::check_base_type<\
	base_type\
>(\
	sge::cg::parameter::object const &\
);\

BOOST_PP_SEQ_FOR_EACH(
	SGE_CG_INSTANTIATE_PARAMETER_DETAIL_CHECK_BASE_TYPE,
	_,
	SGE_CG_PARAMETER_DETAIL_PP_TYPES
)
