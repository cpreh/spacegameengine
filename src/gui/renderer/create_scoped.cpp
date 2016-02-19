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


#include <sge/gui/impl/renderer/scoped.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/renderer/base_unique_ptr.hpp>
#include <sge/gui/renderer/create_scoped.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::gui::renderer::base_unique_ptr
sge::gui::renderer::create_scoped(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::gui::renderer::base
		>(
			fcppt::make_unique_ptr<
				sge::gui::impl::renderer::scoped
			>(
				_renderer,
				_context
			)
		);
}
