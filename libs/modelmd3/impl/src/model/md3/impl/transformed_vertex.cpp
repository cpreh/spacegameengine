//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/model/md3/scalar.hpp>
#include <sge/model/md3/impl/convert_normal.hpp>
#include <sge/model/md3/impl/transformed_vertex.hpp>
#include <sge/model/md3/impl/vec3.hpp>
#include <sge/model/md3/impl/vertex.hpp>
#include <sge/model/md3/impl/xyz_scale.hpp>
#include <fcppt/cast/int_to_float.hpp>


sge::model::md3::impl::transformed_vertex::transformed_vertex(
	sge::model::md3::impl::vertex const &_vertex
)
:
	pos_(
		// TODO(philipp): Don't do this element-wise
		fcppt::cast::int_to_float<
			sge::model::md3::scalar
		>(
			_vertex.x()
		)
		*
		sge::model::md3::impl::xyz_scale()
		,
		fcppt::cast::int_to_float<
			sge::model::md3::scalar
		>(
			_vertex.y()
		)
		*
		sge::model::md3::impl::xyz_scale()
		,
		fcppt::cast::int_to_float<
			sge::model::md3::scalar
		>(
			_vertex.z()
		)
		*
		sge::model::md3::impl::xyz_scale()
	),
	normal_(
		sge::model::md3::impl::convert_normal(
			_vertex.normal()
		)
	)
{
}

sge::model::md3::impl::vec3 const &
sge::model::md3::impl::transformed_vertex::pos() const
{
	return
		pos_;
}

sge::model::md3::impl::vec3 const &
sge::model::md3::impl::transformed_vertex::normal() const
{
	return
		normal_;
}
