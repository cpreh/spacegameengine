#include "../device.hpp"
#include "../error.hpp"
#include "../openal.hpp"
#include "../log.hpp"
#include <sge/audio/exception.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>

sge::openal::device::device(ALCchar const * const specifier)
	: device_(alcOpenDevice(specifier))
{
	SGE_LOG_DEBUG(log(),log::_1 << SGE_TEXT("creating openal device"));

	if (!device_)
	{
		SGE_ALC_ERROR_CHECK(device_);
		SGE_OPENAL_ERROR_CHECK;
	}

	SGE_ASSERT(device_);

	SGE_LOG_DEBUG(log(),log::_1 << SGE_TEXT("created openal device"));
}

sge::openal::device::~device()
{
	SGE_LOG_DEBUG(log(),log::_1 << SGE_TEXT("openal: closing device"));

	if (alcCloseDevice(device_) == AL_FALSE)
		if (!std::uncaught_exception())
			throw audio::exception(SGE_TEXT("error closing audio device. this means you tried to close the device before unloading all contexts and buffers"));

	SGE_OPENAL_ERROR_CHECK;
	SGE_LOG_DEBUG(log(),log::_1 << SGE_TEXT("closed openal device"));
}
