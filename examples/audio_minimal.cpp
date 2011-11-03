#include <sge/extension_set.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/config/media_path.hpp>
#ifdef SGE_EXAMPLES_AUDIO_MINIMAL_USE_SYSTEMS_INIT
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#else
#include <sge/plugin/manager.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/context.hpp>
#include <sge/audio/player_plugin.hpp>
#include <sge/audio/player_ptr.hpp>
#include <sge/config/plugin_path.hpp>
#endif // SGE_EXAMPLES_AUDIO_MINIMAL_USE_SYSTEMS_INIT
#include <sge/audio/loader_capabilities_field.hpp>
#include <sge/audio/multi_loader.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int main(int, char *[])
try
{
	sge::extension_set extensions;
	extensions.insert(
		FCPPT_TEXT("wav"));
#ifdef SGE_EXAMPLES_AUDIO_MINIMAL_USE_SYSTEMS_INIT
//! [systems_initialization]
	// Which file types do we want to load (see below)?

	sge::systems::instance sys(
		sge::systems::list()
			// Player initialization begin
			(sge::systems::audio_player_default())
			// Player initialization end

			// Loader initialization begin
			(sge::systems::audio_loader(
				sge::audio::loader_capabilities_field::null(),
				extensions))
			// Loader initialization end

			// Other system initializations (renderer, ...) here
			// ...
		);

	sge::audio::player &player =
		sys.audio_player();

	sge::audio::multi_loader &loader =
		sys.audio_loader();
//! [systems_initialization]
#else

//! [manual_initialization_pm]
	sge::plugin::manager plugin_manager(
		sge::config::plugin_path());
//! [manual_initialization_pm]
//
//! [manual_initialization_player]
	sge::plugin::iterator<sge::audio::player> player_it =
		plugin_manager.begin<sge::audio::player>();

	typedef
	sge::plugin::context<sge::audio::player>::ptr_type
	player_plugin_ptr;

	player_plugin_ptr const player_plugin(
		player_it->load());

	sge::audio::player_ptr const _player(
		player_plugin->get()());

	sge::audio::player &player =
		*_player;
//! [manual_initialization_player]

//! [manual_initialization_loader]
	sge::audio::multi_loader loader(
		plugin_manager,
		extensions,
		sge::audio::loader_capabilities_field::null());
//! [manual_initialization_loader]
#endif

	sge::audio::file_ptr const soundfile =
		loader.load(
			sge::config::media_path()
				/ FCPPT_TEXT("sounds")
				/ FCPPT_TEXT("ding.wav"));

	sge::audio::buffer_ptr const buf =
		player.create_buffer(
			*soundfile);

	sge::audio::sound::base_ptr const s =
		buf->create_nonpositional();

	s->play(
		sge::audio::sound::repeat::once);

	while (s->status() != sge::audio::sound::play_status::stopped)
		s->update();
}
catch(
	fcppt::exception const &_error)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
