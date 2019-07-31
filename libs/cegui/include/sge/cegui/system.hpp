//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_SYSTEM_HPP_INCLUDED
#define SGE_CEGUI_SYSTEM_HPP_INCLUDED

#include <sge/cegui/cursor_visibility_fwd.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context_fwd.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <sge/cegui/detail/system_impl_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_fwd.hpp>


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
	SGE_CEGUI_DETAIL_SYMBOL
	system(
		fcppt::log::context &,
		sge::cegui::load_context const &,
		sge::renderer::device::ffp &,
		sge::image2d::system &,
		sge::viewport::manager &,
		sge::cegui::cursor_visibility,
		sge::renderer::texture::emulate_srgb
	);

	SGE_CEGUI_DETAIL_SYMBOL
	~system();

	// Sends cegui a time pulse to calculate double clicks, tooltip
	// durations and so on
	SGE_CEGUI_DETAIL_SYMBOL
	void
	update(
		sge::cegui::duration const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	void
	render(
		sge::renderer::context::ffp &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	CEGUI::WindowManager &
	window_manager();

	SGE_CEGUI_DETAIL_SYMBOL
	CEGUI::WindowManager const &
	window_manager() const;

	SGE_CEGUI_DETAIL_SYMBOL
	CEGUI::GUIContext &
	gui_context();

	SGE_CEGUI_DETAIL_SYMBOL
	CEGUI::GUIContext const &
	gui_context() const;
private:
	typedef
	fcppt::unique_ptr<
		sge::cegui::detail::system_impl
	>
	system_impl_ptr;

	system_impl_ptr const impl_;
};

}
}

#endif
