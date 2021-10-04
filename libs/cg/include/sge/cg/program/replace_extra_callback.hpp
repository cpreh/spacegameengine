//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PROGRAM_REPLACE_EXTRA_CALLBACK_HPP_INCLUDED
#define SGE_CG_PROGRAM_REPLACE_EXTRA_CALLBACK_HPP_INCLUDED

#include <sge/cg/program/replace_extra_function.hpp>
#include <fcppt/function_impl.hpp>


namespace sge::cg::program
{

using
replace_extra_callback
=
fcppt::function<
	sge::cg::program::replace_extra_function
>;

}

#endif
