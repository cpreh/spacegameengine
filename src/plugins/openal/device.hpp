#ifndef SGE_OPENAL_DEVICE_HPP_INCLUDED
#define SGE_OPENAL_DEVICE_HPP_INCLUDED

#include "openal.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace openal
{
class device : boost::noncopyable
{
	public:
	device(ALCchar const * = 0);
	ALCdevice *aldevice() { return device_; }
	~device();

	private:
	ALCdevice * const device_;
};
}
}

#endif
