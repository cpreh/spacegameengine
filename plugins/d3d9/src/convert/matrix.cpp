//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/matrix.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>


D3DMATRIX
sge::d3d9::convert::matrix(
	sge::renderer::matrix4 const &_matrix
)
{
	D3DMATRIX ret;

	std::memcpy(
		ret.m[0],
		_matrix.storage().data(),
		sizeof(
			sge::renderer::matrix4::value_type
		)
		*
		sge::renderer::matrix4::storage_type::storage_size::value
	);

	return
		ret;
}
