//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/vf/dynamic/any.hpp>
#include <sge/renderer/vf/dynamic/element.hpp>


sge::renderer::vf::dynamic::element::element(
	sge::renderer::vf::dynamic::any const &_info
)
:
	info_(
		_info
	)
{
}

sge::renderer::vf::dynamic::any const &
sge::renderer::vf::dynamic::element::info() const
{
	return info_;
}
