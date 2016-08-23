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


#include <sge/model/md3/exception.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/impl/max_qpath.hpp>
#include <sge/model/md3/impl/read_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <array>
#include <ios>
#include <istream>
#include <fcppt/config/external_end.hpp>


template<
	sge::model::md3::string::size_type Max
>
sge::model::md3::string
sge::model::md3::impl::read_string(
	std::istream &_stream
)
{
	std::array<
		sge::model::md3::string::value_type,
		Max
	> tmp_name;

	if(
		!_stream.read(
			fcppt::cast::to_char_ptr<
				char *
			>(
				tmp_name.data()
			),
			fcppt::cast::size<
				std::streamsize
			>(
				fcppt::cast::to_signed(
					tmp_name.size()
				)
			)
		)
	)
		throw
			sge::model::md3::exception(
				FCPPT_TEXT("Reading a string failed")
			);

	if(
		!std::count(
			tmp_name.begin(),
			tmp_name.end(),
			0
		)
	)
		throw
			sge::model::md3::exception(
				FCPPT_TEXT("String in md3 file not ended with a 0!")
			);

	return
		tmp_name.data();
}

#define SGE_MODEL_MD3_INSTANTIATE_READ_STRING(\
	maxc\
)\
template \
sge::model::md3::string \
sge::model::md3::impl::read_string< \
	maxc\
>( \
	std::istream &\
);

SGE_MODEL_MD3_INSTANTIATE_READ_STRING(
	sge::model::md3::impl::max_qpath::value
)

SGE_MODEL_MD3_INSTANTIATE_READ_STRING(
	16
)
