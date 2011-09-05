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


#include "read_string.hpp"
#include "max_qpath.hpp"
#include <sge/model/md3/exception.hpp>
#include <sge/model/md3/string.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <istream>
#include <fcppt/config/external_end.hpp>

template<
	sge::model::md3::string::size_type Max
>
sge::model::md3::string const
sge::model::md3::read_string(
	std::istream &_stream
)
{
	fcppt::container::array<
		md3::string::value_type,
		Max
	> tmp_name;

	_stream.read(
		reinterpret_cast<
			char *
		>(
			tmp_name.data()
		),
		static_cast<
			std::streamsize
		>(
			tmp_name.size()
		)
	);

	if(
		!std::count(
			tmp_name.begin(),
			tmp_name.end(),
			0
		)
	)
		throw sge::model::md3::exception(
			FCPPT_TEXT("String in md3 file not ended with a 0!")
		);

	return tmp_name.data();
}

#define SGE_MODEL_MD3_INSTANTIATE_READ_STRING(\
	maxc\
)\
template \
sge::model::md3::string const \
sge::model::md3::read_string< \
	maxc\
>( \
	std::istream &\
);

SGE_MODEL_MD3_INSTANTIATE_READ_STRING(
	sge::model::md3::max_qpath::value
)

SGE_MODEL_MD3_INSTANTIATE_READ_STRING(
	16
)
