//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/vf/dynamic/pos.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>


sge::renderer::vf::dynamic::pos::pos(
	sge::renderer::vf::dynamic::vector const &_type
)
:
	type_(
		_type
	)
{
}

sge::renderer::vf::dynamic::vector const &
sge::renderer::vf::dynamic::pos::type() const
{
	return type_;
}
