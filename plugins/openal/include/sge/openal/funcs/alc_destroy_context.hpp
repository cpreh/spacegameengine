//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENAL_FUNCS_ALC_DESTROY_CONTEXT_HPP_INCLUDED
#define SGE_OPENAL_FUNCS_ALC_DESTROY_CONTEXT_HPP_INCLUDED

#include <sge/openal/alc.hpp>

namespace sge::openal::funcs
{

void alc_destroy_context(
    ALCdevice &, // NOLINT(google-runtime-references)
    ALCcontext & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
