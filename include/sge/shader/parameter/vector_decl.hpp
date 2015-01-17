/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SHADER_PARAMETER_VECTOR_DECL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_VECTOR_DECL_HPP_INCLUDED

#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/shader/parameter/name.hpp>
#include <sge/shader/parameter/vector_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sge
{
namespace shader
{
namespace parameter
{
template
<
	typename ValueType,
	fcppt::math::size_type N
>
class vector
{
FCPPT_NONCOPYABLE(
	vector);
public:
	typedef
	ValueType
	value_type;

	typedef
	fcppt::math::vector::static_<ValueType,N>
	vector_type;

	static fcppt::math::size_type const size =
		N;

	vector(
		sge::cg::program::object &,
		sge::shader::parameter::name const &,
		vector_type const &);

	void
	set(
		vector_type const &);

	~vector();
private:
	sge::cg::parameter::named const parameter_;
};
}
}
}

#endif
