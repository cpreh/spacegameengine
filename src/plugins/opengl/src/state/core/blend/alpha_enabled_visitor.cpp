/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/dest_blend_func.hpp>
#include <sge/opengl/state/convert/source_blend_func.hpp>
#include <sge/opengl/state/core/blend/alpha_enabled_visitor.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/separate.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/phoenix/bind.hpp>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::core::blend::alpha_enabled_visitor::alpha_enabled_visitor(
	sge::opengl::context::system::object &_system_context
)
:
	system_context_(
		_system_context
	)
{
}

// TODO: check what is supported here!

sge::opengl::state::core::blend::alpha_enabled_visitor::result_type
sge::opengl::state::core::blend::alpha_enabled_visitor::operator()(
	sge::renderer::state::core::blend::combined const &_combined
) const
{
	return
		sge::opengl::state::wrap_error_handler<
			sge::opengl::state::core::blend::alpha_enabled_visitor::result_type
		>(
			boost::phoenix::bind(
				::glBlendFunc,
				sge::opengl::state::convert::source_blend_func(
					_combined.source()
				),
				sge::opengl::state::convert::dest_blend_func(
					_combined.dest()
				)
			),
			FCPPT_TEXT("glBlendFunc")
		);
}

sge::opengl::state::core::blend::alpha_enabled_visitor::result_type
sge::opengl::state::core::blend::alpha_enabled_visitor::operator()(
	sge::renderer::state::core::blend::separate const &_separate
) const
{
	return
		sge::opengl::state::wrap_error_handler<
			sge::opengl::state::core::blend::alpha_enabled_visitor::result_type
		>(
			boost::phoenix::bind(
				::glBlendFuncSeparate,
				sge::opengl::state::convert::source_blend_func(
					_separate.color_source().get()
				),
				sge::opengl::state::convert::dest_blend_func(
					_separate.color_dest().get()
				),
				sge::opengl::state::convert::source_blend_func(
					_separate.alpha_source().get()
				),
				sge::opengl::state::convert::dest_blend_func(
					_separate.alpha_dest().get()
				)
			),
			FCPPT_TEXT("glBlendFuncSeparate")
		);
}
