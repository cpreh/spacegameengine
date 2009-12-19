/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../listener.hpp"
#include "../check_state.hpp"
#include "../log.hpp"
#include "../openal.hpp"
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <sge/audio/exception.hpp>
#include <sge/text.hpp>

namespace
{

void listener_fv(
	ALenum const type,
	ALfloat const *const value)
{
	alListenerfv(
		type,
		value
	);

	SGE_OPENAL_CHECK_STATE(
		SGE_TEXT("alListenerfv failed"),
		sge::audio::exception
	)
}

}

sge::openal::listener::listener()
:
	pos_(),
	vel_()
{
}

void sge::openal::listener::vel(audio::point const &n)
{
	SGE_LOG_DEBUG(log(),log::_ << SGE_TEXT("setting listener velocity to ") << n);
	vel_ = n;

	// TODO: use sge::fcppt::math::vector!
	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};
	listener_fv(
		AL_VELOCITY,
		vec
	);
}

sge::audio::point const sge::openal::listener::vel() const
{
	return vel_;
}

void sge::openal::listener::pos(audio::point const &n)
{
	SGE_LOG_DEBUG(log(),log::_ << SGE_TEXT("setting listener position to ") << n);
	pos_ = n;
	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};
	listener_fv(
		AL_POSITION,
		vec
	);
}

sge::audio::point const sge::openal::listener::pos() const
{
	return pos_;
}

void sge::openal::listener::direction(audio::angle const &n)
{
	ALfloat const vec[6] =
		{
			static_cast<ALfloat>(n.forward().x()),
			static_cast<ALfloat>(n.forward().y()),
			static_cast<ALfloat>(n.forward().z()),
			static_cast<ALfloat>(n.up().x()),
			static_cast<ALfloat>(n.up().y()),
			static_cast<ALfloat>(n.up().z())
		};

	listener_fv(
		AL_POSITION,
		vec
	);
}


sge::audio::angle const sge::openal::listener::direction() const
{
	return angle_;
}
