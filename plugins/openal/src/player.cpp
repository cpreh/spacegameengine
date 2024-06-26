//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/file_ref.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/direction/forward.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/audio/direction/up.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/log/location.hpp>
#include <sge/openal/buffer.hpp>
#include <sge/openal/player.hpp>
#include <sge/openal/stream_sound.hpp>
#include <sge/openal/funcs/doppler_factor.hpp>
#include <sge/openal/funcs/listener_float.hpp>
#include <sge/openal/funcs/speed_of_sound.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <al.h>
#include <fcppt/config/external_end.hpp>

sge::openal::player::player(fcppt::log::context_reference const _log_context)
    : log_{_log_context, sge::log::location(), fcppt::log::name{FCPPT_TEXT("openal")}},
      device_(nullptr),
      context_(fcppt::make_ref(device_)),
      current_context_(fcppt::make_ref(log_), fcppt::make_ref(context_)),
      listener_()
{
  // set our own speed of sound standard rather than relying on OpenAL
  sge::openal::player::set_speed_of_sound(
      343.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  );

  this->get_listener().position(fcppt::math::vector::null<sge::audio::vector>());

  this->get_listener().linear_velocity(fcppt::math::vector::null<sge::audio::vector>());

  this->get_listener().direction(sge::audio::direction::object(
      sge::audio::direction::forward(sge::audio::vector(0.F, 0.F, 1.F)),
      sge::audio::direction::up(sge::audio::vector(0.F, 1.F, 0.F))));
}

sge::openal::player::~player() = default;

sge::audio::listener &sge::openal::player::listener() { return this->get_listener(); }

void sge::openal::player::speed_of_sound(sge::audio::scalar const _value)
{
  sge::openal::player::set_speed_of_sound(_value);
}

void sge::openal::player::doppler_factor(sge::audio::scalar const _value)
{
  sge::openal::funcs::doppler_factor(fcppt::cast::size<ALfloat>(_value));
}

void sge::openal::player::gain(sge::audio::scalar const _value)
{
  sge::openal::funcs::listener_float(AL_GAIN, fcppt::cast::size<ALfloat>(_value));
}

sge::audio::buffer_unique_ptr sge::openal::player::create_buffer(sge::audio::file &_file)
{
  return fcppt::unique_ptr_to_base<sge::audio::buffer>(
      fcppt::make_unique_ptr<sge::openal::buffer>(fcppt::make_ref(log_), _file));
}

sge::audio::sound::positional_unique_ptr sge::openal::player::create_positional_stream(
    sge::audio::file_ref const _file, sge::audio::sound::positional_parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::audio::sound::positional>(
      fcppt::make_unique_ptr<sge::openal::stream_sound>(fcppt::make_ref(log_), _parameters, _file));
}

sge::audio::sound::base_unique_ptr sge::openal::player::create_nonpositional_stream(
    sge::audio::file_ref const _file,
    sge::audio::sound::nonpositional_parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::audio::sound::base>(
      fcppt::make_unique_ptr<sge::openal::stream_sound>(fcppt::make_ref(log_), _parameters, _file));
}

bool sge::openal::player::is_null() const { return false; }

sge::audio::listener &sge::openal::player::get_listener() { return listener_; }

void sge::openal::player::set_speed_of_sound(sge::audio::scalar const _value)
{
  sge::openal::funcs::speed_of_sound(fcppt::cast::size<ALfloat>(_value));
}
