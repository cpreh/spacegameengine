//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TARGET_ONSCREEN_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_TARGET_ONSCREEN_SURFACE_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/opengl/color_format_fwd.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/color_buffer/readable_surface.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/buffer/object_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace opengl
{
namespace target
{

class onscreen_surface
:
	public sge::renderer::color_buffer::readable_surface
{
	FCPPT_NONCOPYABLE(
		onscreen_surface
	);
public:
	explicit
	onscreen_surface(
		awl::window::object &
	);

	~onscreen_surface()
	override;
private:
	sge::renderer::color_buffer::readable_surface::const_view
	lock_c(
		sge::renderer::color_buffer::readable_surface::lock_area const &
	) const
	override;

	void
	unlock() const
	override;

	dim
	size() const
	override;

	sge::opengl::color_format
	gl_format() const;

	sge::image::color::format
	format() const
	override;

	awl::window::object &window_;

	typedef
	fcppt::container::buffer::object<
		sge::renderer::raw_value
	>
	buffer_type;

	typedef
	fcppt::optional::object<
		buffer_type
	>
	optional_buffer_type;

	mutable optional_buffer_type buffer_;
};

}
}
}

#endif
