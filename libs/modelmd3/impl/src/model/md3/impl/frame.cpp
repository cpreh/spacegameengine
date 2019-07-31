//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/model/md3/impl/frame.hpp>
#include <sge/model/md3/impl/read_scalar.hpp>
#include <sge/model/md3/impl/read_string.hpp>
#include <sge/model/md3/impl/read_vec3.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::model::md3::impl::frame::frame(
	std::istream &_stream
)
:
	min_bounds_(
		sge::model::md3::impl::read_vec3(
			_stream
		)
	),
	max_bounds_(
		sge::model::md3::impl::read_vec3(
			_stream
		)
	),
	local_origin_(
		sge::model::md3::impl::read_vec3(
			_stream
		)
	),
	radius_(
		sge::model::md3::impl::read_scalar(
			_stream
		)
	),
	name_(
		sge::model::md3::impl::read_string<
			16
		>(
			_stream
		)
	)
{
}
