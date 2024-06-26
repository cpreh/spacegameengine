//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_IMPL_PARAMETER_VECTOR_SET_IMPL_HPP_INCLUDED
#define SGE_CG_IMPL_PARAMETER_VECTOR_SET_IMPL_HPP_INCLUDED

#include <sge/cg/check_state.hpp>
#include <sge/cg/exception.hpp> // IWYU pragma: keep
#include <sge/cg/parameter/object.hpp> // IWYU pragma: keep
#include <fcppt/text.hpp>
#include <fcppt/math/size_type.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h> // IWYU pragma: keep
#include <fcppt/config/external_end.hpp>

#define SGE_CG_IMPL_PARAMETER_VECTOR_SET_IMPL_CASE(cg_name, count) \
  case count: \
    ::cgSetParameter##count##cg_name##v(_parameter.get(), _data); \
    break

#define SGE_CG_IMPL_PARAMETER_VECTOR_SET_IMPL(type, cg_name) \
  void sge::cg::parameter::vector::detail::set_##type( \
      sge::cg::parameter::object const &_parameter, \
      type const *const _data, \
      fcppt::math::size_type const _size) \
  { \
    switch (_size) \
    { \
      SGE_CG_IMPL_PARAMETER_VECTOR_SET_IMPL_CASE(cg_name, 1); \
      SGE_CG_IMPL_PARAMETER_VECTOR_SET_IMPL_CASE(cg_name, 2); \
      SGE_CG_IMPL_PARAMETER_VECTOR_SET_IMPL_CASE(cg_name, 3); \
      SGE_CG_IMPL_PARAMETER_VECTOR_SET_IMPL_CASE(cg_name, 4); \
    default: \
      throw sge::cg::exception{FCPPT_TEXT("Invalid size in cgSetParameter.")}; \
    } \
\
    SGE_CG_CHECK_STATE(FCPPT_TEXT("cgSetParameter failed"), sge::cg::exception) \
  }

#endif
