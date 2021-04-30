//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_CURSOR_OPTION_FIELD_FWD_HPP_INCLUDED
#define SGE_SYSTEMS_CURSOR_OPTION_FIELD_FWD_HPP_INCLUDED

#include <sge/systems/cursor_option.hpp>
#include <fcppt/container/bitfield/object_fwd.hpp>


namespace sge
{
namespace systems
{

using
cursor_option_field
=
fcppt::container::bitfield::object<
	sge::systems::cursor_option
>;

}
}

#endif
