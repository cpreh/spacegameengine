#include "../device_wrapper.hpp"
#include "../error.hpp"
#include "../openal.hpp"
#include <sge/audio/exception.hpp>
#include <sge/log/headers.hpp>
#include <sge/text.hpp>

sge::openal::device_wrapper::device_wrapper(ALCchar const * const specifier)
	: device_(alcOpenDevice(specifier))
{
	if (!device_)
		throw audio::exception(SGE_TEXT("error opening audio device. openal error was: "+error_string()));
	SGE_OPENAL_ERROR_CHECK;
	SGE_LOG_DEBUG(log::global(),log::_1 << SGE_TEXT("created openal device"));
}

ALCdevice *sge::openal::device_wrapper::device()
{
	return device_;
}

sge::openal::device_wrapper::~device_wrapper()
{
	alcCloseDevice(device_); SGE_OPENAL_ERROR_CHECK;
	SGE_LOG_DEBUG(log::global(),log::_1 << SGE_TEXT("closed openal device"));
}
