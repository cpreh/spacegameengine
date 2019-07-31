//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_TO_CEGUI_STRING_HPP_INCLUDED
#define SGE_CEGUI_TO_CEGUI_STRING_HPP_INCLUDED

#include <sge/cegui/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace CEGUI
{
class String;
}

namespace sge
{
namespace cegui
{

SGE_CEGUI_DETAIL_SYMBOL
CEGUI::String
to_cegui_string(
	fcppt::string const &
);

}
}

#endif
