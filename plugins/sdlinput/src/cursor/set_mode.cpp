//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/sdlinput/cursor/set_mode.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_mouse.h>
#include <SDL_stdinc.h>
#include <fcppt/config/external_end.hpp>

namespace
{

SDL_bool convert_mode(sge::input::cursor::mode const _mode)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_mode)
  {
  case sge::input::cursor::mode::normal:
    return SDL_FALSE;
  case sge::input::cursor::mode::exclusive:
    return SDL_TRUE;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_mode);
}

}

void sge::sdlinput::cursor::set_mode(sge::input::cursor::mode const _mode)
{
  if (SDL_SetRelativeMouseMode(convert_mode(_mode)) == -1)
  {
    throw sge::input::exception{FCPPT_TEXT("SDL_SetRelativeMouseMode failed!")};
  }
}
