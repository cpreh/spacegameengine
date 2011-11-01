#include <sge/extension_set.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/config/media_path.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
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
//! [systems_initialization]
	// Which file types do we want to load (see below)?
	sge::extension_set extensions;
	extensions.insert(
		FCPPT_TEXT("wav"));

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
//! [systems_initialization]


	sge::audio::file_ptr const soundfile =
		sys.audio_loader().load(
			sge::config::media_path()
				/ FCPPT_TEXT("sounds")
				/ FCPPT_TEXT("ding.wav"));

	sge::audio::buffer_ptr const buf =
		sys.audio_player().create_buffer(
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
