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


#ifndef SGE_CEGUI_IMPL_DETAIL_SYSTEM_IMPL_HPP_INCLUDED
#define SGE_CEGUI_IMPL_DETAIL_SYSTEM_IMPL_HPP_INCLUDED

#include <sge/cegui/cursor_visibility_fwd.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context_fwd.hpp>
#include <sge/cegui/detail/system_impl_fwd.hpp>
#include <sge/cegui/impl/cegui_logger.hpp>
#include <sge/cegui/impl/image_codec.hpp>
#include <sge/cegui/impl/prefix.hpp>
#include <sge/cegui/impl/renderer.hpp>
#include <sge/cegui/impl/resource_provider.hpp>
#include <sge/cegui/impl/scoped_system.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/GUIContext.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cegui
{
namespace detail
{

class system_impl
{
	FCPPT_NONCOPYABLE(
		system_impl
	);
public:
	system_impl(
		fcppt::log::context &,
		sge::cegui::load_context const &,
		sge::renderer::device::ffp &,
		sge::image2d::system &,
		sge::viewport::manager &,
		sge::cegui::cursor_visibility,
		sge::renderer::texture::emulate_srgb
	);

	~system_impl();

	void
	update(
		sge::cegui::duration const &
	);

	void
	render(
		sge::renderer::context::ffp &
	);

	CEGUI::GUIContext &
	gui_context();
private:
	void
	viewport_change(
		sge::renderer::target::viewport
	);

	fcppt::log::object main_log_;

	fcppt::log::object system_log_;

	sge::cegui::impl::prefix const prefix_;

	sge::cegui::impl::cegui_logger cegui_logger_;

	sge::cegui::impl::renderer renderer_;

	sge::cegui::impl::image_codec image_codec_;

	sge::cegui::impl::resource_provider resource_provider_;

	sge::cegui::impl::scoped_system const scoped_system_;

	CEGUI::GUIContext gui_context_;

	fcppt::signal::auto_connection const viewport_change_connection_;

	// We have to memorize the old viewport so we don't call
	// notifyDisplaySizeChanged if old == new (costs performance)
	sge::renderer::target::viewport old_viewport_;
};

}
}
}

#endif
