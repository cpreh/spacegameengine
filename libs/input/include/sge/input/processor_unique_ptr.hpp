//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_PROCESSOR_UNIQUE_PTR_HPP_INCLUDED
#define SGE_INPUT_PROCESSOR_UNIQUE_PTR_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace input
{

typedef
fcppt::unique_ptr<
	sge::input::processor
>
processor_unique_ptr;

}
}

#endif
