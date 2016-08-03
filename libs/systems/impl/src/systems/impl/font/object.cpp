/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/impl/font/find_plugin.hpp>
#include <sge/systems/impl/font/object.hpp>
#include <fcppt/log/context_fwd.hpp>


sge::systems::impl::font::object::object(
	fcppt::log::context &_log_context,
	sge::font::plugin::collection const &_collection,
	sge::systems::font const &_parameters
)
:
	font_plugin_(
		sge::systems::impl::font::find_plugin(
			_collection,
			_parameters
		)
	),
	font_system_(
		font_plugin_.get()(
			_log_context
		)
	)
{
}

sge::systems::impl::font::object::~object()
{
}

sge::font::system &
sge::systems::impl::font::object::system() const
{
	return
		*font_system_;
}
