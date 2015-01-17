/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_SYSTEM_HPP_INCLUDED
#define SGE_RENDERER_SYSTEM_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/caps/device_fwd.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/index_fwd.hpp>
#include <sge/renderer/device/parameters_fwd.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
\brief Creates sge::renderer::device objects and renderable visuals

\ingroup sge_renderer

The main class created by sge::renderer::core. In order to render anything, you
have to create an sge::renderer::device through this class. If you don't have a
renderable window to pass, you can create a renderable visual that can be used
to create one.
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL system
{
	FCPPT_NONCOPYABLE(
		system
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	system();
public:
	/**
	\brief Creates a core renderer

	Creates a core renderer with properties from \a parameters

	\param parameters The parameters to use
	*/
	virtual
	sge::renderer::device::core_unique_ptr
	create_core_renderer(
		sge::renderer::device::parameters const &parameters
	) = 0;

	/**
	\brief Creates an ffp renderer

	Creates an ffp renderer with properties from \a parameters

	\param parameters The parameters to use
	*/
	virtual
	sge::renderer::device::ffp_unique_ptr
	create_ffp_renderer(
		sge::renderer::device::parameters const &parameters
	) = 0;

	/**
	\brief Creates a renderable visual that satisfies the requirements of
	\a params

	Creates a renderable visual that satisfies the requirements of \a
	params and can be used with sge::renderer::system::create_renderer.

	\param pixel_format The pixel format to use

	\throw sge::renderer::exception if anything goes wrong

	\return An awl::visual::object_unique_ptr that may not be null
	*/
	virtual
	awl::visual::object_unique_ptr
	create_visual(
		sge::renderer::pixel_format::object const &pixel_format
	) = 0;

	/**
	\brief Returns the number of devices
	*/
	virtual
	sge::renderer::caps::device_count const
	device_count() const = 0;

	/**
	\brief Queries the capabilities of a device

	Returns the capabilities of the device identified by \a index.

	\param index The device to query the capabilities for

	\warning The behavior is undefined if index is equal to or greater
	than the device count.
	*/
	virtual
	sge::renderer::caps::device const &
	device_caps(
		sge::renderer::device::index index
	) const = 0;

	/**
	\brief Queries the available display modes of a device

	Returns the display modes of the device identified by \a index.

	\param index The device to query the display modes of

	\warning The behavior is undefined if index is equal to or greater
	than the device count.
	*/
	virtual
	sge::renderer::display_mode::container
	display_modes(
		sge::renderer::device::index index
	) const = 0;

	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~system() = 0;
};

}
}

#endif
