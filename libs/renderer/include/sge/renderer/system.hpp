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


#ifndef SGE_RENDERER_SYSTEM_HPP_INCLUDED
#define SGE_RENDERER_SYSTEM_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/parameters_fwd.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
\brief Creates \link sge::renderer::device\endlink objects and renderable
visuals

\ingroup sge_renderer

The main class created by \linksge::renderer::core\endlink. This class creates
renderable visuals which can then be used to create renderable windows. Given
renderable windows, it also creates devices.
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
	*/
	virtual
	sge::renderer::device::core_unique_ptr
	create_core_renderer(
		sge::renderer::device::parameters const &parameters
	) = 0;

	/**
	\brief Creates an ffp renderer

	Creates an ffp renderer with properties from \a parameters
	*/
	virtual
	sge::renderer::device::ffp_unique_ptr
	create_ffp_renderer(
		sge::renderer::device::parameters const &parameters
	) = 0;

	/**
	\brief Creates a renderable visual

	Creates a renderable visual that satisfies the requirements of \a
	pixel_format and can be used with
	\link sge::renderer::system::create_renderer\endlink.

	\throw \link sge::renderer::exception\endlink if anything goes wrong
	*/
	virtual
	awl::visual::object_unique_ptr
	create_visual(
		sge::renderer::pixel_format::object const &pixel_format
	) = 0;

	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~system() = 0;
};

}
}

#endif
