/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IMAGE_VIEW_MAKE_VISITOR_HPP_INCLUDED
#define SGE_IMAGE_VIEW_MAKE_VISITOR_HPP_INCLUDED

#include "../convert_dim.hpp"
#include <sge/image/raw_pointer.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional_impl.hpp>

namespace sge
{
namespace image
{
namespace view
{

template<
	typename Result,
	typename Dim,
	typename OptionalPitch
>
class make_visitor
{
	FCPPT_NONASSIGNABLE(
		make_visitor
	);
public:
	typedef Result result_type;

	make_visitor(
		sge::image::raw_pointer const _data,
		Dim const &_dim,
		OptionalPitch const &_pitch
	)
	:
		data_(_data),
		dim_(_dim),
		pitch_(_pitch)
	{
	}

	template<
		typename View
	>
	result_type const
	operator()() const
	{
		return
			result_type(
				View(
					sge::image::convert_dim<
						typename View::dim_type
					>(
						dim_
					),
					data_,
					sge::image::convert_dim<
						typename View::pitch_type
					>(
						pitch_
						?
							*pitch_
						:
							OptionalPitch::value_type::null()
					)
				)
			);
	}
private:
	sge::image::raw_pointer const data_;

	Dim const dim_;

	OptionalPitch const pitch_;
};

}
}
}

#endif
