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


#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/opengl/core.hpp>
#include <sge/opengl/system.hpp>
#include <sge/renderer/core.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/window/system.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/name.hpp>


sge::opengl::core::core(
	fcppt::log::context &_log_context
)
:
	sge::renderer::core(),
	log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("opengl")
			}
		)
	}
{
}

sge::opengl::core::~core()
{
}

sge::renderer::system_unique_ptr
sge::opengl::core::create_system(
	sge::window::system &_system
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::system
		>(
			fcppt::make_unique_ptr<
				sge::opengl::system
			>(
				log_,
				_system.awl_system()
			)
		);
}

sge::renderer::caps::system_field
sge::opengl::core::caps() const
{
	return
		sge::renderer::caps::system_field{
			sge::renderer::caps::system::opengl,
			sge::renderer::caps::system::ffp
		};
}
