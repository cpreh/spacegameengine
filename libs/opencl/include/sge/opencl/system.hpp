//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_SYSTEM_HPP_INCLUDED
#define SGE_OPENCL_SYSTEM_HPP_INCLUDED

#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/platform/object.hpp>
#include <sge/opencl/platform/object_sequence.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace opencl
{
class system
{
	FCPPT_NONMOVABLE(
		system
	);
public:
	SGE_OPENCL_DETAIL_SYMBOL
	system();

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::platform::object_sequence &
	platforms();

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::platform::object_sequence const &
	platforms() const;

	SGE_OPENCL_DETAIL_SYMBOL
	~system();
private:
	opencl::platform::object_sequence platforms_;
};
}
}

#endif
