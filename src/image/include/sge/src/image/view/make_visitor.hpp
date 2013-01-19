/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_IMAGE_VIEW_MAKE_VISITOR_HPP_INCLUDED
#define SGE_SRC_IMAGE_VIEW_MAKE_VISITOR_HPP_INCLUDED

#include <sge/image/dim.hpp>
#include <sge/image/pitch.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/src/image/convert_dim.hpp>
#include <fcppt/nonassignable.hpp>


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
		data_(
			_data
		),
		dim_(
			_dim
		),
		pitch_(
			_pitch
		)
	{
	}

	make_visitor(
		make_visitor const &_other
	)
	:
		data_(
			_other.data
		),
		dim_(
			_other.dim
		),
		pitch_(
			_other.pitch
		)
	{
	}

	~make_visitor()
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
						typename View::dim
					>(
						dim_
					),
					data_,
					sge::image::convert_dim<
						typename View::pitch_type
					>(
						pitch_
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
