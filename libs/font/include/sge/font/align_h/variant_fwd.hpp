//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_ALIGN_H_VARIANT_FWD_HPP_INCLUDED
#define SGE_FONT_ALIGN_H_VARIANT_FWD_HPP_INCLUDED

#include <sge/font/align_h/center_fwd.hpp>
#include <sge/font/align_h/left_fwd.hpp>
#include <sge/font/align_h/right_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sge
{
namespace font
{
namespace align_h
{

using
variant
=
fcppt::variant::object<
	sge::font::align_h::left,
	sge::font::align_h::center,
	sge::font::align_h::right
>;

}
}
}

#endif
