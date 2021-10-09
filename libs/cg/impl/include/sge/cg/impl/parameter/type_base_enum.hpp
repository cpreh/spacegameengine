//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_IMPL_PARAMETER_TYPE_BASE_ENUM_HPP_INCLUDED
#define SGE_CG_IMPL_PARAMETER_TYPE_BASE_ENUM_HPP_INCLUDED

#include <sge/cg/impl/type_integral_c.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>

namespace sge::cg::impl::parameter
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename Type>
struct type_base_enum;

template <>
struct type_base_enum<double> : sge::cg::impl::type_integral_c<CG_DOUBLE>
{
};

template <>
struct type_base_enum<float> : sge::cg::impl::type_integral_c<CG_FLOAT>
{
};

template <>
struct type_base_enum<int> : sge::cg::impl::type_integral_c<CG_INT>
{
};

FCPPT_PP_POP_WARNING

}

#endif
