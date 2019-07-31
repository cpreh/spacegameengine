//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <sge/renderer/vf/dynamic/normal.hpp>


sge::renderer::vf::dynamic::normal::normal(
	sge::renderer::vf::dynamic::element_type const _element_type
)
:
	element_type_(
		_element_type
	)
{
}

sge::renderer::vf::dynamic::element_type
sge::renderer::vf::dynamic::normal::element_type() const
{
	return element_type_;
}
