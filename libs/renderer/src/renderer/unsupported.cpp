//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


sge::renderer::unsupported::unsupported(
	fcppt::string const &_feature,
	fcppt::string const &_minimum_version_required,
	fcppt::string const &_possible_extensions
)
:
	sge::renderer::exception(
		FCPPT_TEXT("Unsupported feature \"")
		+
		_feature
		+
		FCPPT_TEXT("\". Minimum required version is \"")
		+
		_minimum_version_required
		+
		FCPPT_TEXT("\". Possible extensions are \"")
		+
		_possible_extensions
		+
		FCPPT_TEXT("\"!")
	),
	feature_(
		_feature
	),
	minimum_version_required_(
		_minimum_version_required
	),
	possible_extensions_(
		_possible_extensions
	)
{
}

fcppt::string const &
sge::renderer::unsupported::feature() const
{
	return
		feature_;
}

fcppt::string const &
sge::renderer::unsupported::minimum_version_required() const
{
	return
		minimum_version_required_;
}

fcppt::string const &
sge::renderer::unsupported::possible_extensions() const
{
	return
		possible_extensions_;
}

sge::renderer::unsupported::unsupported(
	unsupported &&
)
= default;

sge::renderer::unsupported::unsupported(
	unsupported const &
)
= default;

sge::renderer::unsupported &
sge::renderer::unsupported::operator=(
	unsupported &&
)
= default;

sge::renderer::unsupported &
sge::renderer::unsupported::operator=(
	unsupported const &
)
= default;

sge::renderer::unsupported::~unsupported() noexcept
{
}
