//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_INFO_CAST_FUNCTION_HPP_INCLUDED
#define SGE_OPENGL_INFO_CAST_FUNCTION_HPP_INCLUDED

#include <sge/opengl/backend/fun_ptr.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sge::opengl::info
{

template <typename Ret>
[[nodiscard]] Ret cast_function(sge::opengl::backend::fun_ptr const _function)
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wcast-function-type-strict)
  return
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      reinterpret_cast<Ret>(_function);
FCPPT_PP_POP_WARNING
}

}

#endif
