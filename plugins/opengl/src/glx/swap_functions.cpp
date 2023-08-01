//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/glx/proc_address.hpp>
#include <sge/opengl/glx/proc_address_function.hpp>
#include <sge/opengl/glx/raw_function_ref.hpp>
#include <sge/opengl/glx/swap_functions.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace
{

template <typename Ret>
fcppt::reference<Ret> cast_function(sge::opengl::glx::raw_function_ref const _func)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_CLANG_WARNING(-Wundefined-reinterpret-cast)
  FCPPT_PP_DISABLE_CLANG_WARNING(-Wcast-function-type-strict)

  return fcppt::make_ref(
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      reinterpret_cast<std::add_lvalue_reference_t<Ret>>(_func.get()));

  FCPPT_PP_POP_WARNING
}

}

sge::opengl::glx::swap_functions::swap_functions(
    sge::opengl::glx::proc_address_function _proc_address)
    : swap_interval_sgi_(fcppt::optional::map(
          sge::opengl::glx::proc_address(_proc_address, "glXSwapIntervalSGI"),
          [](sge::opengl::glx::raw_function_ref const _func)
          { return cast_function<glx_swap_interval_sgi>(_func); })),
      swap_interval_ext_(fcppt::optional::map(
          sge::opengl::glx::proc_address(_proc_address, "glXSwapIntervalEXT"),
          [](sge::opengl::glx::raw_function_ref const _func)
          { return cast_function<glx_swap_interval_ext>(_func); }))
{
}

sge::opengl::glx::swap_functions::optional_glx_swap_interval_sgi
sge::opengl::glx::swap_functions::swap_interval_sgi() const
{
  return swap_interval_sgi_;
}

sge::opengl::glx::swap_functions::optional_glx_swap_interval_ext
sge::opengl::glx::swap_functions::swap_interval_ext() const
{
  return swap_interval_ext_;
}
