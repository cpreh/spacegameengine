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


#include <sge/charconv/system_fwd.hpp>
#include <sge/src/systems/modules/charconv/base_unique_ptr.hpp>
#include <sge/src/systems/modules/charconv/object.hpp>
#include <sge/src/systems/modules/charconv/original.hpp>
#include <sge/src/systems/modules/charconv/wrapped.hpp>
#include <sge/systems/charconv.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::systems::modules::charconv::object::object(
	sge::systems::charconv const &_charconv
)
:
	base_(
		_charconv.system()
		?
			sge::systems::modules::charconv::base_unique_ptr(
				fcppt::make_unique_ptr<
					sge::systems::modules::charconv::wrapped
				>(
					*_charconv.system()
				)
			)
		:
			sge::systems::modules::charconv::base_unique_ptr(
				fcppt::make_unique_ptr<
					sge::systems::modules::charconv::original
				>()
			)
	)
{

}

sge::systems::modules::charconv::object::~object()
{
}

sge::charconv::system &
sge::systems::modules::charconv::object::system() const
{
	return base_->system();
}
