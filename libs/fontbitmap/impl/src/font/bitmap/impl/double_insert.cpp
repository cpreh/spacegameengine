//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/char_type.hpp>
#include <sge/font/exception.hpp>
#include <sge/font/string.hpp>
#include <sge/font/to_fcppt_string.hpp>
#include <sge/font/bitmap/impl/double_insert.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/from.hpp>


sge::font::exception
sge::font::bitmap::impl::double_insert(
	sge::font::char_type const _ch
)
{
	return
		sge::font::exception{
			FCPPT_TEXT("Double insert of '")
			+
			fcppt::optional::from(
				sge::font::to_fcppt_string(
					sge::font::string{
						_ch
					}
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("CONVERSION_FAILURE")
						};
				}
			)
			+
			FCPPT_TEXT(" in bitmap font")
		};
}
