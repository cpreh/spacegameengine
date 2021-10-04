//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_FOCUS_SCOPED_FD_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_SCOPED_FD_HPP_INCLUDED

#include <awl/backends/posix/fd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::wlinput::focus
{

class scoped_fd
{
	FCPPT_NONMOVABLE(
		scoped_fd
	);
public:
	explicit
	scoped_fd(
		awl::backends::posix::fd
	);

	~scoped_fd();
private:
	awl::backends::posix::fd const fd_;
};

}

#endif
