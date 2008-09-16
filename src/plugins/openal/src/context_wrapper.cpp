#include "../context_wrapper.hpp"
#include "../device_wrapper.hpp"
#include "../error.hpp"
#include "../openal.hpp"
#include <sge/audio/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/log/headers.hpp>
#include <boost/foreach.hpp>
#include <vector>

sge::openal::context_wrapper::context_wrapper(
	device_wrapper &device,
	attribute_container const &attributes)
{
	std::vector<ALCint> al_attributes;
	BOOST_FOREACH(attribute_container::value_type const &v,attributes)
	{
		al_attributes.push_back(v.first);
		al_attributes.push_back(v.second);
	}
	// attribute array has to be null terminated
	al_attributes.push_back(static_cast<ALCint>(0));
	al_attributes.push_back(static_cast<ALCint>(0));

	SGE_LOG_DEBUG(log::global(),log::_1 << SGE_TEXT("creating audio context"))

	context_ = alcCreateContext(device.device(),&(al_attributes[0]));
	if (!context_)
		throw audio::exception(SGE_TEXT("Audio context could not be created. This could have the following reasons:\n-the application requested attributes which could not be satisfied\n-the attribute combination specified could not be satisfied\n-a combination of the specified attributes does not match the default value for an unspecified attribute. openal error was: "+error_string()));

	SGE_OPENAL_ERROR_CHECK;
	SGE_LOG_DEBUG(log::global(),log::_1 << SGE_TEXT("created audio context"))
}

ALCcontext *sge::openal::context_wrapper::context()
{
	return context_;
}

void sge::openal::context_wrapper::make_current()
{
	SGE_LOG_DEBUG(log::global(),
		log::_1 << SGE_TEXT("making audio context the current context"));

	if (alcMakeContextCurrent(context_) == ALC_FALSE)
		throw sge::audio::exception(SGE_TEXT("couldn't make created OpenAL context current. openal error was: "+error_string()));

	SGE_OPENAL_ERROR_CHECK;
	SGE_LOG_DEBUG(log::global(),
		log::_1 << SGE_TEXT("made audio context the current context"));
}

sge::openal::context_wrapper::~context_wrapper()
{
	ALCcontext const * const current = alcGetCurrentContext();
	if (current == context_)
	{
		alcMakeContextCurrent(0); SGE_OPENAL_ERROR_CHECK;
	}

	alcDestroyContext(context_); SGE_OPENAL_ERROR_CHECK;
}
