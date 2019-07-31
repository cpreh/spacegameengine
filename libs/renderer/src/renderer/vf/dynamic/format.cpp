//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>


sge::renderer::vf::dynamic::format::format(
	sge::renderer::vf::dynamic::part_list const &_parts
)
:
	parts_(
		_parts
	)
{
}

sge::renderer::vf::dynamic::part_list const &
sge::renderer::vf::dynamic::format::parts() const
{
	return parts_;
}
