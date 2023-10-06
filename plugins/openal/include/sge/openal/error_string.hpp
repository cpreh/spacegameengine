//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENAL_ERROR_STRING_HPP_INCLUDED
#define SGE_OPENAL_ERROR_STRING_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <al.h>
#include <fcppt/config/external_end.hpp>

namespace sge::openal
{

fcppt::string error_string(ALenum error);

}

#endif
