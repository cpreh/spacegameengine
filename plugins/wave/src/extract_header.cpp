//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/wave/extract_header.hpp>
#include <sge/wave/header.hpp>
#include <sge/wave/optional_header.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


sge::wave::optional_header
sge::wave::extract_header(
	std::istream &_stream
)
{
	sge::wave::header result{
		fcppt::no_init{}
	};

	_stream.read(
		result.data(),
		result.size()
	);

	return
		_stream.fail()
		?
			sge::wave::optional_header()
		:
			sge::wave::optional_header(
				result
			)
		;
}
