#include "../context_wrapper.hpp"
#include "../device_wrapper.hpp"
#include "../error.hpp"
#include "../openal.hpp"
#include <sge/audio/exception.hpp>
#include <boost/foreach.hpp>
#include <vector>

sge::openal::context_wrapper::context_wrapper(device_wrapper &device,attribute_container const &attributes)
{
	std::vector<ALCint> al_attributes;
	BOOST_FOREACH(attribute_container::value_type const &v,attributes)
	{
		al_attributes.push_back(v.first);
		al_attributes.push_back(v.second);
	}

	if (alcCreateContext(device.device(),&al_attributes[0]))
		throw audio::exception(SGE_TEXT("Audio context could not be created. This could have the following reasons:\n-the application requested attributes which could not be satisfied\n-the attribute combination specified could not be satisfied\n-a combination of the specified attributes does not match the default value for an unspecified attribute"));
	SGE_OPENAL_ERROR_CHECK
}

ALCcontext *sge::openal::context_wrapper::context()
{
	return context_;
}

void sge::openal::context_wrapper::make_current()
{
	if (alcMakeContextCurrent(context_) != ALC_TRUE)
		throw sge::audio::exception(SGE_TEXT("couldn't make created OpenAL context current"));

	SGE_OPENAL_ERROR_CHECK
}

sge::openal::context_wrapper::~context_wrapper()
{
	alcMakeCurrent(0);
	SGE_OPENAL_ERROR_CHECK
	alcDestroyContext(context_);
	SGE_OPENAL_ERROR_CHECK
}
