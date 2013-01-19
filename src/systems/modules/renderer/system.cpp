/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/plugin/collection_fwd.hpp>
#include <sge/src/systems/merge_config_strings.hpp>
#include <sge/src/systems/modules/renderer/find_plugin.hpp>
#include <sge/src/systems/modules/renderer/system.hpp>
#include <sge/systems/detail/renderer.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/text.hpp>


sge::systems::modules::renderer::system::system(
	sge::renderer::plugin::collection const &_collection,
	sge::systems::detail::renderer const &_parameters,
	sge::parse::ini::start const &_config
)
:
	renderer_parameters_(
		_parameters.parameters().parameters()
	),
	system_pair_(
		sge::systems::modules::renderer::find_plugin(
			_collection,
			sge::systems::merge_config_strings(
				_parameters.parameters().name(),
				_config,
				sge::parse::ini::entry_name(
					FCPPT_TEXT("renderer")
				)
			),
			_parameters.parameters().caps(),
			_parameters.caps()
		)
	)
{
}

sge::systems::modules::renderer::system::~system()
{
}

awl::visual::object_unique_ptr
sge::systems::modules::renderer::system::create_visual(
	awl::system::object &_awl_system
)
{
	return
		this->get().create_visual(
			_awl_system,
			renderer_parameters_.pixel_format()
		);
}

sge::renderer::system &
sge::systems::modules::renderer::system::get() const
{
	return
		system_pair_.system();
}
