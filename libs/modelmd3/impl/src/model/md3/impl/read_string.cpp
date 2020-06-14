//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
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
	{
		throw
			sge::model::md3::exception(
				FCPPT_TEXT("Reading a string failed")
			);
	}

	if(
		!std::count(
			tmp_name.begin(),
			tmp_name.end(),
			0
		)
	)
	{
		throw
			sge::model::md3::exception(
				FCPPT_TEXT("String in md3 file not ended with a 0!")
			);
	}

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
)

SGE_MODEL_MD3_INSTANTIATE_READ_STRING(
	sge::model::md3::impl::max_qpath::value
);

SGE_MODEL_MD3_INSTANTIATE_READ_STRING(
	16
);
