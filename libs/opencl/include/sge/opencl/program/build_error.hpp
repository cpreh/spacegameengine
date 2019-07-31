//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_PROGRAM_BUILD_ERROR_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_BUILD_ERROR_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/opencl/exception.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace opencl
{
namespace program
{

class SGE_CORE_DETAIL_CLASS_SYMBOL build_error
:
	public sge::opencl::exception
{
public:
	SGE_OPENCL_DETAIL_SYMBOL
	explicit
	build_error(
		fcppt::string const &
	);

	SGE_OPENCL_DETAIL_SYMBOL
	build_error(
		build_error &&
	);

	SGE_OPENCL_DETAIL_SYMBOL
	build_error(
		build_error const &
	);

	SGE_OPENCL_DETAIL_SYMBOL
	build_error &
	operator=(
		build_error &&
	);

	SGE_OPENCL_DETAIL_SYMBOL
	build_error &
	operator=(
		build_error const &
	);

	SGE_OPENCL_DETAIL_SYMBOL
	~build_error() noexcept
	override;

	SGE_OPENCL_DETAIL_SYMBOL
	fcppt::string const &
	message() const;
private:
	fcppt::string message_;
};

}
}
}

#endif
