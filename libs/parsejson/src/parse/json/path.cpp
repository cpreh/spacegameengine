//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::parse::json::path::path(
	sge::charconv::utf8_string &&_first
)
:
	sequence_{
		std::move(
			_first
		)
	}
{
}

sge::parse::json::path::path(
	sequence_type &&_sequence
)
:
	sequence_{
		std::move(
			_sequence
		)
	}
{
}

sge::parse::json::path
sge::parse::json::path::operator/(
	sge::charconv::utf8_string &&_element
) &&
{
	this->sequence_.push_back(
		std::move(
			_element
		)
	);

	return
		std::move(
			*this
		);
}

sge::parse::json::path::sequence_type const &
sge::parse::json::path::get() const
{
	return
		this->sequence_;
}
