//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_DEREF_FUN_PTR_HPP_INCLUDED
#define SGE_OPENGL_DEREF_FUN_PTR_HPP_INCLUDED

#include <sge/opengl/fun_ref.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>

namespace sge::opengl
{

template <typename Function>
sge::opengl::fun_ref<Function> deref_fun_ptr(Function const _function)
{
  if (_function == nullptr)
  {
    throw sge::renderer::exception{FCPPT_TEXT("opengl::deref_fun_ptr: Pointer is null!")};
  }

  return fcppt::make_ref(*_function);
}

}

#endif
