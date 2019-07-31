//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/exception.hpp>
#include <sge/texture/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::texture::exception::exception(
	fcppt::string &&_what
)
:
	sge::core::exception(
		FCPPT_TEXT("texture: ")
		+
		std::move(
			_what
		)
	)
{
}

sge::texture::exception::exception(
	exception &&
)
= default;

sge::texture::exception::exception(
	exception const &
)
= default;

sge::texture::exception &
sge::texture::exception::operator=(
	exception &&
)
= default;

sge::texture::exception &
sge::texture::exception::operator=(
	exception const &
)
= default;

sge::texture::exception::~exception() noexcept
{
}
