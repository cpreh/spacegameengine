//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GDIFONT_CREATE_FONT_HPP_INCLUDED
#define SGE_GDIFONT_CREATE_FONT_HPP_INCLUDED

#include <sge/font/parameters_fwd.hpp>
#include <sge/gdifont/hfont_unique_ptr.hpp>


namespace sge
{
namespace gdifont
{

sge::gdifont::hfont_unique_ptr
create_font(
	sge::font::parameters const &
);

}
}

#endif
