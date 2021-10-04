//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_EVENT_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_EVENT_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/event/object_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::opencl::event
{

using
sequence
=
std::vector<
	sge::opencl::event::object_unique_ptr
>;

}

#endif
