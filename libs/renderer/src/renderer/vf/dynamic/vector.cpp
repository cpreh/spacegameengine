//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/vf/dynamic/element_count.hpp>
#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>


sge::renderer::vf::dynamic::vector::vector(
	sge::renderer::vf::dynamic::element_type const _element_type,
	sge::renderer::vf::dynamic::element_count const _element_count
)
:
	element_type_(
		_element_type
	),
	element_count_(
		_element_count
	)
{
}

sge::renderer::vf::dynamic::element_type
sge::renderer::vf::dynamic::vector::element_type() const
{
	return
		element_type_;
}

sge::renderer::vf::dynamic::element_count
sge::renderer::vf::dynamic::vector::element_count() const
{
	return
		element_count_;
}
