//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_IMPL_PARAMETER_MATRIX_SET_IMPL_HPP_INCLUDED
#define SGE_CG_IMPL_PARAMETER_MATRIX_SET_IMPL_HPP_INCLUDED


#include <sge/cg/check_state.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/parameter/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


#define SGE_CG_IMPL_PARAMETER_MATRIX_SET_IMPL(\
	type,\
	cg_name\
)\
void \
sge::cg::parameter::matrix::detail::set_ ## type(\
	sge::cg::parameter::object const &_parameter,\
	type const *const _data\
)\
{\
	::cgSetMatrixParameter ## cg_name ## r(\
		_parameter.get(),\
		_data\
	);\
\
	SGE_CG_CHECK_STATE(\
		FCPPT_TEXT("cgSetMatrixParameter failed"),\
		sge::cg::exception\
	)\
}

#endif
