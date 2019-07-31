//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/dynamic/format.hpp>


sge::renderer::index::buffer_parameters::buffer_parameters(
	sge::renderer::index::dynamic::format const _format,
	sge::renderer::index::count const _count,
	sge::renderer::resource_flags_field const &_flags
)
:
	format_(
		_format
	),
	count_(
		_count
	),
	flags_(
		_flags
	)
{
}

sge::renderer::index::dynamic::format
sge::renderer::index::buffer_parameters::format() const
{
	return
		format_;
}

sge::renderer::index::count
sge::renderer::index::buffer_parameters::count() const
{
	return
		count_;
}

sge::renderer::resource_flags_field const &
sge::renderer::index::buffer_parameters::flags() const
{
	return
		flags_;
}
