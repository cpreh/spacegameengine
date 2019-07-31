//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_INI_SKIPPER_HPP_INCLUDED
#define SGE_PARSE_INI_SKIPPER_HPP_INCLUDED

#include <fcppt/parse/blank.hpp>
#include <fcppt/parse/make_skipper.hpp>


namespace sge
{
namespace parse
{
namespace ini
{

inline
auto
skipper()
{
	return
		fcppt::parse::make_skipper(
			fcppt::parse::blank()
		);
}

}
}
}

#endif
