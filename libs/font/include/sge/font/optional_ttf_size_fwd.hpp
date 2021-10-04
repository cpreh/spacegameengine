//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_OPTIONAL_TTF_SIZE_FWD_HPP_INCLUDED
#define SGE_FONT_OPTIONAL_TTF_SIZE_FWD_HPP_INCLUDED

#include <sge/font/ttf_size.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge::font
{

using
optional_ttf_size
=
fcppt::optional::object<
	sge::font::ttf_size
>;

}

#endif
