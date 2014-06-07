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


#include <sge/font/plugin/collection_fwd.hpp>
#include <sge/font/plugin/object.hpp>
#include <sge/log/option_container.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/load_with_log_options.hpp>
#include <sge/plugin/object.hpp>
#include <sge/src/systems/modules/font/find_plugin.hpp>
#include <sge/systems/exception.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/optional_name.hpp>
#include <fcppt/text.hpp>


sge::font::plugin::object
sge::systems::modules::font::find_plugin(
	sge::font::plugin::collection const &_collection,
	sge::log::option_container const &_log_options,
	sge::systems::font const &_parameters
)
{
	sge::systems::optional_name const name(
		_parameters.name()
	);

	for(
		auto element
		:
		_collection
	)
	{
		if(
			!name
			||
			*name
			==
			element.info().name()
		)
			return
				sge::plugin::load_with_log_options(
					element,
					_log_options
				);
	}

	throw sge::systems::exception(
		name
		?
			FCPPT_TEXT("No plugin of type sge::font::system with name ")
			+
			name->get()
			+
			FCPPT_TEXT(" found!")

		:
			FCPPT_TEXT("No plugin of type sge::font::system found!")
	);
}
