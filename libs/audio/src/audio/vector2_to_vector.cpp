//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/vector2.hpp>
#include <sge/audio/vector2_to_vector.hpp>
#include <fcppt/literal.hpp>


sge::audio::vector
sge::audio::vector2_to_vector(
	sge::audio::vector2 const &_pos
)
{
	return
		sge::audio::vector(
			_pos.x(),
			fcppt::literal<
				sge::audio::scalar
			>(
				0
			),
			_pos.y()
		);
}
