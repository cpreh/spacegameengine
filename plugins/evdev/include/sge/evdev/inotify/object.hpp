//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_INOTIFY_OBJECT_HPP_INCLUDED
#define SGE_EVDEV_INOTIFY_OBJECT_HPP_INCLUDED

#include <sge/evdev/inotify/object_fwd.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace evdev
{
namespace inotify
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object();

	~object();

	awl::backends::posix::fd
	fd() const;
private:
	awl::backends::posix::fd const fd_;
};

}
}
}

#endif
