#ifndef SGE_OPENAL_DEVICE_WRAPPER_HPP_INCLUDED
#define SGE_OPENAL_DEVICE_WRAPPER_HPP_INCLUDED

#include "openal.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace openal
{
class device_wrapper : boost::noncopyable
{
	public:
	device_wrapper(ALCchar const * = 0);
	ALCdevice *device();
	~device_wrapper();

	private:
	ALCdevice * const device_;
};
}
}

#endif
