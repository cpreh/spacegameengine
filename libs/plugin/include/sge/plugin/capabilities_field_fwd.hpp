//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_CAPABILITIES_FIELD_FWD_HPP_INCLUDED
#define SGE_PLUGIN_CAPABILITIES_FIELD_FWD_HPP_INCLUDED

#include <sge/plugin/capabilities.hpp>
#include <fcppt/container/bitfield/object_fwd.hpp>


namespace sge
{
namespace plugin
{

using
capabilities_field
=
fcppt::container::bitfield::object<
	sge::plugin::capabilities
>;

}
}

#endif
