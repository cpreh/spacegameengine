/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_OBJECT_DECL_HPP_INCLUDED
#define SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_OBJECT_DECL_HPP_INCLUDED

#include <sge/scenic/impl/number_multiplexer/object_fwd.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
namespace impl
{
namespace number_multiplexer
{
template<typename T>
class object
{
static_assert(
	std::is_unsigned<T>::value,
	"number_multiplexer only works on unsigned types");
public:
	typedef
	T
	value_type;

	FCPPT_MAKE_STRONG_TYPEDEF(
		value_type,
		bit_count);

	object();

	explicit
	object(
		value_type);

	object &
	append(
		bit_count const &,
		value_type);

	value_type
	value() const;
private:
	value_type value_;
	value_type last_bit_set_;
};
}
}
}
}

#endif
