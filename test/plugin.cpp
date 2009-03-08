/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/system.hpp>
#include <sge/mpl/for_each.hpp>
#include <sge/text.hpp>
#include <sge/cout.hpp>
#include <boost/mpl/vector.hpp>
#include <typeinfo>

namespace
{

struct print_plugins {
	explicit print_plugins(
		sge::plugin::manager &);

	template<
		typename T
	>
	void
	operator()() const;
private:
	sge::plugin::manager &man;
};

}

int main()
{
	sge::plugin::manager man;

	typedef boost::mpl::vector<
		sge::audio::loader,
		sge::audio::player,
		sge::collision::system,
		sge::font::system,
		sge::image::loader,
		sge::input::system,
		sge::renderer::system
	> plugins;

	sge::mpl::for_each<
		plugins
	>(
		print_plugins(
			man
		)
	);
}

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
	sge::cout
		<< typeid(T).name()
		<< SGE_TEXT('\n');

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

		sge::cout
			<< SGE_TEXT('\t')
			<< base.name()
			<< SGE_TEXT(", ")
			<< base.description()
			<< SGE_TEXT('\n');
	}
}

}
