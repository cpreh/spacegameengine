//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/model/md3/exception.hpp>
#include <sge/model/md3/scalar.hpp>
#include <sge/model/md3/impl/endian.hpp>
#include <sge/model/md3/impl/read_scalar.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::model::md3::scalar
sge::model::md3::impl::read_scalar(
	std::istream &_stream
)
{
	return
		fcppt::optional::to_exception(
			fcppt::io::read<
				sge::model::md3::scalar
			>(
				_stream,
				sge::model::md3::impl::endian()
			),
			[]{
				return
					sge::model::md3::exception{
						FCPPT_TEXT("Failed reading a scalar")
					};
			}
		);
}
