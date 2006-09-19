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
