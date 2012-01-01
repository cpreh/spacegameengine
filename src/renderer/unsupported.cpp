/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/renderer/unsupported.hpp>
#include <fcppt/text.hpp>


sge::renderer::unsupported::unsupported(
	fcppt::string const &_feature,
	fcppt::string const &_minimum_version_required,
	fcppt::string const &_possible_extensions
)
:
	renderer::exception(
		FCPPT_TEXT("Unsupported feature \"")
		+ _feature
		+ FCPPT_TEXT("\". Minimum required version is \"")
		+ _minimum_version_required
		+ FCPPT_TEXT("\". Possible extensions are \"")
		+ _possible_extensions
		+ FCPPT_TEXT("\"!")
	),
	feature_(_feature),
	minimum_version_required_(_minimum_version_required),
	possible_extensions_(_possible_extensions)
{}

fcppt::string const &
sge::renderer::unsupported::feature() const
{
	return feature_;
}

fcppt::string const &
sge::renderer::unsupported::minimum_version_required() const
{
	return minimum_version_required_;
}

fcppt::string const &
sge::renderer::unsupported::possible_extensions() const
{
	return possible_extensions_;
}

sge::renderer::unsupported::~unsupported() throw()
{
}
