//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/image2d.hpp>


sge::systems::image2d::image2d(
	sge::media::optional_extension_set const &_extensions
)
:
	extensions_(
		_extensions
	)
{
}

sge::media::optional_extension_set const &
sge::systems::image2d::extensions() const
{
	return
		extensions_;
}
