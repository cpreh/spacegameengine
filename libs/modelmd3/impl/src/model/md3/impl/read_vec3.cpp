//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/model/md3/scalar.hpp>
#include <sge/model/md3/impl/read_scalar.hpp>
#include <sge/model/md3/impl/read_vec3.hpp>
#include <sge/model/md3/impl/vec3.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::model::md3::impl::vec3
sge::model::md3::impl::read_vec3(
	std::istream &_stream
)
{
	sge::model::md3::scalar const x{
		sge::model::md3::impl::read_scalar(
			_stream
		)
	};

	sge::model::md3::scalar const y{
		sge::model::md3::impl::read_scalar(
			_stream
		)
	};

	sge::model::md3::scalar const z{
		sge::model::md3::impl::read_scalar(
			_stream
		)
	};

	return
		sge::model::md3::impl::vec3(
			x,
			y,
			z
		);
}
