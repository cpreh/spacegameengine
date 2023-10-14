//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/file.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/load_exn.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/position.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/vector2.hpp>
#include <sge/audio/vector2_to_vector.hpp>
#include <sge/audio/sound/positional.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/config/media_path.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_audio_loader.hpp>
#include <sge/systems/with_audio_player.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_fractional.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <numbers>
#include <ostream>
#include <fcppt/config/external_end.hpp>

int main()
try
{
  sge::systems::instance<sge::systems::with_audio_loader, sge::systems::with_audio_player> const
      sys(sge::systems::make_list(sge::systems::audio_player_default())(
          sge::systems::audio_loader(sge::media::optional_extension_set(
              sge::media::extension_set{sge::media::extension(FCPPT_TEXT("wav"))}))));

  sge::audio::file_unique_ptr const file(sge::audio::load_exn(
      fcppt::make_ref(sys.audio_loader()),
      sge::config::media_path() / FCPPT_TEXT("sounds") / FCPPT_TEXT("ding.wav")));

  sge::audio::sound::positional_unique_ptr const sound(sys.audio_player().create_positional_stream(
      fcppt::make_ref(*file),
      sge::audio::sound::positional_parameters{
          sge::audio::position{fcppt::math::vector::null<sge::audio::vector>()}}));

  sound->play(sge::audio::sound::repeat::loop);

  sge::timer::basic<sge::timer::clocks::standard> frame_timer(
      sge::timer::parameters<sge::timer::clocks::standard>(std::chrono::seconds(1)));

  sge::audio::scalar const rpm(fcppt::literal<sge::audio::scalar>(1));

  sge::audio::scalar const speed(
      std::numbers::pi_v<sge::audio::scalar> * fcppt::literal<sge::audio::scalar>(2) * rpm);

  for (;;)
  {
    sge::audio::scalar const angle(
        sge::timer::elapsed_fractional<sge::audio::scalar>(frame_timer) * speed);

    sound->position(
        sge::audio::vector2_to_vector(sge::audio::vector2{std::sin(angle), std::cos(angle)}));

    sound->update();
  }
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
