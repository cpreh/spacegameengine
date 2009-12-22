/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include <sge/plugin/manager.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/collision/system.hpp>
#include <sge/font/system.hpp>
#include <sge/image/loader.hpp>
#include <sge/input/system.hpp>
#include <sge/model/loader.hpp>
#include <sge/renderer/system.hpp>
#include <sge/log/global.hpp>
#include <sge/mainloop/catch_block.hpp>
#include <fcppt/mpl/for_each.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <typeinfo>

namespace
{

struct print_plugins
{
	typedef void result_type;

	explicit print_plugins(
		sge::plugin::manager &
	);

	template<
		typename T
	>
	result_type
	operator()() const;
private:
	sge::plugin::manager &man;
};

}

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::plugin::manager man;

	typedef boost::mpl::vector8<
		sge::audio::loader,
		sge::audio::player,
		sge::collision::system,
		sge::font::system,
		sge::image::loader,
		sge::input::system,
		sge::model::loader,
		sge::renderer::system
	> plugins;

	fcppt::mpl::for_each<
		plugins
	>(
		print_plugins(
			man
		)
	);
}
SGE_MAINLOOP_CATCH_BLOCK

namespace
{

print_plugins::print_plugins(
	sge::plugin::manager &man)
:
	man(man)
{}

template<
	typename T
>
void
print_plugins::operator()() const
{
	fcppt::io::cout
		<< fcppt::type_name(
			typeid(T)
		)
		<< FCPPT_TEXT('\n');

	for(
		sge::plugin::iterator<T> it(
			man.begin<T>()
		);
		it != man.end<T>();
		++it
	)
	{
		sge::plugin::context_base const &base(
			it->info()
		);

		fcppt::io::cout
			<< FCPPT_TEXT("\tname: \"")
			<< base.name()
			<< FCPPT_TEXT("\", description: \"")
			<< base.description()
			<< FCPPT_TEXT("\"\n");
	}
}

}
