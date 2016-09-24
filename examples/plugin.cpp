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


#include <sge/audio/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/config/plugin_path.hpp>
#include <sge/font/system.hpp>
#include <sge/image2d/system.hpp>
#include <sge/input/system.hpp>
#include <sge/log/default_level_streams.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/renderer/core.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/use.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/optional_level.hpp>
#include <fcppt/mpl/for_each.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	fcppt::log::context log_context(
		fcppt::log::optional_level{
			fcppt::log::level::debug
		},
		sge::log::default_level_streams()
	);

	sge::plugin::manager manager(
		log_context,
		sge::config::plugin_path(),
		sge::plugin::optional_cache_ref()
	);

	typedef
	boost::mpl::vector6<
		sge::audio::loader,
		sge::audio::player,
		sge::font::system,
		sge::image2d::system,
		sge::input::system,
		sge::renderer::core
	>
	plugins;

	fcppt::mpl::for_each<
		plugins
	>(
		[
			&manager
		](
			auto const _tag
		)
		{
			FCPPT_USE(
				_tag
			);

			typedef
			fcppt::tag_type<
				decltype(
					_tag
				)
			>
			type;

			fcppt::io::cout()
				<<
				fcppt::type_name_from_info(
					typeid(
						type
					)
				)
				<<
				FCPPT_TEXT('\n');

			for(
				auto const &plugin
				:
				manager.collection<
					type
				>()
			)
			{
				sge::plugin::info const &info(
					plugin.info()
				);

				fcppt::io::cout()
					<<
					FCPPT_TEXT("\tname: \"")
					<<
					info.name()
					<<
					FCPPT_TEXT("\", description: \"")
					<<
					info.description()
					<<
					FCPPT_TEXT("\"\n");
			}
		}
	);
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<<
		_exception.string()
		<<
		FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_exception
)
{
	std::cerr
		<<
		_exception.what()
		<<
		'\n';

	return
		EXIT_FAILURE;
}
