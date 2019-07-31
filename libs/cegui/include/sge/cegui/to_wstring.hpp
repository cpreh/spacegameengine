//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_TO_WSTRING_HPP_INCLUDED
#define SGE_CEGUI_TO_WSTRING_HPP_INCLUDED

#include <sge/cegui/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class String;
}

namespace sge
{
namespace cegui
{

SGE_CEGUI_DETAIL_SYMBOL
std::wstring
to_wstring(
	CEGUI::String const &
);

}
}

#endif
