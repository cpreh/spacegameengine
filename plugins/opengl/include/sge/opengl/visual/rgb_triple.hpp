//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VISUAL_RGB_TRIPLE_HPP_INCLUDED
#define SGE_OPENGL_VISUAL_RGB_TRIPLE_HPP_INCLUDED

#include <sge/opengl/visual/rgb_triple_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace opengl
{
namespace visual
{

class rgb_triple
{
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		red_bits
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		green_bits
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		blue_bits
	);

	rgb_triple(
		sge::opengl::visual::rgb_triple::red_bits,
		sge::opengl::visual::rgb_triple::green_bits,
		sge::opengl::visual::rgb_triple::blue_bits
	);

	sge::opengl::visual::rgb_triple::red_bits
	red() const;

	sge::opengl::visual::rgb_triple::green_bits
	green() const;

	sge::opengl::visual::rgb_triple::blue_bits
	blue() const;
private:
	sge::opengl::visual::rgb_triple::red_bits red_;

	sge::opengl::visual::rgb_triple::green_bits green_;

	sge::opengl::visual::rgb_triple::blue_bits blue_;
};

}
}
}

#endif
