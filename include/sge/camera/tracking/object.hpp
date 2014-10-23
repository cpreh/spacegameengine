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


#ifndef SGE_CAMERA_TRACKING_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_OBJECT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/camera/base.hpp>
#include <sge/camera/has_activation.hpp>
#include <sge/camera/has_mutable_coordinate_system.hpp>
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/tracking/is_looping.hpp>
#include <sge/camera/tracking/keyframe_sequence.hpp>
#include <fcppt/cyclic_iterator.hpp>
#include <fcppt/optional.hpp>


namespace sge
{
namespace camera
{
namespace tracking
{
class SGE_CORE_DETAIL_CLASS_SYMBOL object
:
	public virtual sge::camera::base,
	public sge::camera::has_activation,
	public sge::camera::is_dynamic,
	public sge::camera::has_mutable_projection
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	object(
		sge::camera::optional_projection_matrix const &,
		sge::camera::tracking::keyframe_sequence const &,
		sge::camera::tracking::is_looping const &,
		sge::camera::is_active const &);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::coordinate_system::object const
	coordinate_system() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::projection_matrix const
	projection_matrix() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	update_projection_matrix(
		sge::camera::projection_matrix const &
	)
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::is_active const
	is_active() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	is_active(
		sge::camera::is_active const &
	)
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	update(
		sge::camera::update_duration const &
	)
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	bool
	finished() const;

	SGE_CAMERA_DETAIL_SYMBOL
	~object()
	override;
private:
	typedef
	fcppt::cyclic_iterator
	<
		sge::camera::tracking::keyframe_sequence::const_iterator
	>
	cyclic_iterator;

	sge::camera::optional_projection_matrix projection_matrix_;
	sge::camera::tracking::keyframe_sequence const keyframes_;
	sge::camera::tracking::is_looping const is_looping_;
	cyclic_iterator current_keyframe_;
	sge::camera::update_duration current_time_point_;
	sge::camera::is_active is_active_;
	sge::camera::coordinate_system::object coordinate_system_;
	bool finished_;
};
}
}
}

#endif
