//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_STRING_HPP_INCLUDED
#define SGE_CG_STRING_HPP_INCLUDED

#include <sge/cg/char_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cg
{

typedef std::basic_string<
	sge::cg::char_type
> string;

}
}

#endif
