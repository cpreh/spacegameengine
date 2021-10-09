//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/vector.hpp>
#include <sge/openal/to_vector3.hpp>
#include <sge/openal/vector3.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sge::openal::vector3 sge::openal::to_vector3(sge::audio::vector const &_vec)
{
  return fcppt::math::vector::structure_cast<sge::openal::vector3, fcppt::cast::size_fun>(_vec);
}
