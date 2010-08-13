#ifndef SGE_PLUGINS_AUDIO_NULL_BUFFER_HPP_INCLUDED
#define SGE_PLUGINS_AUDIO_NULL_BUFFER_HPP_INCLUDED

#include "positional.hpp"
#include <sge/audio/buffer.hpp>

namespace sge
{
namespace audio_null
{
class buffer
:
	public sge::audio::buffer
{
public:
	audio::sound::positional_ptr const
	create_positional(
		audio::sound::positional_parameters const&)
	{
		return audio::sound::positional_ptr(
			new positional());
	}

	audio::sound::base_ptr const
	create_nonpositional()
	{
		return audio::sound::base_ptr(
			new positional());
	}
};
}
}

#endif
