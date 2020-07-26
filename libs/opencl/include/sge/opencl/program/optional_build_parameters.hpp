//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_PROGRAM_OPTIONAL_BUILD_PARAMETERS_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_OPTIONAL_BUILD_PARAMETERS_HPP_INCLUDED

#include <sge/opencl/program/build_parameters_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace opencl
{
namespace program
{

using
optional_build_parameters
=
fcppt::optional::object<
	sge::opencl::program::build_parameters
>;

}
}
}

#endif
