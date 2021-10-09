//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENAL_FUNCS_DELETE_BUFFERS_HPP_INCLUDED
#define SGE_OPENAL_FUNCS_DELETE_BUFFERS_HPP_INCLUDED

#include <sge/openal/al.hpp>

namespace sge::openal::funcs
{

void delete_buffers(ALuint const *buffers, ALsizei size);

}

#endif
