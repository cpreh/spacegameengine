//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/check_state.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/impl/parameter/get_type.hpp>
#include <sge/cg/parameter/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>

CGtype sge::cg::impl::parameter::get_type(sge::cg::parameter::object const &_parameter)
{
  CGtype const ret(::cgGetParameterType(_parameter.get()));

  SGE_CG_CHECK_STATE(FCPPT_TEXT("cgGetParameterType failed"), sge::cg::exception)

  if (ret == CG_UNKNOWN_TYPE)
  {
    throw sge::cg::exception{FCPPT_TEXT("Unknown parameter tpye")};
  }

  return ret;
}
