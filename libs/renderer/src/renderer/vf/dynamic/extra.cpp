//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/vf/dynamic/extra.hpp>
#include <sge/renderer/vf/dynamic/extra_any.hpp>
#include <sge/renderer/vf/dynamic/index.hpp>


sge::renderer::vf::dynamic::extra::extra(
	sge::renderer::vf::dynamic::extra_any const &_type,
	sge::renderer::vf::dynamic::index const _index
)
:
	type_(
		_type
	),
	index_(
		_index
	)
{
}

sge::renderer::vf::dynamic::extra_any const &
sge::renderer::vf::dynamic::extra::type() const
{
	return
		type_;
}

sge::renderer::vf::dynamic::index
sge::renderer::vf::dynamic::extra::index() const
{
	return
		index_;
}
