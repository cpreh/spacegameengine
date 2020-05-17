//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_PROCESSOR_REF_HPP_INCLUDED
#define SGE_INPUT_PROCESSOR_REF_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace input
{

using
processor_ref
=
fcppt::reference<
	sge::input::processor
>;

}
}

#endif
