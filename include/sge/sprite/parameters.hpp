#ifndef SGE_SPRITE_PARAMETERS_HPP_INCLUDED
#define SGE_SPRITE_PARAMETERS_HPP_INCLUDED

#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/sprite/point.hpp>
#include <sge/sprite/dim.hpp>
#include <sge/sprite/color.hpp>
#include <sge/sprite/depth_type.hpp>
#include <sge/sprite/rotation_type.hpp>
#include <sge/sprite/repetition_type.hpp>
#include <sge/sprite/object.hpp>
#include <sge/texture/part_fwd.hpp>

namespace sge
{
namespace sprite
{
class parameters
{
	public:
	parameters();

	parameters &pos(point const &);
	parameters &texture(texture::const_part_ptr);
	parameters &size(dim const &);
	parameters &color(sge::sprite::color const &);
	parameters &depth(depth_type);
	parameters &rotation(rotation_type);
	parameters &visible(bool);

	operator sge::sprite::object() const;
	private:
	point pos_;
	texture::const_part_ptr texture_;
	dim size_;
	sge::sprite::color color_;
	depth_type depth_;
	rotation_type rotation_;
	bool visible_;
};
}
}

#endif
