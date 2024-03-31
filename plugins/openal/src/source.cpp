//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/audio/position.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/optional_direction.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/source.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/to_vector3.hpp>
#include <sge/openal/vector3.hpp>
#include <sge/openal/funcs/get_source_int.hpp>
#include <sge/openal/funcs/source_float.hpp>
#include <sge/openal/funcs/source_float_ptr.hpp>
#include <sge/openal/funcs/source_int.hpp>
#include <sge/openal/funcs/source_pause.hpp>
#include <sge/openal/funcs/source_play.hpp>
#include <sge/openal/funcs/source_stop.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/math/rad_to_deg.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <al.h>
#include <fcppt/config/external_end.hpp>

sge::openal::source::source(
    fcppt::log::object_reference const _log,
    sge::audio::sound::nonpositional_parameters const &_parameters,
    sge::openal::buffer_id const _buffer)
    : source(_log, _buffer)
{
  this->init(_parameters);
}

sge::openal::source::source(
    fcppt::log::object_reference const _log,
    sge::audio::sound::positional_parameters const &_parameters,
    sge::openal::buffer_id const _buffer)
    : source(_log, _buffer)
{
  this->init(_parameters);
}

sge::openal::source::source(
    fcppt::log::object_reference const _log,
    sge::audio::sound::nonpositional_parameters const &_parameters)
    : source(_log)
{
  this->init(_parameters);
}

sge::openal::source::source(
    fcppt::log::object_reference const _log,
    sge::audio::sound::positional_parameters const &_parameters)
    : source(_log)
{
  this->init(_parameters);
}

sge::openal::source::~source() = default;

void sge::openal::source::play(sge::audio::sound::repeat const _repeat)
{
  repeat_ = _repeat;

  this->do_play();

  if (this->status() != sge::audio::sound::play_status::playing)
  {
    sge::openal::funcs::source_play(this->source_id());
  }
}

void sge::openal::source::toggle_pause()
{
  sge::audio::sound::play_status const cur_status{this->status()};

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (cur_status)
  {
  case sge::audio::sound::play_status::stopped:
    return;
  case sge::audio::sound::play_status::paused:
    sge::openal::funcs::source_play(this->source_id());
    return;
  case sge::audio::sound::play_status::playing:
    sge::openal::funcs::source_pause(this->source_id());
    return;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(cur_status);
}

sge::audio::sound::play_status sge::openal::source::status() const
{
  switch (sge::openal::funcs::get_source_int(this->source_id(), AL_SOURCE_STATE))
  {
  case AL_STOPPED:
  case AL_INITIAL:
    return sge::audio::sound::play_status::stopped;
  case AL_PAUSED:
    return sge::audio::sound::play_status::paused;
  case AL_PLAYING:
    return sge::audio::sound::play_status::playing;
  default: break;
  }

  throw sge::audio::exception{FCPPT_TEXT("Invalid AL_SOURCE_STATE!")};
}

void sge::openal::source::stop()
{
  if (this->status() == audio::sound::play_status::stopped)
  {
    return;
  }

  sge::openal::funcs::source_stop(this->source_id());
}

void sge::openal::source::update() {}

void sge::openal::source::position(sge::audio::vector const &_vector)
{
  sge::openal::funcs::source_float_ptr(
      this->source_id(), AL_POSITION, sge::openal::to_vector3(_vector).storage().data());
}

void sge::openal::source::linear_velocity(sge::audio::vector const &_vector)
{
  sge::openal::funcs::source_float_ptr(
      this->source_id(), AL_VELOCITY, sge::openal::to_vector3(_vector).storage().data());
}

void sge::openal::source::gain(sge::audio::scalar const _value)
{
  sge::openal::funcs::source_float(this->source_id(), AL_GAIN, fcppt::cast::size<ALfloat>(_value));
}

void sge::openal::source::pitch(sge::audio::scalar const _value)
{
  sge::openal::funcs::source_float(this->source_id(), AL_PITCH, fcppt::cast::size<ALfloat>(_value));
}

void sge::openal::source::rolloff_factor(sge::audio::scalar const _value)
{
  sge::openal::funcs::source_float(
      this->source_id(), AL_ROLLOFF_FACTOR, fcppt::cast::size<ALfloat>(_value));
}

void sge::openal::source::reference_distance(sge::audio::scalar const _value)
{
  sge::openal::funcs::source_float(
      this->source_id(), AL_REFERENCE_DISTANCE, fcppt::cast::size<ALfloat>(_value));
}

void sge::openal::source::max_distance(sge::audio::scalar const _value)
{
  sge::openal::funcs::source_float(
      this->source_id(), AL_MAX_DISTANCE, fcppt::cast::size<ALfloat>(_value));
}

void sge::openal::source::direction(sge::audio::sound::optional_direction const &_opt_dir)
{
  sge::openal::funcs::source_float_ptr(
      this->source_id(),
      AL_DIRECTION,
      sge::openal::to_vector3(
          fcppt::optional::from(
              _opt_dir, fcppt::const_(fcppt::math::vector::null<sge::audio::vector>())))
          .storage()
          .data());
}

void sge::openal::source::inner_cone_angle(sge::audio::scalar const _value)
{
  sge::openal::funcs::source_float(
      this->source_id(),
      AL_CONE_INNER_ANGLE,
      fcppt::cast::size<ALfloat>(fcppt::math::rad_to_deg(_value)));
}

void sge::openal::source::outer_cone_angle(sge::audio::scalar const _value)
{
  sge::openal::funcs::source_float(
      this->source_id(),
      AL_CONE_OUTER_ANGLE,
      fcppt::cast::size<ALfloat>(fcppt::math::rad_to_deg(_value)));
}

void sge::openal::source::outer_cone_gain(sge::audio::scalar const _value)
{
  sge::openal::funcs::source_float(
      this->source_id(), AL_CONE_OUTER_GAIN, fcppt::cast::size<ALfloat>(_value));
}

void sge::openal::source::do_play()
{
  sge::openal::funcs::source_int(
      this->source_id(),
      AL_LOOPING,
      repeat_ == sge::audio::sound::repeat::loop ? AL_TRUE : AL_FALSE);
}

sge::openal::source_id sge::openal::source::source_id() const { return source_.get(); }

sge::audio::sound::repeat sge::openal::source::repeat() const { return repeat_; }

sge::openal::source::source(fcppt::log::object_reference const _log)
    : source_(_log), repeat_(sge::audio::sound::repeat::once)
{
}

sge::openal::source::source(
    fcppt::log::object_reference const _log, sge::openal::buffer_id const _buffer)
    : source(_log)
{
  sge::openal::funcs::source_int(
      this->source_id(), AL_BUFFER, fcppt::cast::to_signed(_buffer.get()));
}

// that's a hack because we have two constructors
void sge::openal::source::init(sge::audio::sound::positional_parameters const &_parameters)
{
  this->pitch(_parameters.pitch());

  this->position(_parameters.position());

  this->linear_velocity(_parameters.linear_velocity());

  this->pitch(_parameters.pitch());

  this->gain(_parameters.gain());

  this->rolloff_factor(_parameters.rolloff_factor());

  this->reference_distance(_parameters.reference_distance());

  this->max_distance(_parameters.max_distance());

  this->inner_cone_angle(_parameters.inner_cone_angle());

  this->outer_cone_angle(_parameters.outer_cone_angle());

  this->direction(_parameters.direction());
}

void sge::openal::source::init(sge::audio::sound::nonpositional_parameters const &_parameters)
{
  // TODO(philipp): Is this right?
  this->init(sge::audio::sound::positional_parameters(
                 sge::audio::position{fcppt::math::vector::null<sge::audio::vector>()})
                 .gain(_parameters.gain())
                 .pitch(_parameters.pitch())
                 // The special value 0 for the rolloff factor means
                 // that the source is nonpositional (as indicated
                 // directly by the OpenAL spec)
                 .rolloff_factor(0.F));
}
