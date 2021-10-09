//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/openal/alc.hpp>
#include <sge/openal/alc_error_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

fcppt::string sge::openal::alc_error_string(ALCenum const _error)
{
  switch (_error)
  {
  case ALC_NO_ERROR:
    return FCPPT_TEXT("no error in openal (maybe somewhere else)");
  case ALC_INVALID_DEVICE:
    return FCPPT_TEXT("the device handle specifies an inaccessible driver/server");
  case ALC_INVALID_CONTEXT:
    return FCPPT_TEXT("the context argument does not name a valid context");
  case ALC_INVALID_ENUM:
    return FCPPT_TEXT("a token used is not valid, or not acceptable");
  case ALC_INVALID_VALUE:
    return FCPPT_TEXT("a value (e.g. attribute) is not valid, or not applicable");
  case ALC_OUT_OF_MEMORY:
    return FCPPT_TEXT("unable to allocate memory");
  default:
    return FCPPT_TEXT("Unkown");
  }
}
