#include <sge/sprite/parameters.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/defaults.hpp>

sge::sprite::parameters::parameters()
:
	pos_(defaults::pos),
	texture_(defaults::texture),
	size_(defaults::size),
	color_(defaults::color),
	depth_(defaults::depth),
	rotation_(defaults::rotation),
	visible_(defaults::visible)
{}

sge::sprite::parameters &sge::sprite::parameters::pos(
	point const &_pos)
{
	pos_ = _pos;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::texture(
	texture::const_part_ptr const _texture)
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
	bool const _visible)
{
	visible_ = _visible;
	return *this;
}

sge::sprite::parameters::operator sge::sprite::object() const
{
	return object(
		pos_,
		texture_,
		size_,
		color_,
		depth_,
		rotation_,
		visible_
	);
}
