#ifndef SGE_AUDIO_LISTENER_HPP_INCLUDED
#define SGE_AUDIO_LISTENER_HPP_INCLUDED

#include "types.hpp"

namespace sge
{
namespace audio
{
class listener
{
	public:
	virtual point const pos() const = 0;
	virtual void pos(point const &) = 0;
	virtual angle const direction() const = 0;
	virtual void direction(angle const &) = 0;
};
}
}

#endif
