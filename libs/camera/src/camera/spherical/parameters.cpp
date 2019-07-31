//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/spherical/acceleration_factor.hpp>
#include <sge/camera/spherical/damping_factor.hpp>
#include <sge/camera/spherical/maximum_radius.hpp>
#include <sge/camera/spherical/minimum_radius.hpp>
#include <sge/camera/spherical/movement_speed.hpp>
#include <sge/camera/spherical/origin.hpp>
#include <sge/camera/spherical/parameters.hpp>
#include <sge/camera/spherical/action/mapping.hpp>
#include <sge/camera/spherical/coordinate_system/azimuth.hpp>
#include <sge/camera/spherical/coordinate_system/inclination.hpp>
#include <sge/camera/spherical/coordinate_system/object.hpp>
#include <sge/camera/spherical/coordinate_system/radius.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


sge::camera::spherical::parameters::parameters(
	sge::camera::spherical::coordinate_system::object const &_coordinate_system,
	sge::camera::spherical::action::mapping const &_action_mapping
)
:
	movement_speed_{
		sge::camera::spherical::coordinate_system::object{
			sge::camera::spherical::coordinate_system::azimuth{
				1.0f
			},
			sge::camera::spherical::coordinate_system::inclination{
				1.0f
			},
			sge::camera::spherical::coordinate_system::radius{
				1.0f
			}
		}
	},
	coordinate_system_{
		_coordinate_system
	},
	action_mapping_{
		_action_mapping
	},
	origin_{
		fcppt::math::vector::null<
			sge::renderer::vector3
		>()
	},
	minimum_radius_{
		0.0f
	},
	maximum_radius_{
		std::numeric_limits<
			sge::renderer::scalar
		>::infinity()
	},
	acceleration_factor_{
		sge::camera::spherical::coordinate_system::object{
			sge::camera::spherical::coordinate_system::azimuth{
				3.0f
			},
			sge::camera::spherical::coordinate_system::inclination{
				3.0f
			},
			sge::camera::spherical::coordinate_system::radius{
				3.0f
			}
		}
	},
	damping_factor_{
		sge::camera::spherical::coordinate_system::object{
			sge::camera::spherical::coordinate_system::azimuth{
				0.0001f
			},
			sge::camera::spherical::coordinate_system::inclination{
				0.0001f
			},
			sge::camera::spherical::coordinate_system::radius{
				0.0001f
			}
		}
	},
	projection_matrix_{}
{
}

sge::camera::spherical::coordinate_system::object const &
sge::camera::spherical::parameters::coordinate_system() const
{
	return
		coordinate_system_;
}

sge::camera::spherical::action::mapping const &
sge::camera::spherical::parameters::action_mapping() const
{
	return
		action_mapping_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::movement_speed(
	sge::camera::spherical::movement_speed const &_movement_speed
)
{
	movement_speed_ =
		_movement_speed;

	return
		*this;
}

sge::camera::spherical::movement_speed const &
sge::camera::spherical::parameters::movement_speed() const
{
	return
		movement_speed_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::origin(
	sge::camera::spherical::origin const &_origin
)
{
	origin_ =
		_origin;

	return
		*this;
}

sge::camera::spherical::origin const &
sge::camera::spherical::parameters::origin() const
{
	return
		origin_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::minimum_radius(
	sge::camera::spherical::minimum_radius const _minimum_radius
)
{
	minimum_radius_ =
		_minimum_radius;

	return
		*this;
}

sge::camera::spherical::minimum_radius
sge::camera::spherical::parameters::minimum_radius() const
{
	return
		minimum_radius_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::maximum_radius(
	sge::camera::spherical::maximum_radius const _maximum_radius
)
{
	maximum_radius_ =
		_maximum_radius;

	return
		*this;
}

sge::camera::spherical::maximum_radius
sge::camera::spherical::parameters::maximum_radius() const
{
	return
		maximum_radius_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::acceleration_factor(
	sge::camera::spherical::acceleration_factor const &_acceleration_factor
)
{
	acceleration_factor_ =
		_acceleration_factor;

	return
		*this;
}

sge::camera::spherical::acceleration_factor const &
sge::camera::spherical::parameters::acceleration_factor() const
{
	return
		acceleration_factor_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::damping_factor(
	sge::camera::spherical::damping_factor const &_damping_factor
)
{
	damping_factor_ =
		_damping_factor;

	return
		*this;
}

sge::camera::spherical::damping_factor const &
sge::camera::spherical::parameters::damping_factor() const
{
	return
		damping_factor_;
}

sge::camera::spherical::parameters &
sge::camera::spherical::parameters::projection(
	sge::camera::projection_matrix const &_projection_matrix
)
{
	projection_matrix_ =
		sge::camera::optional_projection_matrix(
			_projection_matrix
		);

	return
		*this;
}

sge::camera::optional_projection_matrix const &
sge::camera::spherical::parameters::projection_matrix() const
{
	return
		projection_matrix_;
}
