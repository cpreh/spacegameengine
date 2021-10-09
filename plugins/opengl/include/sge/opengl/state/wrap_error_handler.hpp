//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_WRAP_ERROR_HANDLER_HPP_INCLUDED
#define SGE_OPENGL_STATE_WRAP_ERROR_HANDLER_HPP_INCLUDED

#include <sge/opengl/state/error_handler.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::state
{

template <typename Result, typename Actor>
Result wrap_error_handler(
    Actor &&_actor,
    // TODO(philipp): Pass a function returning a string here
    fcppt::string &&_name)
{
  return Result{sge::opengl::state::error_handler<std::remove_cvref_t<Actor>>(
      std::forward<Actor>(_actor), std::move(_name))};
}

}

#endif
