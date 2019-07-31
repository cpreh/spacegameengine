//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PARAMETER_MATRIX_DETAIL_SET_HPP_INCLUDED
#define SGE_CG_PARAMETER_MATRIX_DETAIL_SET_HPP_INCLUDED

#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/detail/pp_types.hpp>
#include <sge/cg/parameter/matrix/detail/set_double.hpp>
#include <sge/cg/parameter/matrix/detail/set_float.hpp>
#include <sge/cg/parameter/matrix/detail/set_int.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{
namespace matrix
{
namespace detail
{

#define SGE_CG_PARAMETER_MATRIX_DETAIL_SET(\
	seq,\
	_,\
	type\
)\
template<\
	fcppt::math::size_type R,\
	fcppt::math::size_type C,\
	typename S\
>\
void \
set(\
	sge::cg::parameter::object const &_parameter,\
	fcppt::math::matrix::object<\
		type,\
		R,\
		C,\
		S\
	> const &_matrix\
)\
{\
	sge::cg::parameter::matrix::detail:: BOOST_PP_CAT(set_, type)(\
		_parameter,\
		_matrix.storage().data()\
	);\
}

BOOST_PP_SEQ_FOR_EACH(
	SGE_CG_PARAMETER_MATRIX_DETAIL_SET,
	_,
	SGE_CG_PARAMETER_DETAIL_PP_TYPES
)

}
}
}
}
}

#endif
