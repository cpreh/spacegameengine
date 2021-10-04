//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_BUFFER_ID_CONTAINER_FWD_HPP_INCLUDED
#define SGE_OPENAL_BUFFER_ID_CONTAINER_FWD_HPP_INCLUDED

#include <sge/openal/al.hpp>
#include <fcppt/container/raw_vector/object_fwd.hpp>


namespace sge::openal
{

using
buffer_id_container
=
fcppt::container::raw_vector::object<
	ALuint
>;

}

#endif
