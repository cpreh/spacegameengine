//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_IMPL_LIBRARY_CAST_FUNCTION_UNSAFE_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_LIBRARY_CAST_FUNCTION_UNSAFE_HPP_INCLUDED

#include <sge/plugin/impl/library/is_function_ptr.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sge::plugin::impl::library
{

template <typename Target, typename Source>
inline Target cast_function_unsafe(Source const _function)
{
  static_assert(
      sge::plugin::impl::library::is_function_ptr<Target>::value,
      "Target must be a function pointer type");

  static_assert(
      sge::plugin::impl::library::is_function_ptr<Source>::value,
      "Source must be a function pointer type");

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_VC_WARNING(4191)
  FCPPT_PP_DISABLE_GCC_WARNING(-Wcast-function-type)
  FCPPT_PP_DISABLE_CLANG_WARNING(-Wcast-function-type-strict)
  return
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      reinterpret_cast<Target>(_function);
  FCPPT_PP_POP_WARNING
}

}

#endif
