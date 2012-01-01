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


#include <sge/log/global.hpp>
#include <sge/renderer/state/any.hpp>
#include <sge/renderer/state/any_key.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/map.hpp>
#include <sge/src/renderer/state/make_key.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

bool
insert_to_map(
	sge::renderer::state::map &_map,
	sge::renderer::state::any const &_state
)
{
	return
		_map.insert(
			std::make_pair(
				sge::renderer::state::make_key(
					_state
				),
				_state
			)
		).second;

}

}

sge::renderer::state::list::list()
:
	map_()
{
}

sge::renderer::state::list::list(
	state::any const &_arg
)
:
	map_()
{
	::insert_to_map(
		map_,
		_arg
	);
}

sge::renderer::state::list::~list()
{
}

sge::renderer::state::list const
sge::renderer::state::list::operator()(
	state::any const &_arg
) const
{
	state::list temp(
		*this
	);

	if(
		!::insert_to_map(
			temp.map_,
			_arg
		)
	)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Duplicate renderer state of type \"")
				<< fcppt::type_name(
					_arg.type()
				)
				<< FCPPT_TEXT("\" given!")
		);

	return temp;
}

void
sge::renderer::state::list::overwrite(
	state::any const &_state
)
{
	state::any_key const key(
		state::make_key(
			_state
		)
	);

	state::map::iterator const it(
		map_.find(
			key
		)
	);

	if(
		it == map_.end()
	)
		map_.insert(
			std::make_pair(
				key,
				_state
			)
		);
	else
		it->second = _state;
}

sge::renderer::state::map const &
sge::renderer::state::list::values() const
{
	return map_;
}
