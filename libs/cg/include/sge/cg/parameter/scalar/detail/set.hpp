//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_PARAMETER_SCALAR_DETAIL_SET_HPP_INCLUDED
#define SGE_CG_PARAMETER_SCALAR_DETAIL_SET_HPP_INCLUDED

#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/detail/pp_types.hpp>
#include <sge/cg/parameter/scalar/detail/set_double.hpp>
#include <sge/cg/parameter/scalar/detail/set_float.hpp>
#include <sge/cg/parameter/scalar/detail/set_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge::cg::parameter::scalar::detail
{

#define SGE_CG_PARAMETER_SCALAR_DETAIL_SET(seq, _, type) \
  inline void set(sge::cg::parameter::object const &_parameter, type const _scalar) \
  { \
    sge::cg::parameter::scalar::detail::BOOST_PP_CAT(set_, type)(_parameter, _scalar); \
  }

BOOST_PP_SEQ_FOR_EACH(SGE_CG_PARAMETER_SCALAR_DETAIL_SET, _, SGE_CG_PARAMETER_DETAIL_PP_TYPES)

}

#endif
