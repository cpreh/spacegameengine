//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_WGL_VISUAL_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_WGL_VISUAL_CONFIG_HPP_INCLUDED

#include <sge/opengl/wgl/extension_set.hpp>
#include <sge/opengl/wgl/scoped_current_fwd.hpp>
#include <sge/opengl/wgl/visual/config_fwd.hpp>
#include <sge/opengl/wgl/visual/optional_pixel_format_types.hpp>
#include <fcppt/optional/object_impl.hpp>


namespace sge
{
namespace opengl
{
namespace wgl
{
namespace visual
{

class config
{
public:
	config(
		sge::opengl::wgl::extension_set const &,
		sge::opengl::wgl::scoped_current const &
	);

	sge::opengl::wgl::visual::optional_pixel_format_types
	pixel_format_types() const;

	typedef
	fcppt::optional::object<
		GLint
	>
	optional_int;

	optional_int
	multi_sample_flag() const;

	optional_int
	srgb_flag() const;
private:
	sge::opengl::wgl::visual::optional_pixel_format_types pixel_format_types_;

	optional_int multi_sample_flag_;

	optional_int srgb_flag_;
};

}
}
}
}

#endif
