/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SHADER_PARAMETER_SCALAR_DECL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_SCALAR_DECL_HPP_INCLUDED

#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/shader/parameter/name.hpp>
#include <sge/shader/parameter/scalar_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace shader
{
namespace parameter
{
template<typename ValueType>
class scalar
{
FCPPT_NONCOPYABLE(
	scalar);
public:
	typedef
	ValueType
	value_type;

	scalar(
		sge::cg::program::object &,
		sge::shader::parameter::name const &,
		value_type);

	void
	set(
		value_type);

	~scalar();
private:
	sge::cg::parameter::named const parameter_;
};
}
}
}

#endif
