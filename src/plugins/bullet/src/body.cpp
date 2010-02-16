#include "../body.hpp"
#include "../convert/to_bullet.hpp"
#include "../world.hpp"
#include "../shapes/base.hpp"
#include "../log.hpp"
#include <sge/exception.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <boost/foreach.hpp>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("body")));
}

sge::bullet::body::body(
	world &_world,
	collision::shapes::container const &_shapes,
	point const &_position,
	point const &_linear_velocity)
:
	world_(
		_world),
	shapes_(), // <-- we push the shapes in the foreach below
	position_(
		_position),
	linear_velocity_(
		_linear_velocity),
	solid_shapes_(
		0)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("In constructor, now adding shapes to body"));
		
	BOOST_FOREACH(collision::shapes::container::const_reference r,_shapes)
		add_shape(
			r);
			
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Shapes added, now setting position ")
			<< position_
			<< FCPPT_TEXT(" and velocity ")
			<< linear_velocity_);
}

sge::collision::point const 
sge::bullet::body::position() const
{
	return 
		fcppt::math::vector::structure_cast<collision::point>(
			position_);
}

void 
sge::bullet::body::position(
	collision::point const &p)
{
	position_ = 
		fcppt::math::vector::structure_cast<point>(
			p);
			
	BOOST_FOREACH(shape_container::reference r,shapes_)
		r->meta_body_position(
			position_);
}

void 
sge::bullet::body::position_changed(
	collision::point const &_position)
{
	position_ = 
		fcppt::math::vector::structure_cast<point>(
			_position);
}
	
sge::collision::point const 
sge::bullet::body::linear_velocity() const
{
	return
		fcppt::math::vector::structure_cast<collision::point>(
			linear_velocity_);
}

void 
sge::bullet::body::linear_velocity(
	collision::point const &_linear_velocity)
{
	linear_velocity_ = 
		fcppt::math::vector::structure_cast<collision::point>(
			_linear_velocity);
	
	BOOST_FOREACH(shape_container::reference r,shapes_)
		r->linear_velocity(
			linear_velocity_);
}

void
sge::bullet::body::add_shape(
	collision::shapes::base_ptr _shape)
{
	shapes_.push_back(
		fcppt::dynamic_pointer_cast<shapes::base,collision::shapes::base>(
			_shape));
			
	shapes_.back()->meta_body(
		*this);

	// If this shape is not solid _but_ there are no solid shapes and no nonsolids yet, then
	// this shape will be the position changer (since it's the best choice)
	if(
	  !shapes_.back()->is_solid())
	{
		if(
		    !solid_shapes_ && 
		    shapes_.size() == static_cast<shape_container::size_type>(1))
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_ << FCPPT_TEXT("Setting position changer"));

			shapes_.back()->is_position_changer(
				true);

		}
		else
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_ << FCPPT_TEXT("NOT Setting position changer"));
		}
		return;
	}
	
	if (solid_shapes_)
		throw 
			exception(
				FCPPT_TEXT("You can only have one solid shape per body (else there will be ambiguities with solid/solid collisions"));
				
	++solid_shapes_;
	
	shapes_.back()->is_position_changer(
		true);
}

void
sge::bullet::body::remove_shape(
	shapes::base &s)
{
	for(
		shape_container::iterator i = shapes_.begin();
		i != shapes_.end();
		++i)
	{
		if (i->get() == &s)
		{
			bool const pc = 
				s.is_position_changer();
			shapes_.erase(
				i);
			// Assign a new position changer if there are shapes left
			if (pc && !shapes_.empty())
				shapes_.front()->is_position_changer(
					true);
			return;
		}
	}
	FCPPT_ASSERT_MESSAGE(
		false,
		FCPPT_TEXT("A shape had to be detached from the body, but the body didn't contain the shape. o_O"));
}

sge::bullet::body::~body()
{
	// this doesn't work, the shapes have to be created before the body
	// because the body gets them in the constructor
	/*
	FCPPT_ASSERT_MESSAGE(
		shapes_.empty(),
		FCPPT_TEXT("You tried to delete a body before all of the assigned shapes were destroyed"));
		*/
}
