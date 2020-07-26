//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <sge/image2d/system_ref.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
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
	FCPPT_NONMOVABLE(
		system_impl
	);
public:
	system_impl(
		fcppt::log::context_reference,
		sge::cegui::load_context const &,
		sge::renderer::device::ffp_ref,
		sge::image2d::system_ref,
		sge::viewport::manager_ref,
		sge::cegui::cursor_visibility,
		sge::renderer::texture::emulate_srgb
	);

	~system_impl();

	static
	void
	update(
		sge::cegui::duration const &
	);

	void
	render(
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	[[nodiscard]]
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
