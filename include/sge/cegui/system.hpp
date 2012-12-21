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


#ifndef SGE_CEGUI_SYSTEM_HPP_INCLUDED
#define SGE_CEGUI_SYSTEM_HPP_INCLUDED

#include <sge/cegui/cursor_visibility_fwd.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context_fwd.hpp>
#include <sge/cegui/symbol.hpp>
#include <sge/cegui/detail/system_impl_fwd.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace CEGUI
{
class GUIContext;
class WindowManager;
}

namespace sge
{
namespace cegui
{

class system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	SGE_CEGUI_SYMBOL
	system(
		sge::cegui::load_context const &,
		sge::renderer::device::ffp &,
		sge::image2d::system &,
		sge::charconv::system &,
		sge::viewport::manager &,
		sge::cegui::cursor_visibility,
		sge::renderer::texture::emulate_srgb::type
	);

	SGE_CEGUI_SYMBOL
	~system();

	// Sends cegui a time pulse to calculate double clicks, tooltip
	// durations and so on
	SGE_CEGUI_SYMBOL
	void
	update(
		sge::cegui::duration const &
	);

	SGE_CEGUI_SYMBOL
	void
	render(
		sge::renderer::context::ffp &
	);

	SGE_CEGUI_SYMBOL
	CEGUI::WindowManager &
	window_manager();

	SGE_CEGUI_SYMBOL
	CEGUI::WindowManager const &
	window_manager() const;

	SGE_CEGUI_SYMBOL
	CEGUI::GUIContext &
	gui_context();

	SGE_CEGUI_SYMBOL
	CEGUI::GUIContext const &
	gui_context() const;

	SGE_CEGUI_SYMBOL
	sge::charconv::system &
	charconv_system() const;
private:
	typedef fcppt::scoped_ptr<
		sge::cegui::detail::system_impl
	> system_impl_ptr;

	system_impl_ptr const impl_;
};

}
}

#endif
