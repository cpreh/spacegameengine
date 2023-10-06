//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENAL_FUNCS_ALC_OPEN_DEVICE_HPP_INCLUDED
#define SGE_OPENAL_FUNCS_ALC_OPEN_DEVICE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <alc.h>
#include <fcppt/config/external_end.hpp>

namespace sge::openal::funcs
{

ALCdevice *alc_open_device(ALCchar const *);

}

#endif
