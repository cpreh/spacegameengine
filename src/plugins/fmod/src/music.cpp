/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <stdexcept>
#include "../music.hpp"

namespace {
	signed char F_CALLBACKAPI restart_callback(FSOUND_STREAM* s, void*, int, void*)
	{
		if(FSOUND_Stream_SetPosition(s,0)==false)
			throw std::runtime_error("Unable to set the stream's position");
		if(FSOUND_Stream_Play(0,s)==-1)
			throw std::runtime_error("Unable to play music");
		return true;
	}
}

sge::fmod::music::music(const std::string& file)
: stream(FSOUND_Stream_Open(file.c_str(),0,0,0))
{
	if(!stream)
		throw std::runtime_error("Unable to load music");
}

sge::fmod::music::~music()
{
	FSOUND_Stream_Close(stream);
}

void sge::fmod::music::play(bool loop)
{
	if(FSOUND_Stream_Play(0,stream)==-1)
		throw std::runtime_error("Unable to play music");
	if(loop)
	{
		if(FSOUND_Stream_SetEndCallback(stream,restart_callback,0) == false)
			throw std::runtime_error("Unable to loop music");
	}
	else
	{
		if(FSOUND_Stream_SetEndCallback(stream,0,0) == false)
			throw std::runtime_error("Unable to unloop music");
	}
}

void sge::fmod::music::stop()
{
	if(FSOUND_Stream_Stop(stream)==false)
		throw std::runtime_error("Unable to stop music");
}
