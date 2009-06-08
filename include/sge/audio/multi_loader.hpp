#ifndef SGE_AUDIO_MULTI_LOADER_HPP_INCLUDED
#define SGE_AUDIO_MULTI_LOADER_HPP_INCLUDED

#include <sge/multi_loader.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/exception.hpp>

namespace sge
{
namespace audio
{
typedef multi_loader<
	loader,
	file,
	exception> multi_loader;
}
}

#endif
