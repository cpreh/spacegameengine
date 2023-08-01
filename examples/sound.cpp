//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/load_exn.hpp>
#include <sge/audio/load_raw_exn.hpp>
#include <sge/audio/loader_ref.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/position.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/config/media_path.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/media/const_raw_pointer.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/media/raw_value.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_audio_loader.hpp>
#include <sge/systems/with_audio_player.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cin.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <limits>
#include <ostream>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{

// Test for raw loading
sge::audio::file_unique_ptr
load_raw(std::filesystem::path const &_path, sge::audio::loader_ref const _audio_loader)
{
  std::ifstream raw_stream(_path, std::ios::binary);

  using raw_byte_container = std::vector<char>;

  raw_byte_container raw_bytes{
      std::istreambuf_iterator<char>(raw_stream), std::istreambuf_iterator<char>()};

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

  return sge::audio::load_raw_exn(
      _audio_loader,
      sge::media::const_raw_range(
          fcppt::cast::to_char_ptr<sge::media::const_raw_pointer>(raw_bytes.data()),
          fcppt::cast::to_char_ptr<sge::media::const_raw_pointer>(
              raw_bytes.data() + // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
              raw_bytes.size())),
      sge::media::optional_extension());

FCPPT_PP_POP_WARNING

}

}

namespace
{

void wait_for_input()
{
  fcppt::io::cout() << FCPPT_TEXT("Please press enter to continue...\n");

  fcppt::io::cin().ignore(std::numeric_limits<std::streamsize>::max(), FCPPT_TEXT('\n'));
}

void wait_for_sound(sge::audio::sound::base &_sound // NOLINT(google-runtime-references)
                    ) // NOLINT(google-runtime-references)
{
  while (_sound.status() != sge::audio::sound::play_status::stopped)
  {
    _sound.update();
  }
}

}

int main()
try
{
  std::filesystem::path const file_name{
      sge::config::media_path() / FCPPT_TEXT("sounds") / FCPPT_TEXT("ding.wav")};
  std::filesystem::path const streaming_file_name{
      sge::config::media_path() / FCPPT_TEXT("sounds") / FCPPT_TEXT("epoq.ogg")};

  fcppt::io::cout() << FCPPT_TEXT(
      "This is the sge sound example. We will now try to load the audio loader\n");

  wait_for_input();

  sge::systems::instance<sge::systems::with_audio_player, sge::systems::with_audio_loader> const
      sys(sge::systems::make_list(sge::systems::audio_player_default())(
          sge::systems::audio_loader(sge::media::optional_extension_set(sge::media::extension_set{
              sge::media::extension(FCPPT_TEXT("wav")),
              sge::media::extension(FCPPT_TEXT("ogg"))})))(
          sge::systems::config().log_settings(sge::systems::log_settings(sge::log::option_container{
              sge::log::option{sge::log::location(), fcppt::log::level::debug}}))));

  fcppt::io::cout() << FCPPT_TEXT("Audio loader loaded\n")
                    << FCPPT_TEXT("We will now try to load a sound file\n");

  wait_for_input();

  sge::audio::file_unique_ptr const soundfile(
      load_raw(file_name, fcppt::make_ref(sys.audio_loader())));

  fcppt::io::cout() << FCPPT_TEXT("Sound file loaded\n")
                    << FCPPT_TEXT("We will now try to create a nonstreaming buffer from it.\n");

  wait_for_input();

  sge::audio::buffer_unique_ptr const buf(sys.audio_player().create_buffer(*soundfile));

  fcppt::io::cout() << FCPPT_TEXT("Buffer created\n")
                    << FCPPT_TEXT("We will now try to create a nonpositional source from it.\n");

  wait_for_input();

  sge::audio::sound::base_unique_ptr const sound(
      buf->create_nonpositional(sge::audio::sound::nonpositional_parameters()));

  fcppt::io::cout() << FCPPT_TEXT("Nonpositional source loaded\n")
                    << FCPPT_TEXT("You should hear a sound after pressing enter\n");

  wait_for_input();

  sound->play(sge::audio::sound::repeat::once);

  wait_for_sound(*sound);

  fcppt::io::cout() << FCPPT_TEXT(
      "Now we use the same sound, but create a positional source from it.\n");

  wait_for_input();

  sge::audio::sound::positional_unique_ptr const positional_sound(buf->create_positional(
      sge::audio::sound::positional_parameters{
          sge::audio::position{fcppt::math::vector::null<sge::audio::vector>()}}
          .linear_velocity(fcppt::math::vector::null<sge::audio::vector>())));

  fcppt::io::cout() << FCPPT_TEXT("Sound created at the origin, now we play it\n");

  wait_for_input();

  sound->play(sge::audio::sound::repeat::once);

  wait_for_sound(*sound);

  fcppt::io::cout() << FCPPT_TEXT(
      "Now we reposition and play again\nYou should hear the sound coming from the _left_ now.\n");

  wait_for_input();

  positional_sound->position(sge::audio::vector(
      -2.F, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      0.F,
      0.F));

  positional_sound->play(sge::audio::sound::repeat::once);

  wait_for_sound(*positional_sound);

  fcppt::io::cout() << FCPPT_TEXT("Back to the nonpositional sound. We now try to lower the volume "
                                  "globally. Playing at 100% volume...\n");

  wait_for_input();

  sound->play(sge::audio::sound::repeat::once);

  wait_for_sound(*sound);

  fcppt::io::cout() << FCPPT_TEXT("Now 50% volume...\n");

  wait_for_input();

  sys.audio_player().gain(static_cast<sge::audio::scalar>(
      0.5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      ));

  sound->play(sge::audio::sound::repeat::once);

  wait_for_sound(*sound);

  fcppt::io::cout() << FCPPT_TEXT("Now 25% volume...\n");

  wait_for_input();

  sys.audio_player().gain(static_cast<sge::audio::scalar>(
      0.25 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      ));

  sound->play(sge::audio::sound::repeat::once);

  wait_for_sound(*sound);

  fcppt::io::cout() << FCPPT_TEXT("And finally 0% volume...\n");

  wait_for_input();

  sys.audio_player().gain(static_cast<sge::audio::scalar>(0.0));

  sound->play(sge::audio::sound::repeat::once);

  wait_for_sound(*sound);

  sys.audio_player().gain(static_cast<sge::audio::scalar>(1.0));

  fcppt::io::cout() << FCPPT_TEXT(
      "Let's try changing the sound pitch now...You'll hear the sound with a 50% pitch now.\n");

  wait_for_input();

  sound->pitch(static_cast<sge::audio::scalar>(
      0.5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      ));

  sound->play(sge::audio::sound::repeat::once);

  wait_for_sound(*sound);

  fcppt::io::cout() << FCPPT_TEXT("Now with 150% pitch...\n");

  wait_for_input();

  sound->pitch(static_cast<sge::audio::scalar>(
      1.5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      ));

  sound->play(sge::audio::sound::repeat::once);

  wait_for_sound(*sound);

  fcppt::io::cout() << FCPPT_TEXT(
      "On to streaming sounds, we'll now create a positional streaming sound...\n");

  wait_for_input();

  sge::audio::file_unique_ptr const streaming_file(
      sge::audio::load_exn(fcppt::make_ref(sys.audio_loader()), streaming_file_name));

  sge::audio::sound::positional_unique_ptr const streaming_positional_sound(
      sys.audio_player().create_positional_stream(
          fcppt::make_ref(*streaming_file),
          sge::audio::sound::positional_parameters{
              sge::audio::position{sge::audio::vector{
                  -2000.F, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  0.F,
                  0.F}}}
              .linear_velocity(fcppt::math::vector::null<sge::audio::vector>())));

  fcppt::io::cout() << FCPPT_TEXT("Streaming sound created.\nWe'll now play it for 10 seconds.\n");

  wait_for_input();

  streaming_positional_sound->play(sge::audio::sound::repeat::once);

  streaming_positional_sound->position(sge::audio::vector(
      -2000.F, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      0.F,
      0.F));

  sge::timer::basic<sge::timer::clocks::standard> frame_timer(
      sge::timer::parameters<sge::timer::clocks::standard>(std::chrono::seconds(
          10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          )));

  while (streaming_positional_sound->status() != sge::audio::sound::play_status::stopped &&
         !frame_timer.expired())
  {
    streaming_positional_sound->update();
  }

  streaming_positional_sound->stop();

  fcppt::io::cout() << FCPPT_TEXT("Finished\n");

  wait_for_input();
}
catch (fcppt::exception const &_error)
{
  fcppt::io::cerr() << _error.string() << FCPPT_TEXT('\n');

  return EXIT_FAILURE;
}
catch (std::exception const &_error)
{
  std::cerr << _error.what() << '\n';

  return EXIT_FAILURE;
}
