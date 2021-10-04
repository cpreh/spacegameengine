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
#include <sge/image2d/system_ref.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace CEGUI
{
class GUIContext;
class WindowManager;
}

namespace sge::cegui
{

class system
{
	FCPPT_NONMOVABLE(
		system
	);
public:
	SGE_CEGUI_DETAIL_SYMBOL
	system(
		fcppt::log::context_reference,
		sge::cegui::load_context const &,
		sge::renderer::device::ffp_ref,
		sge::image2d::system_ref,
		sge::viewport::manager_ref,
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
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	[[nodiscard]]
	SGE_CEGUI_DETAIL_SYMBOL
	CEGUI::WindowManager &
	window_manager();

	[[nodiscard]]
	SGE_CEGUI_DETAIL_SYMBOL
	CEGUI::WindowManager const &
	window_manager() const;

	[[nodiscard]]
	SGE_CEGUI_DETAIL_SYMBOL
	CEGUI::GUIContext &
	gui_context();

	[[nodiscard]]
	SGE_CEGUI_DETAIL_SYMBOL
	CEGUI::GUIContext const &
	gui_context() const;
private:
	using
	system_impl_ptr
	=
	fcppt::unique_ptr<
		sge::cegui::detail::system_impl
	>;

	system_impl_ptr const impl_;
};

}

#endif
