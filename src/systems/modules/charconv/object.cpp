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


#include <sge/charconv/plugin.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/charconv/system_ptr.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/src/systems/modules/charconv/object.hpp>


sge::systems::modules::charconv::object::object(
	sge::plugin::manager &_manager
)
:
	charconv_plugin_(
		_manager.plugin<
			sge::charconv::system
		>().load()
	),
	charconv_system_(
		charconv_plugin_->get()()
	)
{
}

sge::systems::modules::charconv::object::~object()
{
}

sge::charconv::system &
sge::systems::modules::charconv::object::system() const
{
	return *charconv_system_;
}
