//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image2d/dim.hpp>
#include <sge/libpng/byte_vector.hpp>
#include <sge/libpng/file_rep.hpp>
#include <sge/libpng/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::libpng::file_rep::file_rep(
	sge::image2d::dim const _size,
	sge::libpng::format const _format,
	sge::libpng::byte_vector &&_bytes
)
:
	size_(
		_size
	),
	format_(
		_format
	),
	bytes_(
		std::move(
			_bytes
		)
	)
{
}

sge::libpng::file_rep::file_rep(
	file_rep &&
) = default;

sge::libpng::file_rep &
sge::libpng::file_rep::operator=(
	file_rep &&
) = default;

sge::libpng::file_rep::~file_rep()
{
}

sge::image2d::dim
sge::libpng::file_rep::size() const
{
	return
		size_;
}

sge::libpng::format
sge::libpng::file_rep::format() const
{
	return
		format_;
}

sge::libpng::byte_vector const &
sge::libpng::file_rep::bytes() const
{
	return
		bytes_;
}
