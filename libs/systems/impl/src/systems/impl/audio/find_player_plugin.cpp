//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/player.hpp>
#include <sge/audio/player_plugin/collection.hpp>
#include <sge/audio/player_plugin/context.hpp>
#include <sge/audio/player_plugin/iterator.hpp>
#include <sge/audio/player_plugin/traits.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/systems/audio_player.hpp>
#include <sge/systems/impl/find_plugin.hpp>
#include <sge/systems/impl/find_plugin_opt.hpp>
#include <sge/systems/impl/audio/find_player_plugin.hpp>
#include <sge/systems/impl/audio/player_pair.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/from.hpp>


sge::systems::impl::audio::player_pair
sge::systems::impl::audio::find_player_plugin(
	fcppt::log::context_reference const _log_context,
	fcppt::log::object &_log,
	sge::audio::player_plugin::collection const &_collection,
	sge::systems::audio_player const &_parameters
)
{
	return
		_parameters.name().has_value()
		?
			sge::systems::impl::find_plugin<
				sge::audio::player
			>(
				_log_context,
				_collection,
				_parameters.name(),
				[](
					sge::audio::player const &
				)
				{
					return
						true;
				}
			)
		:
			fcppt::optional::from(
				sge::systems::impl::find_plugin_opt<
					sge::audio::player
				>(
					_log_context,
					_collection,
					[](
						sge::audio::player const &_player
					)
					{
						return
							!_player.is_null();
					}
				),
				[
					&_log_context,
					&_log,
					&_collection,
					&_parameters
				]
				{
					FCPPT_LOG_WARNING(
						_log,
						fcppt::log::out
							<< FCPPT_TEXT("Unable to load an audio player that is not null.")
							<< FCPPT_TEXT(" Trying to load a null audio player instead.")
					)

					return
						sge::systems::impl::find_plugin<
							sge::audio::player
						>(
							_log_context,
							_collection,
							_parameters.name(),
							[](
								sge::audio::player const &_player
							)
							{
								return
									_player.is_null();
							}
						);
				}
			)
		;
}
