//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_PLATFORM_VERSION_HPP_INCLUDED
#define SGE_OPENCL_PLATFORM_VERSION_HPP_INCLUDED

#include <sge/opencl/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge::opencl::platform
{

class version
{
public:
	using
	unit
	=
	unsigned;

	SGE_OPENCL_DETAIL_SYMBOL
	explicit
	version(
		std::string const &
	);

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	unit
	major_part() const;

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	unit
	minor_part() const;

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	std::string const &
	platform_specific() const;
private:
	unit major_;
	unit minor_;
	std::string platform_specific_;
};

}

#endif
