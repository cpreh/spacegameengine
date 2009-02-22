#ifndef SGE_OPENAL_DEVICE_HPP_INCLUDED
#define SGE_OPENAL_DEVICE_HPP_INCLUDED

#include "openal.hpp"
#include <sge/noncopyable.hpp>

namespace sge
{
namespace openal
{
class device
{
	SGE_NONCOPYABLE(device)
	public:
	explicit device(ALCchar const * = 0);
	ALCdevice *aldevice();
	~device();

	private:
	ALCdevice * const device_;
};
}
}

#endif
