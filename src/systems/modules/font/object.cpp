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


#include <sge/font/system.hpp>
#include <sge/font/plugin/collection_fwd.hpp>
#include <sge/font/plugin/traits.hpp>
#include <sge/plugin/object.hpp>
#include <sge/src/systems/modules/charconv/object.hpp>
#include <sge/src/systems/modules/font/find_plugin.hpp>
#include <sge/src/systems/modules/font/object.hpp>
#include <sge/systems/font_fwd.hpp>


sge::systems::modules::font::object::object(
	sge::font::plugin::collection const &_collection,
	sge::systems::font const &_parameters,
	sge::systems::modules::charconv::object const &_charconv
)
:
	font_plugin_(
		sge::systems::modules::font::find_plugin(
			_collection,
			_parameters
		)
	),
	font_system_(
		font_plugin_->get()(
			_charconv.system()
		)
	)
{
}

sge::systems::modules::font::object::~object()
{
}

sge::font::system &
sge::systems::modules::font::object::system() const
{
	return *font_system_;
}
