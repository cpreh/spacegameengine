//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_TO_FCPPT_STRING_HPP_INCLUDED
#define SGE_CG_TO_FCPPT_STRING_HPP_INCLUDED

#include <sge/cg/string.hpp>
#include <sge/cg/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace cg
{

SGE_CG_DETAIL_SYMBOL
fcppt::string
to_fcppt_string(
	sge::cg::string const &
);

}
}

#endif
