//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/media/const_raw_range.hpp>
#include <sge/media/impl/raw_streambuf.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


sge::media::impl::raw_streambuf::raw_streambuf(
	sge::media::const_raw_range const &_range
)
:
	std::streambuf()
{
	auto const convert(
		[](
			sge::media::const_raw_pointer const _ptr
		)
		-> char_type *
		{
			// The streambuf should never write to
			// this unless pbackfail has
			// non-default behavior
			return
				const_cast<
					char_type *
				>(
					fcppt::cast::to_char_ptr<
						char_type const *
					>(
						_ptr
					)
				);
		}
	);

	char_type *const beg(
		convert(
			_range.begin()
		)
	);

	char_type *const end(
		convert(
			_range.end()
		)
	);

	this->setg(
		beg,
		beg,
		end
	);
}

sge::media::impl::raw_streambuf::~raw_streambuf()
{
}
