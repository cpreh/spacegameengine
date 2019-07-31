//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/load_exn.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/multi_loader_parameters.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/player_unique_ptr.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/audio/player_plugin/collection_fwd.hpp>
#include <sge/audio/player_plugin/object.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/config/media_path.hpp>
#include <sge/config/plugin_path.hpp>
#include <sge/log/default_level_streams.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/optional_level.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	sge::media::extension_set const extensions{
		sge::media::extension{
			FCPPT_TEXT("wav")
		}
	};

	fcppt::log::context log_context{
		fcppt::log::optional_level{
			fcppt::log::level::debug
		},
		sge::log::default_level_streams()
	};

//! [manual_initialization_pm]
	sge::plugin::manager plugin_manager{
		log_context,
		sge::config::plugin_path(),
		sge::plugin::optional_cache_ref()
	};
//! [manual_initialization_pm]

//! [manual_initialization_player]
	sge::audio::player_plugin::collection const audio_players{
		plugin_manager.collection<
			sge::audio::player
		>()
	};

	sge::audio::player_plugin::object const player_plugin{
		audio_players.get(0u).load()
	};

	sge::audio::player_unique_ptr const player_ptr{
		player_plugin.get()(
			log_context
		)
	};

	sge::audio::player &player{
		*player_ptr
	};
//! [manual_initialization_player]

//! [manual_initialization_loader]
	sge::audio::multi_loader loader(
		sge::audio::multi_loader_parameters(
			log_context,
			plugin_manager.collection<
				sge::audio::loader
			>(),
			sge::media::optional_extension_set(
				extensions
			)
		)
	);
//! [manual_initialization_loader]

//! [create_file_buffer_and_sound]
	sge::audio::file_unique_ptr const soundfile{
		sge::audio::load_exn(
			loader,
			sge::config::media_path()
			/ FCPPT_TEXT("sounds")
			/ FCPPT_TEXT("ding.wav")
		)
	};

	sge::audio::buffer_unique_ptr const buf{
		player.create_buffer(
			*soundfile
		)
	};

	sge::audio::sound::base_unique_ptr const sound{
		buf->create_nonpositional(
			sge::audio::sound::nonpositional_parameters()
			.gain(
				fcppt::literal<
					sge::audio::scalar
				>(
					1
				)
			)
			.pitch(
				fcppt::literal<
					sge::audio::scalar
				>(
					1
				)
			)
		)
	};
//! [create_file_buffer_and_sound]

//! [play]
	sound->play(
		sge::audio::sound::repeat::once
	);

	while(
		sound->status()
		!=
		sge::audio::sound::play_status::stopped
	)
		sound->update();
//! [play]

//! [listener_direction]
	player.listener().position(
		fcppt::math::vector::null<
			sge::audio::vector
		>()
	);

	player.listener().linear_velocity(
		fcppt::math::vector::null<
			sge::audio::vector
		>()
	);

	player.listener().direction(
		sge::audio::direction::object{
			sge::audio::direction::forward{
				sge::audio::vector{
					0.0f,
					0.0f,
					1.0f
				}
			},
			sge::audio::direction::up{
				sge::audio::vector{
					0.0f,
					1.0f,
					0.0f
				}
			}
		}
	);
//! [listener_direction]

//! [create_and_play_streaming]
	sge::audio::sound::base_unique_ptr const streaming{
		player.create_nonpositional_stream(
			*soundfile,
			sge::audio::sound::nonpositional_parameters()
		)
	};

	while(
		streaming->status()
		!=
		sge::audio::sound::play_status::stopped
	)
		streaming->update();
//! [create_and_play_streaming]
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<<
		_error.string()
		<<
		FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<<
		_error.what()
		<<
		'\n';

	return
		EXIT_FAILURE;
}
