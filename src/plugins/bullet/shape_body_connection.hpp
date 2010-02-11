#ifndef SGE_BULLET_SHAPE_BODY_CONNECTION_HPP_INCLUDED
#define SGE_BULLET_SHAPE_BODY_CONNECTION_HPP_INCLUDED

#include "shapes/base_fwd.hpp"
#include "body_fwd.hpp"

namespace sge
{
namespace bullet
{
class shape_body_connection
{
public:
	explicit
	shape_body_connection(
		shapes::base &,
		body &);
	
	sge::bullet::body &
	body() const;
	
	~shape_body_connection();
private:
	shapes::base &shape_;
	sge::bullet::body &body_;
};
}
}

#endif