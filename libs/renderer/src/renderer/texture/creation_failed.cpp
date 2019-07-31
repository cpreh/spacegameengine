//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/creation_failed.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::texture::creation_failed::creation_failed(
	fcppt::string &&_string
)
:
	sge::renderer::exception(
		FCPPT_TEXT("texture creation failed: ")
		+
		std::move(
			_string
		)
	)
{
}

sge::renderer::texture::creation_failed::creation_failed(
	creation_failed &&
)
= default;

sge::renderer::texture::creation_failed::creation_failed(
	creation_failed const &
)
= default;

sge::renderer::texture::creation_failed &
sge::renderer::texture::creation_failed::operator=(
	creation_failed &&
)
= default;

sge::renderer::texture::creation_failed &
sge::renderer::texture::creation_failed::operator=(
	creation_failed const &
)
= default;

sge::renderer::texture::creation_failed::~creation_failed() noexcept
{
}
