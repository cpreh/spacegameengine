//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
