#include "../device.hpp"
#include "../error.hpp"
#include "../openal.hpp"
#include <sge/audio/exception.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>

sge::openal::device::device(
	ALCchar const * const specifier)
:
	device_(alcOpenDevice(specifier))
{
	if (!device_)
	{
		SGE_ALC_ERROR_CHECK(device_);
		SGE_OPENAL_ERROR_CHECK;
	}

	SGE_ASSERT(device_);
}

ALCdevice *
sge::openal::device::aldevice()
{
	return device_;
}

sge::openal::device::~device()
{
	if (alcCloseDevice(device_) == AL_FALSE)
		if (!std::uncaught_exception())
			throw audio::exception(
				SGE_TEXT("error closing audio device. this means you tried to close the device before unloading all contexts and buffers"));
}
