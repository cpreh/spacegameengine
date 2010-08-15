/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/index/dynamic/copy.hpp>
#include <sge/exception.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/less_equal.hpp>
#include <algorithm>

namespace
{

template<
	typename Src,
	typename Dest
>
struct is_compatible
:
boost::mpl::less_equal<
	boost::mpl::sizeof_<
		typename boost::remove_const<
			typename Src::format_type::type
		>::type
	>,
	boost::mpl::sizeof_<
		typename Dest::format_type::type
	>
>
{};

class copy_visitor
{
public:
	typedef void result_type;

	template<
		typename T,
		typename U
	>
	typename boost::enable_if<
		is_compatible<
			T,
			U
		>,
		result_type
	>::type
	operator()(
		T const &src,
		U const &dest
	) const
	{
		std::copy(
			src.begin(),
			src.end(),
			dest.begin()
		);
	}

	template<
		typename T,
		typename U
	>
	typename boost::disable_if<
		is_compatible<
			T,
			U
		>,
		result_type
	>::type
	operator()(
		T,
		U
	) const
	{
		throw sge::exception(
			FCPPT_TEXT("Incompatible index::dynamic::views in index::dynamic::copy!")
		);
	}
};

}

void
sge::renderer::index::dynamic::copy(
	const_view const &src,
	view const &dest
)
{
	fcppt::variant::apply_binary(
		copy_visitor(),
		src.any(),
		dest.any()
	);
}
