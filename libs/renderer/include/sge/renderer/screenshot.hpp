//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_SCREENSHOT_HPP_INCLUDED
#define SGE_RENDERER_SCREENSHOT_HPP_INCLUDED

#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{

/**
\brief Takes a screenshot and saves it to a path

\ingroup sge_renderer

Takes a screenshot of the color surface of the onscreen target denoted by \a
device. It will be saved to \a path by \a system.

\note Make sure that \a system is able to save the file format specified by \a
path.

\param device The device to take the screenshot from

\param system The image system to use for saving

\param path The path to save the screenshot to
*/
SGE_RENDERER_DETAIL_SYMBOL
void
screenshot(
	sge::renderer::device::core const &device,
	sge::image2d::system &system,
	std::filesystem::path const &path
);

}
}

#endif
