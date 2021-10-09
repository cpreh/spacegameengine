//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENAL_TO_VECTOR3_HPP_INCLUDED
#define SGE_OPENAL_TO_VECTOR3_HPP_INCLUDED

#include <sge/audio/vector_fwd.hpp>
#include <sge/openal/vector3_fwd.hpp>

namespace sge::openal
{

sge::openal::vector3 to_vector3(sge::audio::vector const &);

}

#endif
