/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RUCKSACK_AXIS_POLICY_OUTPUT_HPP_INCLUDED
#define SGE_RUCKSACK_AXIS_POLICY_OUTPUT_HPP_INCLUDED

#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace rucksack
{

template<
	typename Ch,
	typename Traits
>
std::basic_ostream<
	Ch,
	Traits
> &
operator<<(
	std::basic_ostream<
		Ch,
		Traits
	> &_stream,
	sge::rucksack::axis_policy const &_policy
)
{
	typedef
	std::basic_ostream<
		Ch,
		Traits
	>
	stream_type;

	class visitor
	{
		FCPPT_NONASSIGNABLE(
			visitor
		);
	public:
		typedef
		stream_type &
		result_type;

		explicit
		visitor(
			stream_type &_nstream
		)
		:
			stream_(
				_nstream
			)
		{
		}

		result_type
		operator()(
			sge::rucksack::minimum_size const _min
		) const
		{
			return
				stream_
					<< stream_.widen('m')
					<< _min;
		}

		result_type
		operator()(
			sge::rucksack::preferred_size const _pref
		) const
		{
			return
				stream_
					<< stream_.widen('p')
					<< _pref;
		}
	private:
		stream_type &stream_;
	};

	return
		fcppt::variant::apply_unary(
			visitor(
				_stream
			),
			_policy
		);
}

}
}

#endif
