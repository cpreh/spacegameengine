//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_MISC_POINT_SPRITE_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_MISC_POINT_SPRITE_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/config_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace misc
{
namespace point_sprite
{

class config
{
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		GLenum,
		point_sprite_flag_type
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		GLenum,
		vertex_shader_size_flag_type
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		GLenum,
		coord_replace_flag_type
	);

	config(
		point_sprite_flag_type,
		vertex_shader_size_flag_type,
		coord_replace_flag_type
	);

	point_sprite_flag_type
	point_sprite_flag() const;

	vertex_shader_size_flag_type
	vertex_shader_size_flag() const;

	coord_replace_flag_type
	coord_replace_flag() const;
private:
	point_sprite_flag_type point_sprite_flag_;

	vertex_shader_size_flag_type vertex_shader_size_flag_;

	coord_replace_flag_type coord_replace_flag_;
};

}
}
}
}
}
}

#endif
