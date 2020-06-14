//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/model/md3/scalar.hpp>
#include <sge/model/md3/impl/convert_normal.hpp>
#include <sge/model/md3/impl/s16.hpp>
#include <sge/model/md3/impl/vec3.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sge::model::md3::impl::vec3
sge::model::md3::impl::convert_normal(
	sge::model::md3::impl::s16 const _normal
)
{
	sge::model::md3::scalar const lat(
		fcppt::cast::int_to_float<
			sge::model::md3::scalar
		>(
			(_normal >> 8) // NOLINT(hicpp-signed-bitwise)
			& 255 // NOLINT(hicpp-signed-bitwise)
		)
		*
		fcppt::math::twopi<
			sge::model::md3::scalar
		>()
		/ 255
	);

	sge::model::md3::scalar const lng(
		fcppt::cast::int_to_float<
			sge::model::md3::scalar
		>(
			_normal & 255 // NOLINT(hicpp-signed-bitwise)
		)
		*
		fcppt::math::twopi<
			sge::model::md3::scalar
		>()
		/ 255
	);

	return
		sge::model::md3::impl::vec3(
			std::cos(lat) * std::sin(lng),
			std::sin(lat) * std::sin(lng),
			std::cos(lng)
		);
}
