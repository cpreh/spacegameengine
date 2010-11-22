#include <sge/camera/projection/to_matrix.hpp>
#include <sge/renderer/scalar.hpp>
#include <fcppt/math/matrix/orthogonal_xy.hpp>
#include <fcppt/math/matrix/perspective.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/variant/apply_unary.hpp>

namespace
{
class conversion_operator
{
public:
	typedef 
	sge::renderer::matrix4 
	result_type;

	sge::renderer::matrix4 const
	operator()(sge::camera::projection::orthogonal const &) const
	{
		return fcppt::math::matrix::orthogonal_xy<sge::renderer::scalar>();
	}

	sge::renderer::matrix4 const
	operator()(sge::camera::projection::perspective const &o) const
	{
		return 
			fcppt::math::matrix::perspective(
				o.aspect(),
				o.fov(),
				o.near(),
				o.far());
	}
};
}

sge::renderer::matrix4 const
sge::camera::projection::to_matrix(
	object const &o)
{
	return 
		fcppt::variant::apply_unary(
			conversion_operator(),
			o);
}
