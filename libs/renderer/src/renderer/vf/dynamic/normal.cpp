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
	return
		this->element_type_;
}

bool
sge::renderer::vf::dynamic::operator==(
	sge::renderer::vf::dynamic::normal const &_left,
	sge::renderer::vf::dynamic::normal const &_right
)
{
	return
		_left.element_type() == _right.element_type();
}
