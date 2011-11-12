/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/state/list.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/variant/object_impl.hpp>


sge::renderer::state::list::list()
:
	set_()
{
}

sge::renderer::state::list::list(
	state::any const &_any
)
:
	set_()
{
	set_.insert(
		_any
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
		!temp.set_.insert(
			_arg
		).second
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
	set_.erase(
		_state
	);

	set_.insert(
		_state
	);
}

sge::renderer::state::set const &
sge::renderer::state::list::values() const
{
	return set_;
}
