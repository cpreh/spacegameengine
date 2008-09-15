#include "../device_wrapper.hpp"
#include "../error.hpp"
#include "../openal.hpp"
#include <sge/audio/exception.hpp>

sge::openal::device_wrapper::device_wrapper(ALCchar const * const specifier)
	: device_(alcOpenDevice(specifier))
{
	if (!device_)
		throw audio::exception(SGE_TEXT("error opening audio device"));
	SGE_OPENAL_ERROR_CHECK
}

ALCdevice *sge::openal::device_wrapper::device()
{
	return device_;
}

sge::openal::device_wrapper::~device_wrapper()
{
	alcCloseDevice(device_);
	SGE_OPENAL_ERROR_CHECK
}
