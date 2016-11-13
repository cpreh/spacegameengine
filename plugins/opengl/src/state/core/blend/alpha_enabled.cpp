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


#include <sge/opengl/common.hpp>
#include <sge/opengl/get_fun_ref.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/dest_blend_func.hpp>
#include <sge/opengl/state/convert/source_blend_func.hpp>
#include <sge/opengl/state/core/blend/alpha_enabled.hpp>
#include <sge/opengl/state/core/blend/context.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/separate.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor
sge::opengl::state::core::blend::alpha_enabled(
	sge::opengl::context::object &_context,
	sge::renderer::state::core::blend::alpha_enabled const &_variant
)
{
	return
		fcppt::variant::match(
			_variant,
			[](
				sge::renderer::state::core::blend::combined const &_combined
			)
			{
				return
					sge::opengl::state::wrap_error_handler<
						sge::opengl::state::actor
					>(
						std::bind(
							sge::opengl::get_fun_ref(
								::glBlendFunc
							),
							sge::opengl::state::convert::source_blend_func(
								_combined.source()
							),
							sge::opengl::state::convert::dest_blend_func(
								_combined.dest()
							)
						),
						FCPPT_TEXT("glBlendFunc")
					);
			},
			[
				&_context
			](
				sge::renderer::state::core::blend::separate const &_separate
			)
			{
				return
					sge::opengl::state::wrap_error_handler<
						sge::opengl::state::actor
					>(
						std::bind(
							fcppt::optional::to_exception(
								sge::opengl::context::use<
									sge::opengl::state::core::blend::context
								>(
									_context,
									_context.info()
								).config(),
								[]{
									return
										sge::renderer::unsupported{
											FCPPT_TEXT("blend func separate"),
											FCPPT_TEXT("1.4"),
											FCPPT_TEXT("")
										};
								}
							).blend_func_separate(),
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
		);
}
