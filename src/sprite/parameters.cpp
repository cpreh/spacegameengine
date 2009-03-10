#include <sge/sprite/parameters.hpp>
#include <sge/sprite/object.hpp>

sge::sprite::parameters::parameters()
:
	pos_(sprite::defaults::pos_),
	texture_(sprite::defaults::texture_),
	size_(defaults::dim_),
	color_(defaults::color_),
	depth_(defaults::depth_),
	rotation_(defaults::rotation_),
	visible_(defaults::visible_)
{
}

sge::sprite::parameters &sge::sprite::parameters::pos(
	point const &_pos)
{
	pos_ = _pos;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::texture(
	texture::const_part_ptr _texture)
{
	texture_ = _texture;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::size(
	dim const &_size)
{
	size_ = _size;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::color(
	sge::sprite::color const &_color)
{
	color_ = _color;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::depth(
	depth_type const _depth)
{
	depth_ = _depth;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::rotation(
	rotation_type const _rotation)
{
	rotation_ = _rotation;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::visible(
	bool _visible)
{
	visible_ = _visible;
	return *this;
}

sge::sprite::parameters::operator sge::sprite::object() const
{
	return sge::sprite::object(
		pos_,
		texture_,
		size_,
		color_,
		depth_,
		rotation_,
		visible_);
}
