//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_FLAGS_FIELD_FWD_HPP_INCLUDED
#define SGE_FONT_FLAGS_FIELD_FWD_HPP_INCLUDED

#include <sge/font/flags.hpp>
#include <fcppt/container/bitfield/enum_object_fwd.hpp>


namespace sge
{
namespace font
{

using
flags_field
=
fcppt::container::bitfield::enum_object<
	sge::font::flags
>;

}
}

#endif
