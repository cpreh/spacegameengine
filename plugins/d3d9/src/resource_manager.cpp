//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/resource_manager.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::d3d9::resource_manager::resource_manager()
:
	resources_()
{
}

sge::d3d9::resource_manager::~resource_manager()
{
}

void
sge::d3d9::resource_manager::add(
	d3d9::resource &_resource
)
{
	resources_.push_back(
		_resource
	);
}

void
sge::d3d9::resource_manager::release()
{
	std::for_each(
		resources_.begin(),
		resources_.end(),
		std::bind(
			&sge::d3d9::resource::loss,
			std::placeholders::_1
		)
	);
}

void
sge::d3d9::resource_manager::reinit()
{
	std::for_each(
		resources_.begin(),
		resources_.end(),
		std::bind(
			&sge::d3d9::resource::reset,
			std::placeholders::_1
		)
	);
}
