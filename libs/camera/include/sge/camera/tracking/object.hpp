//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_TRACKING_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_OBJECT_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/tracking/is_looping.hpp>
#include <sge/camera/tracking/keyframe_sequence.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <fcppt/cyclic_iterator_decl.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace camera
{
namespace tracking
{

// NOLINTNEXTLINE(fuchsia-multiple-inheritance)
class SGE_CORE_DETAIL_CLASS_SYMBOL object
:
	public virtual sge::camera::base,
	public sge::camera::is_dynamic,
	public sge::camera::has_mutable_projection
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	object(
		sge::camera::optional_projection_matrix,
		sge::camera::tracking::keyframe_sequence &&,
		sge::camera::tracking::is_looping
	);

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::coordinate_system::object
	coordinate_system() const
	override;

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::optional_projection_matrix
	projection_matrix() const
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	update_projection_matrix(
		sge::camera::optional_projection_matrix const &
	)
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	update(
		sge::camera::update_duration
	)
	override;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	process_event(
		sge::input::event_base const &
	)
	override;

	[[nodiscard]]
	SGE_CAMERA_DETAIL_SYMBOL
	bool
	finished() const;

	SGE_CAMERA_DETAIL_SYMBOL
	~object()
	override;
private:
	using
	cyclic_iterator
	=
	fcppt::cyclic_iterator<
		sge::camera::tracking::keyframe_sequence::const_iterator
	>;

	sge::camera::optional_projection_matrix projection_matrix_;

	sge::camera::tracking::keyframe_sequence const keyframes_;

	sge::camera::tracking::is_looping const is_looping_;

	cyclic_iterator current_keyframe_;

	sge::camera::update_duration current_time_point_;

	sge::camera::coordinate_system::object coordinate_system_;

	bool finished_;
};

}
}
}

#endif
