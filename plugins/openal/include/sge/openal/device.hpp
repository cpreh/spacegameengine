//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_DEVICE_HPP_INCLUDED
#define SGE_OPENAL_DEVICE_HPP_INCLUDED

#include <sge/openal/alc.hpp>
#include <sge/openal/device_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace openal
{

class device
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	explicit
	device(
		ALCchar const *
	);

	ALCdevice &
	aldevice();

	~device();
private:
	ALCdevice *const device_;
};

}
}

#endif
