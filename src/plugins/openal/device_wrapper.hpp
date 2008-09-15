#ifndef SGE_OPENAL_DEVICE_WRAPPER_HPP_INCLUDED
#define SGE_OPENAL_DEVICE_WRAPPER_HPP_INCLUDED


class ALCdevice;

namespace sge
{
namespace openal
{
class device_wrapper
{
	public:
	device_wrapper(ALCdevice *);
	ALCdevice *device();
	~device_wrapper();

	private:
	ALCdevice * const device_;
};
}
}

#endif
