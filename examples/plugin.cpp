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


#include <sge/audio/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/config/plugin_path.hpp>
#include <sge/font/system.hpp>
#include <sge/image2d/system.hpp>
#include <sge/input/system.hpp>
#include <sge/log/global_context.hpp>
#include <sge/log/location.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/renderer/system.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/activate_levels_recursive.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/mpl/for_each.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


namespace
{

class print_plugins
{
	FCPPT_NONASSIGNABLE(
		print_plugins
	);
public:
	typedef void result_type;

	explicit
	print_plugins(
		sge::plugin::manager &
	);

	template<
		typename Type
	>
	result_type
	operator()() const;
private:
	sge::plugin::manager &manager_;
};

}

int
main()
try
{
	fcppt::log::activate_levels_recursive(
		sge::log::global_context(),
		sge::log::location(),
		fcppt::log::level::debug
	);

	sge::plugin::manager manager(
		sge::config::plugin_path(),
		sge::plugin::optional_cache_ref()
	);

	typedef boost::mpl::vector6<
		sge::audio::loader,
		sge::audio::player,
		sge::font::system,
		sge::image2d::system,
		sge::input::system,
		sge::renderer::system
	> plugins;

	fcppt::mpl::for_each<
		plugins
	>(
		print_plugins(
			manager
		)
	);
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_exception
)
{
	std::cerr
		<< _exception.what()
		<< '\n';

	return
		EXIT_FAILURE;
}

namespace
{

print_plugins::print_plugins(
	sge::plugin::manager &_manager
)
:
	manager_(
		_manager
	)
{
}

template<
	typename Type
>
void
print_plugins::operator()() const
{
	fcppt::io::cout()
		<< fcppt::type_name_from_info(
			typeid(
				Type
			)
		)
		<< FCPPT_TEXT('\n');

	for(
		auto const &plugin
		:
		manager_.collection<
			Type
		>()
	)
	{
		sge::plugin::info const &info(
			plugin.info()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("\tname: \"")
			<< info.name()
			<< FCPPT_TEXT("\", description: \"")
			<< info.description()
			<< FCPPT_TEXT("\"\n");
	}
}

}
