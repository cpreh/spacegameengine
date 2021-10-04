//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_FOCUS_MMAP_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_MMAP_HPP_INCLUDED

#include <awl/backends/posix/fd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace sge::wlinput::focus
{

class mmap
{
	FCPPT_NONMOVABLE(
		mmap
	);
public:
	mmap(
		awl::backends::posix::fd,
		std::uint32_t
	);

	~mmap();

	[[nodiscard]]
	char const *
	string() const;
private:
	std::size_t const size_;

	char *const string_;
};

}

#endif
