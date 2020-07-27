//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/file_ref.hpp>
#include <sge/audio/listener_fwd.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/audio_null/buffer.hpp>
#include <sge/audio_null/player.hpp>
#include <sge/audio_null/positional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::audio_null::player::player()
:
	listener_()
{
}

sge::audio_null::player::~player()
= default;

sge::audio::listener &
sge::audio_null::player::listener()
{
	return
		listener_;
}

void
sge::audio_null::player::speed_of_sound(
	sge::audio::scalar
)
{
}

void
sge::audio_null::player::doppler_factor(
	sge::audio::scalar
)
{
}

void
sge::audio_null::player::gain(
	sge::audio::scalar
)
{
}

sge::audio::buffer_unique_ptr
sge::audio_null::player::create_buffer(
	sge::audio::file &
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::audio::buffer
		>(
			fcppt::make_unique_ptr<
				sge::audio_null::buffer
			>()
		);
}

sge::audio::sound::positional_unique_ptr
sge::audio_null::player::create_positional_stream(
	sge::audio::file_ref,
	sge::audio::sound::positional_parameters const &
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::audio::sound::positional
		>(
			fcppt::make_unique_ptr<
				sge::audio_null::positional
			>()
		);
}

sge::audio::sound::base_unique_ptr
sge::audio_null::player::create_nonpositional_stream(
	sge::audio::file_ref,
	sge::audio::sound::nonpositional_parameters const &
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::audio::sound::base
		>(
			fcppt::make_unique_ptr<
				sge::audio_null::positional
			>()
		);
}

bool
sge::audio_null::player::is_null() const
{
	return
		true;
}
