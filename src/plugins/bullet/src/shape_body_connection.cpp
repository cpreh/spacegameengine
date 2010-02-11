#include "../shape_body_connection.hpp"
#include "../shapes/base.hpp"
#include "../body.hpp"
#include "../convert/to_bullet.hpp"

sge::bullet::shape_body_connection::shape_body_connection(
	shapes::base &_shape,
	sge::bullet::body &_body)
:
	shape_(
		_shape),
	body_(
		_body)
{
	// NOTE: This doesn't call shape_.meta_body(_body); because that's what bullet::body::add_shape should do
}

sge::bullet::body &
sge::bullet::shape_body_connection::body() const
{
	return 
		body_;
}
	
sge::bullet::shape_body_connection::~shape_body_connection()
{
	body_.remove_shape(
		shape_);
}