/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/matrix_conversion/world_matrix_to_coordinate_system.hpp>
#include <sge/camera/tracking/object.hpp>
#include <sge/camera/tracking/alexa/lerp.hpp>
#include <sge/src/camera/logger.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/math/matrix/output.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/structure_cast.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{
sge::renderer::matrix4 const
lerp_double(
	sge::renderer::scalar const _t,
	sge::renderer::matrix4 const &_a,
	sge::renderer::matrix4 const &_b)
{
	typedef
	long double
	real;

	typedef
	fcppt::math::matrix::static_<real,4,4>
	real_matrix;

	return
		fcppt::math::matrix::structure_cast<
			sge::renderer::matrix4,
			fcppt::cast::size_fun
		>(
			sge::camera::tracking::alexa::lerp(
				fcppt::cast::size<
					real
				>(
					_t
				),
				fcppt::math::matrix::structure_cast<
					real_matrix,
					fcppt::cast::size_fun
				>(
					_a
				),
				fcppt::math::matrix::structure_cast<
					real_matrix,
					fcppt::cast::size_fun
				>(
					_b
				)
			)
		);
}
}

sge::camera::tracking::object::object(
	sge::camera::optional_projection_matrix const &_projection_matrix,
	sge::camera::tracking::keyframe_sequence const &_keyframes,
	sge::camera::tracking::is_looping const &_is_looping,
	sge::camera::is_active const &_is_active)
:
	sge::camera::base(),
	projection_matrix_(
		_projection_matrix),
	keyframes_(
		_keyframes),
	is_looping_(
		_is_looping),
	current_keyframe_(
		keyframes_.begin(),
		keyframes_.begin(),
		keyframes_.end()),
	current_time_point_(
		0.0f),
	is_active_(
		_is_active),
	coordinate_system_(
		keyframes_.begin()->coordinate_system()),
	finished_(
		false)
{
	FCPPT_ASSERT_PRE(
		!keyframes_.empty());
}

sge::camera::coordinate_system::object const
sge::camera::tracking::object::coordinate_system() const
{
	return
		coordinate_system_;
}

sge::camera::projection_matrix const
sge::camera::tracking::object::projection_matrix() const
{
	return
		*projection_matrix_;
}

void
sge::camera::tracking::object::update_projection_matrix(
	sge::camera::projection_matrix const &_projection_matrix)
{
	projection_matrix_ =
		sge::camera::optional_projection_matrix(
			_projection_matrix);
}

sge::camera::is_active const
sge::camera::tracking::object::is_active() const
{
	return
		is_active_;
}

void
sge::camera::tracking::object::is_active(
	sge::camera::is_active const &_is_active)
{
	is_active_ =
		_is_active;
}

void
sge::camera::tracking::object::update(
	sge::camera::update_duration const &_duration)
{
	if(!is_active_.get())
		return;

	current_time_point_ +=
		_duration;

	while(current_time_point_ > current_keyframe_->duration())
	{
		current_time_point_ -=
			current_keyframe_->duration();

		current_keyframe_++;

		if(current_keyframe_.get() == current_keyframe_.begin())
		{
			finished_ =
				true;

			if(!is_looping_.get())
			{
				coordinate_system_ =
					keyframes_.back().coordinate_system();
				return;
			}
		}
	}

	FCPPT_LOG_DEBUG(
		sge::camera::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("Keyframe count: ")
			<< keyframes_.size()
			<< FCPPT_TEXT('\n')
			<< FCPPT_TEXT("Current keyframe index: ")
			<< std::distance(
				keyframes_.begin(),
				current_keyframe_.get())
	);

	sge::renderer::matrix4 const
		left(
			sge::camera::matrix_conversion::world(
				current_keyframe_->coordinate_system())),
		right(
			sge::camera::matrix_conversion::world(
				std::next(
					current_keyframe_)->coordinate_system()));

	coordinate_system_ =
		sge::camera::matrix_conversion::world_matrix_to_coordinate_system(
			lerp_double(
				current_time_point_.count() /
				current_keyframe_->duration().count(),
				sge::renderer::matrix4::identity(),
				right *
				fcppt::math::matrix::inverse(
					left)) *
			left);
}

bool
sge::camera::tracking::object::finished() const
{
	return
		finished_;
}

sge::camera::tracking::object::~object()
{
}
