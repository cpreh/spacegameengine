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


#include <sge/image2d/multi_system.hpp>
#include <sge/image2d/multi_system_parameters.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/src/systems/modules/image2d/object.hpp>
#include <sge/systems/image2d.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>


sge::systems::modules::image2d::object::object(
	sge::plugin::manager &_manager,
	sge::systems::image2d const &_parameters
)
:
	image_multi_system_(
		fcppt::make_unique_ptr<
			sge::image2d::multi_system
		>(
			sge::image2d::multi_system_parameters(
				fcppt::ref(
					_manager
				),
				_parameters.extensions(),
				_parameters.capabilities()
			)
		)
	)
{
}

sge::systems::modules::image2d::object::~object()
{
}

sge::image2d::system &
sge::systems::modules::image2d::object::system() const
{
	return *image_multi_system_;
}
