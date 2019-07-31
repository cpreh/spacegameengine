//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
	~system();
};

}
}

#endif
