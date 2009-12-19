/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../transform.hpp"
#include <sge/variant/object_impl.hpp>
#include <sge/variant/apply_unary.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/spirit/home/phoenix/object/static_cast.hpp>
#include <algorithm>

namespace
{

struct visitor {
	typedef D3DMATRIX result_type;

	template<
		typename T
	>
	result_type const
	operator()(
		T const &) const;
};

D3DMATRIX const
convert_matrix(
	sge::renderer::any_matrix const &m)
{
	return sge::variant::apply_unary(
		visitor(),
		m
	);
}

}

void
sge::d3d9::set_transform(
	d3d_device_ptr const device,
	D3DTRANSFORMSTATETYPE const type,
	sge::renderer::any_matrix const &m)
{
	D3DMATRIX const d3d_matrix(
		convert_matrix(
			m
		)
	);

	if(
		device->SetTransform(
			type,
			&d3d_matrix
		) != D3D_OK
	)
		throw exception(
			SGE_TEXT("SetTransform() failed!")
		);
}

namespace
{

template<
	typename T
>
visitor::result_type const
visitor::operator()(
	T const &m) const
{
	result_type res;

	std::transform(
		m.data(),
		m.data_end(),
		res.m,
		boost::phoenix::static_cast_<
			float
		>()
	);

	return res;
}

}
