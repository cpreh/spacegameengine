//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/multi_loader_parameters.hpp>
#include <sge/audio/loader_plugin/collection_fwd.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/impl/audio/loader.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/context_fwd.hpp>


sge::systems::impl::audio::loader::loader(
	fcppt::log::context &_log_context,
	sge::audio::loader_plugin::collection const &_collection,
	sge::systems::audio_loader const &_parameters
)
:
	audio_multi_loader_(
		fcppt::make_unique_ptr<
			sge::audio::multi_loader
		>(
			sge::audio::multi_loader_parameters(
				_log_context,
				_collection,
				_parameters.extensions()
			)
		)
	)
{
}

sge::systems::impl::audio::loader::~loader()
{
}

sge::audio::loader &
sge::systems::impl::audio::loader::get() const
{
	return
		*audio_multi_loader_;
}
