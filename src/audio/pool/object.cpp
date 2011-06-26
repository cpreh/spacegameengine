/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/audio/pool/object.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/log/global.hpp>
#include <fcppt/log/log.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/inverse.hpp>
#include <fcppt/assert_message.hpp>

sge::audio::pool::object::object(
	pool::gain_factor const &_gain_factor,
	pool::pitch_factor const &_pitch_factor)
:
	sounds_(),
	gain_factor_(
		_gain_factor.get()),
	pitch_factor_(
		_pitch_factor.get())
{}

sge::audio::pool::object::~object()
{}

void
sge::audio::pool::object::add(
	sound::base_ptr const s,
	pool::stop_mode::type const pm
)
{
	s->gain(
		s->gain() * gain_factor());
	s->pitch(
		s->pitch() * pitch_factor());
	sounds_.push_back(
		pool::sound_data(
			s,
			pm));
}

void
sge::audio::pool::object::update()
{
	for(
		container_type::iterator sound_it(
			sounds_.begin()
		);
		sound_it != sounds_.end();
	)
	{
		// sound's not dead yet?
		if (!sound_it->sound().unique())
		{
			sound_it->sound()->update();
			sound_it++;
			continue;
		}

		switch (sound_it->stop_mode())
		{
			case pool::stop_mode::stop_playing:
			break;
			case pool::stop_mode::continue_playing:
				FCPPT_ASSERT_MESSAGE(
					sound_it->sound()->status() != audio::sound::play_status::paused,
					FCPPT_TEXT("a paused sound was destroyed but kept alive by the sound pool")
				);

				if (sound_it->sound()->status() != audio::sound::play_status::stopped)
				{
					sound_it++;
					continue;
				}
			break;
			case pool::stop_mode::play_once:
				FCPPT_ASSERT_MESSAGE(
					sound_it->sound()->status() != audio::sound::play_status::paused,
					FCPPT_TEXT("a paused sound was destroyed but kept alive by the sound pool")
				);

				if (sound_it->sound()->status() != audio::sound::play_status::stopped)
				{
					if (sound_it->sound()->repeat() != audio::sound::repeat::once)
					{
						FCPPT_LOG_WARNING(
							log::global(),
							fcppt::log::_
								<< FCPPT_TEXT("got a looping sound, setting to play only once")
						);

						sound_it->sound()->play(
							audio::sound::repeat::once
						);
					}
					sound_it++;
					continue;
				}
			break;
		}

		sound_it = sounds_.erase(sound_it);
	}
}

bool
sge::audio::pool::object::sounds_finished() const
{
	for(
		container_type::const_iterator it(
			sounds_.begin()
		);
		it != sounds_.end();
		++it
	)
		if(
			it->sound()->status()
			!= audio::sound::play_status::stopped
		)
			return false;
	return true;
}

sge::audio::pool::gain_factor::value_type
sge::audio::pool::object::gain_factor() const
{
	return gain_factor_;
}

void
sge::audio::pool::object::gain_factor(
	sge::audio::pool::gain_factor::value_type const _gain_factor)
{
	for(
		container_type::iterator i = 
			sounds_.begin(); 
		i != sounds_.end(); 
		++i)
		i->sound()->gain(
			// Technically leads to numerical drift, but not important here
			i->sound()->gain() 
				* 
					fcppt::math::inverse(
						gain_factor_) 
				* _gain_factor);

	gain_factor_ = 
		_gain_factor;
}

sge::audio::pool::pitch_factor::value_type
sge::audio::pool::object::pitch_factor() const
{
	return pitch_factor_;
}

void
sge::audio::pool::object::pitch_factor(
	sge::audio::pool::pitch_factor::value_type const _pitch_factor)
{
	for(
		container_type::iterator i = 
			sounds_.begin(); 
		i != sounds_.end(); 
		++i)
		i->sound()->pitch(
			// Technically leads to numerical drift, but not important here
			i->sound()->pitch() 
				* 
					fcppt::math::inverse(
						pitch_factor_) 
				* _pitch_factor);

	pitch_factor_ = 
		_pitch_factor;
}
