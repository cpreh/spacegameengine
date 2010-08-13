#ifndef SGE_PLUGINS_OPENAL_BUFFER_HPP_INCLUDED
#define SGE_PLUGINS_OPENAL_BUFFER_HPP_INCLUDED

#include "openal.hpp"
#include <sge/audio/buffer.hpp>
#include <sge/audio/file_ptr.hpp>
#include <sge/audio/sound/positional_ptr.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/base_ptr.hpp>

namespace sge
{
namespace openal
{
class buffer
:
	public audio::buffer
{
public:
	explicit
	buffer(
		audio::file_ptr);
	
	audio::sound::positional_ptr const
	create_positional(
		audio::sound::positional_parameters const&);

	audio::sound::base_ptr const
	create_nonpositional();

	~buffer();
private:
	ALuint buffer_;
};
}
}

#endif
