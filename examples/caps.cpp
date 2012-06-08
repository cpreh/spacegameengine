/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_scoped_ptr.hpp>
#include <sge/renderer/caps/device_output.hpp>
#include <sge/renderer/plugin/object_scoped_ptr.hpp>
#include <sge/renderer/plugin/traits.hpp>
#include <awl/system/create.hpp>
#include <awl/system/object.hpp>
#include <awl/system/object_scoped_ptr.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	sge::plugin::manager manager(
		sge::config::plugin_path(),
		sge::plugin::optional_cache_ref()
	);

	sge::renderer::plugin::object_scoped_ptr const plugin(
		manager.collection<
			sge::renderer::system
		>().get(
			0u
		).load()
	);

	sge::renderer::system_scoped_ptr const render_sys(
		plugin->get()()
	);

	for(
		sge::renderer::adapter adapter(
			0u
		);
		adapter.get() < render_sys->device_count().get();
		++adapter
	)
		fcppt::io::cout()
			<<
			FCPPT_TEXT("Adapter ")
			<<
			adapter
			<<
			FCPPT_TEXT(": ")
			<<
			render_sys->device_caps(
				adapter
			)
			<< FCPPT_TEXT('\n');

	return EXIT_SUCCESS;
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
