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


#include "../../image/convert_dim.hpp"
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/mpl/invoke_on.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional_impl.hpp>
#include <mizuiro/image/is_raw_view.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>
#include <cstddef>

namespace
{

class operation
{
	FCPPT_NONASSIGNABLE(
		operation
	)
public:
	typedef sge::image2d::view::object result_type;

	operation(
		sge::image::raw_pointer,
		sge::image2d::dim const &,
		sge::image2d::view::optional_pitch const &
	);

	template<
		typename View
	>
	sge::image2d::view::object const
	operator()() const;
private:
	sge::image::raw_pointer const data_;

	sge::image2d::dim const dim_;

	sge::image2d::view::optional_pitch const pitch_;
};

}

sge::image2d::view::object const
sge::image2d::view::make(
	image::raw_pointer const _data,
	image2d::dim const &_dim,
	image::color::format::type const _format,
	image2d::view::optional_pitch const _pitch
)
{

	// TODO: gcc-4.5: Check if this is a gcc bug

	return
		fcppt::mpl::invoke_on<
			boost::mpl::filter_view<
				view::elements,
				boost::mpl::bind<
					boost::mpl::quote1<
						mizuiro::image::is_raw_view
					>,
					boost::mpl::_1
				>
			>
		>(
			static_cast<
				image::size_type
			>(
				_format
			),
			::operation(
				_data,
				_dim,
				_pitch
			)
		);
}

sge::image2d::view::const_object const
sge::image2d::view::make(
	image::const_raw_pointer const _data,
	image2d::dim const &_dim,
	image::color::format::type const _format,
	image2d::view::optional_pitch const _pitch
)
{
	return
		view::make_const(
			view::make(
				const_cast<
					image::raw_pointer
				>(
					_data
				),
				_dim,
				_format,
				_pitch
			)
		);
}

namespace
{

operation::operation(
	sge::image::raw_pointer const _data,
	sge::image2d::dim const &_dim,
	sge::image2d::view::optional_pitch const &_pitch
)
:
	data_(_data),
	dim_(_dim),
	pitch_(_pitch)
{}

template<
	typename View
>
sge::image2d::view::object const
operation::operator()() const
{
	return
		sge::image2d::view::object(
			View(
				sge::image::convert_dim<
					typename View::dim_type
				>(
					dim_
				),
				data_,
				static_cast<
					typename View::pitch_type
				>(
					pitch_
					?
						static_cast<
							std::ptrdiff_t
						>(
							*pitch_
						)
					:
						static_cast<
							std::ptrdiff_t
						>(
							0
						)
				)
			)
		);
}

}
