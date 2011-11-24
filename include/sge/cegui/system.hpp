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


#ifndef SGE_CEGUI_SYSTEM_HPP_INCLUDED
#define SGE_CEGUI_SYSTEM_HPP_INCLUDED

#include <sge/cegui/cursor_visibility.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context_fwd.hpp>
#include <sge/cegui/symbol.hpp>
#include <sge/cegui/detail/cegui_logger.hpp>
#include <sge/cegui/detail/image_codec.hpp>
#include <sge/cegui/detail/renderer.hpp>
#include <sge/cegui/detail/resource_provider.hpp>
#include <sge/cegui/detail/scoped_system.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUIString.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class WindowManager;
}

namespace sge
{
namespace cegui
{
class system
{
FCPPT_NONCOPYABLE(
	system);
public:
	SGE_CEGUI_SYMBOL explicit
	system(
		load_context const &,
		sge::renderer::device &,
		sge::image2d::system &,
		sge::charconv::system &,
		sge::viewport::manager &,
		sge::cegui::cursor_visibility::type);

	// Sends cegui a time pulse to calculate double clicks, tooltip
	// durations and so on
	SGE_CEGUI_SYMBOL void
	update(
		cegui::duration const &);

	SGE_CEGUI_SYMBOL void
	render();

	SGE_CEGUI_SYMBOL CEGUI::WindowManager &
	window_manager();

	SGE_CEGUI_SYMBOL CEGUI::WindowManager const &
	window_manager() const;

	SGE_CEGUI_SYMBOL
	~system();
private:
	// To keep the user interface clean, we permit access to the image
	// system and the renderer only to friend classes (see the accessor
	// functions below)
	friend class detail::texture;
	friend class detail::texture_target;
	friend class syringe;

	sge::charconv::system &charconv_system_;
	fcppt::filesystem::path prefix_;
	detail::cegui_logger cegui_logger_;
	detail::renderer renderer_;
	detail::image_codec image_codec_;
	detail::resource_provider resource_provider_;
	detail::scoped_system system_;
	fcppt::signal::scoped_connection viewport_change_connection_;
	// We have to memorize the old viewport so we don't call
	// notifyDisplaySizeChanged if old == new (costs performance)
	sge::renderer::pixel_rect old_viewport_;

	void
	viewport_change();

	sge::charconv::system &
	charconv_system() const;

	sge::image2d::system &
	image_system() const;

	sge::renderer::device &
	renderer() const;

	fcppt::filesystem::path const
	to_absolute_path(
		CEGUI::String const &,
		CEGUI::String const &);
};
}
}

#endif
