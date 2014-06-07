/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/config/plugin_path.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/renderer/core.hpp>
#include <sge/renderer/core_unique_ptr.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/device_output.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/renderer/plugin/object.hpp>
#include <awl/system/create.hpp>
#include <awl/system/object.hpp>
#include <awl/system/object_unique_ptr.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	sge::plugin::manager manager(
		sge::config::plugin_path(),
		sge::plugin::optional_cache_ref()
	);

	sge::renderer::plugin::object const plugin(
		manager.collection<
			sge::renderer::core
		>().get(
			0u
		).load()
	);

	sge::renderer::core_unique_ptr const render_core(
		plugin.get()()
	);

	awl::system::object_unique_ptr const awl_system(
		awl::system::create()
	);

	sge::renderer::system_unique_ptr const render_sys(
		render_core->create_system(
			*awl_system
		)
	);

	for(
		sge::renderer::device::index index(
			0u
		);
		index.get() < render_sys->device_count().get();
		++index
	)
		fcppt::io::cout()
			<<
			std::boolalpha
			<<
			FCPPT_TEXT("Device ")
			<<
			index
			<<
			FCPPT_TEXT(": ")
			<<
			render_sys->device_caps(
				index
			)
			<< FCPPT_TEXT('\n');

	return
		EXIT_SUCCESS;
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
