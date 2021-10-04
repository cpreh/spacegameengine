//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PROGRAM_REPLACE_EXTRA_HPP_INCLUDED
#define SGE_CG_PROGRAM_REPLACE_EXTRA_HPP_INCLUDED

#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/program/replace_extra_callback.hpp>
#include <sge/cg/program/source.hpp>


namespace sge::cg::program
{

SGE_CG_DETAIL_SYMBOL
sge::cg::program::source
replace_extra(
	sge::cg::program::source const &,
	sge::cg::program::replace_extra_callback const &
);

}

#endif
