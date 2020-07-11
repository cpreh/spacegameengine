//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/audio_loader.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::systems::audio_loader::audio_loader(
	sge::media::optional_extension_set &&_extensions
)
:
	extensions_(
		std::move(
			_extensions
		)
	)
{
}

sge::media::optional_extension_set const &
sge::systems::audio_loader::extensions() const
{
	return
		extensions_;
}
