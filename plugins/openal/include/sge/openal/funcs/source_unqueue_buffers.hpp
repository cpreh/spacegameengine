//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_FUNCS_SOURCE_UNQUEUE_BUFFERS_HPP_INCLUDED
#define SGE_OPENAL_FUNCS_SOURCE_UNQUEUE_BUFFERS_HPP_INCLUDED

#include <sge/openal/al.hpp>
#include <sge/openal/buffer_id_container.hpp>
#include <sge/openal/source_id.hpp>


namespace sge::openal::funcs
{

sge::openal::buffer_id_container
source_unqueue_buffers(
	sge::openal::source_id,
	ALsizei
);

}

#endif
