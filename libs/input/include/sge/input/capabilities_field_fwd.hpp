//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_CAPABILITIES_FIELD_FWD_HPP_INCLUDED
#define SGE_INPUT_CAPABILITIES_FIELD_FWD_HPP_INCLUDED

#include <sge/input/capabilities.hpp>
#include <fcppt/container/bitfield/enum_object_fwd.hpp>


namespace sge
{
namespace input
{

typedef
fcppt::container::bitfield::enum_object<
	sge::input::capabilities
>
capabilities_field;

}
}

#endif
