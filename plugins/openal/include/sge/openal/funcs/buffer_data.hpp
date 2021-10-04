//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_FUNCS_BUFFER_DATA_HPP_INCLUDED
#define SGE_OPENAL_FUNCS_BUFFER_DATA_HPP_INCLUDED

#include <sge/openal/al.hpp>
#include <sge/openal/buffer_id.hpp>


namespace sge::openal::funcs
{

void
buffer_data(
	sge::openal::buffer_id,
	ALenum format,
	ALvoid const *data,
	ALsizei size,
	ALsizei freq
);

}

#endif
