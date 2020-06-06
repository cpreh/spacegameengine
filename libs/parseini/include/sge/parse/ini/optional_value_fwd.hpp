//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_INI_OPTIONAL_VALUE_FWD_HPP_INCLUDED
#define SGE_PARSE_INI_OPTIONAL_VALUE_FWD_HPP_INCLUDED

#include <sge/parse/ini/value.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace parse
{
namespace ini
{

using
optional_value
=
fcppt::optional::object<
	sge::parse::ini::value
>;

}
}
}

#endif
