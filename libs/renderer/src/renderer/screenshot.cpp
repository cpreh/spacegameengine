//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image2d/save_from_view.hpp>
#include <sge/renderer/screenshot.hpp>
#include <sge/renderer/color_buffer/const_scoped_surface_lock.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


void
sge::renderer::screenshot(
	sge::renderer::device::core const &_renderer,
	sge::image2d::system &_system,
	std::filesystem::path const &_path
)
{
	sge::renderer::color_buffer::const_scoped_surface_lock const lock(
		fcppt::make_cref(
			_renderer.onscreen_target().surface()
		)
	);

	sge::image2d::save_from_view(
		_system,
		lock.value(),
		_path
	);
}
