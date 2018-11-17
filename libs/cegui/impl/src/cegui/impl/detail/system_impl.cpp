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


#include <sge/cegui/cursor_visibility.hpp>
#include <sge/cegui/default_font.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/cegui/impl/log_name.hpp>
#include <sge/cegui/impl/scoped_render_context.hpp>
#include <sge/cegui/impl/texture_parameters.hpp>
#include <sge/cegui/impl/to_cegui_rect.hpp>
#include <sge/cegui/impl/detail/system_impl.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/target/viewport_is_null.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/math/box/comparison.hpp>
#include <fcppt/math/box/null.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Font.h>
#include <CEGUI/FontManager.h>
#include <CEGUI/ImageManager.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/Rect.h>
#include <CEGUI/Scheme.h>
#include <CEGUI/System.h>
#include <CEGUI/falagard/WidgetLookManager.h>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::cegui::detail::system_impl::system_impl(
	fcppt::log::context &_log_context,
	sge::cegui::load_context const &_load_context,
	sge::renderer::device::ffp &_renderer,
	sge::image2d::system &_image_system,
	sge::viewport::manager &_viewport_manager,
	sge::cegui::cursor_visibility const _cursor_visibility,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
:
	main_log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			sge::cegui::impl::log_name()
		)
	},
	system_log_{
		main_log_,
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("system")
			}
		)
	},
	prefix_(
		_load_context.scheme_file().parent_path()
	),
	cegui_logger_(
		main_log_
	),
	renderer_{
		main_log_,
		sge::cegui::impl::texture_parameters(
			prefix_,
			_image_system,
			_renderer,
			_emulate_srgb
		)
	},
	image_codec_(
		_image_system
	),
	resource_provider_{
		main_log_
	},
	scoped_system_(
		renderer_,
		image_codec_,
		resource_provider_
	),
	gui_context_(
		renderer_.getDefaultRenderTarget()
	),
	viewport_change_connection_(
		_viewport_manager.manage_callback(
			sge::viewport::manage_callback{
				std::bind(
					&sge::cegui::detail::system_impl::viewport_change,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	old_viewport_(
		fcppt::math::box::null<
			sge::renderer::pixel_rect
		>()
	)
{
	CEGUI::WidgetLookManager::setDefaultResourceGroup(
		sge::cegui::to_cegui_string(
			fcppt::filesystem::path_to_string(
				fcppt::optional::from(
					_load_context.looknfeel_directory(),
					[
						this
					]{
						return
							prefix_.get();
					}
				)
			)
		)
	);

	CEGUI::Font::setDefaultResourceGroup(
		sge::cegui::to_cegui_string(
			fcppt::filesystem::path_to_string(
				fcppt::optional::from(
					_load_context.font_directory(),
					[
						this
					]{
						return
							prefix_.get();
					}
				)
			)
		)
	);

	CEGUI::ImageManager::setImagesetDefaultResourceGroup(
		sge::cegui::to_cegui_string(
			fcppt::filesystem::path_to_string(
				fcppt::optional::from(
					_load_context.imageset_directory(),
					[
						this
					]{
						return
							prefix_.get();
					}
				)
			)
		)
	);

	CEGUI::Scheme::setDefaultResourceGroup(
		sge::cegui::to_cegui_string(
			fcppt::filesystem::path_to_string(
				prefix_.get()
			)
		)
	);

	CEGUI::SchemeManager::getSingleton().createFromFile(
		sge::cegui::to_cegui_string(
			fcppt::filesystem::path_to_string(
				_load_context.scheme_file().filename()
			)
		)
	);

	if(
		_cursor_visibility
		==
		sge::cegui::cursor_visibility::invisible
	)
		gui_context_.getMouseCursor().hide();

	fcppt::optional::maybe_void(
		_load_context.default_font(),
		[
			this
		](
			sge::cegui::default_font const &_default_font
		)
		{
			gui_context_.setDefaultFont(
				&CEGUI::FontManager::getSingleton().createFreeTypeFont(
					"",
					_default_font.font_size(),
					true,
					cegui::to_cegui_string(
						fcppt::filesystem::path_to_string(
							_default_font.path()
						)
					)
				)
			);
		}
	);

	this->viewport_change(
		_viewport_manager.viewport()
	);
}
FCPPT_PP_POP_WARNING

sge::cegui::detail::system_impl::~system_impl()
{
}

void
sge::cegui::detail::system_impl::update(
	sge::cegui::duration const &_duration
)
{
	CEGUI::System::getSingleton().injectTimePulse(
		_duration.count()
	);
}

void
sge::cegui::detail::system_impl::render(
	sge::renderer::context::ffp &_context
)
{
	sge::cegui::impl::scoped_render_context const context(
		renderer_,
		_context
	);

	gui_context_.draw();
}

CEGUI::GUIContext &
sge::cegui::detail::system_impl::gui_context()
{
	return
		gui_context_;
}

void
sge::cegui::detail::system_impl::viewport_change(
	sge::renderer::target::viewport _viewport
)
{
	FCPPT_LOG_DEBUG(
		system_log_,
		fcppt::log::out
			<< FCPPT_TEXT("viewport_change() with ")
			<< _viewport.get()
	);

	if(
		sge::renderer::target::viewport_is_null(
			_viewport
		)
	)
	{
		_viewport =
			sge::renderer::target::viewport(
				sge::renderer::pixel_rect(
					fcppt::math::vector::null<
						sge::renderer::pixel_rect::vector
					>(),
					fcppt::math::dim::fill<
						sge::renderer::pixel_rect::dim
					>(
						10u
					)
				)
			);
	}

	// Calling notifyDisplaySizeChanged with a null rect causes a strange problem
	if(
		sge::renderer::target::viewport_is_null(
			_viewport
		)
		||
		old_viewport_
		==
		_viewport
	)
		return;

	CEGUI::Rectf const new_area_cegui(
		sge::cegui::impl::to_cegui_rect(
			fcppt::math::box::structure_cast<
				fcppt::math::box::rect<
					float
				>,
				fcppt::cast::int_to_float_fun
			>(
				_viewport.get()
			)
		)
	);

	CEGUI::System::getSingleton().notifyDisplaySizeChanged(
		new_area_cegui.getSize()
	);

	// TODO:
	// We have to reset this manually. The cursor does receive its own
	// "notifyDisplaySizeChanged" but that (deliberately?) doesn't
	// update the constraint area
	gui_context_.getMouseCursor().setConstraintArea(
		&new_area_cegui
	);

	old_viewport_ =
		_viewport;
}
