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


#include "../context.hpp"
#include "../device.hpp"
#include "../check_state.hpp"
#include "../check_alc_state.hpp"
#include "../openal.hpp"
#include "../log.hpp"
#include <sge/audio/exception.hpp>
#include <fcppt/assert/post.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


sge::openal::context::context(
	device &_device,
	attribute_container const &_attributes
)
:
	device_(_device)
{
	std::vector<ALCint> al_attributes;

	for(
		attribute_container::const_iterator it(
			_attributes.begin()
		);
		it != _attributes.end();
		++it
	)
	{
		al_attributes.push_back(
			it->first
		);

		al_attributes.push_back(
			it->second
		);
	}
	// attribute array has to be null terminated
	al_attributes.push_back(static_cast<ALCint>(0));
	al_attributes.push_back(static_cast<ALCint>(0));

	FCPPT_LOG_DEBUG(log(),fcppt::log::_ << FCPPT_TEXT("creating audio context"))

	context_ = alcCreateContext(device_.aldevice(),&(al_attributes[0]));

	SGE_OPENAL_CHECK_ALC_STATE(
		device_.aldevice(),
		FCPPT_TEXT("alcCreateContext failed"),
		audio::exception
	)

	// TODO: why is this here?
	/*
	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alcCreateContext failed"),
		audio::exception
	)
	*/

	// FIXME: can this leak? For example the creation of the context succeeds but there is an alError?

	FCPPT_ASSERT_POST(
		context_,
		sge::audio::exception
	);

	FCPPT_LOG_DEBUG(log(),fcppt::log::_ << FCPPT_TEXT("created audio context"))
}

ALCcontext *
sge::openal::context::alcontext()
{
	return context_;
}

void sge::openal::context::make_current()
{
	FCPPT_LOG_DEBUG(log(),
		fcppt::log::_ << FCPPT_TEXT("making audio context the current context"));

	alcMakeContextCurrent(context_);

	SGE_OPENAL_CHECK_ALC_STATE(
		device_.aldevice(),
		FCPPT_TEXT("alcMakeContextCurrent failed"),
		audio::exception
	)

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alcMakeContextCurrent failed"),
		audio::exception
	)

	FCPPT_LOG_DEBUG(log(),
		fcppt::log::_ << FCPPT_TEXT("made audio context the current context"));
}

sge::openal::context::~context()
{
	ALCcontext const * const current = alcGetCurrentContext();

	// TODO: this needs to be split and std::uncaugt_exception needs to be checked

	SGE_OPENAL_CHECK_ALC_STATE(
		device_.aldevice(),
		FCPPT_TEXT("alcGetCurrentContext failed"),
		audio::exception
	)

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alcGetCurrentContext failed"),
		audio::exception
	)

	if (current == context_)
	{
		FCPPT_LOG_DEBUG(log(),
			fcppt::log::_ << FCPPT_TEXT("context is the current context, so resetting current context"));

		// TODO: alcMakeContextCurrent is called more than once, split this!
		alcMakeContextCurrent(0);

		SGE_OPENAL_CHECK_ALC_STATE(
			device_.aldevice(),
			FCPPT_TEXT("alcMakeContextCurrent failed"),
			audio::exception
		);
		// at this vector: DO NOT CHECK FOR OPENAL ERRORS. IT'S ILLEGAL
		//SGE_OPENAL_ERROR_CHECK;
	}

	alcDestroyContext(context_);

	SGE_OPENAL_CHECK_ALC_STATE(
		device_.aldevice(),
		FCPPT_TEXT("alcDestroyContext failed"),
		audio::exception
	);
}
