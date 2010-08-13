#ifndef SGE_AUDIO_BUFFER_HPP_INCLUDED
#define SGE_AUDIO_BUFFER_HPP_INCLUDED

#include <sge/audio/sound/positional_ptr.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/base_ptr.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace audio
{
class SGE_CLASS_SYMBOL buffer
{
FCPPT_NONCOPYABLE(buffer)
public:
	SGE_SYMBOL explicit 
	buffer();

	virtual sound::positional_ptr const
	create_positional(
		sound::positional_parameters const&) = 0;

	virtual sound::base_ptr const
	create_nonpositional() = 0;

	SGE_SYMBOL virtual 
	~buffer();
};
}
}

#endif
