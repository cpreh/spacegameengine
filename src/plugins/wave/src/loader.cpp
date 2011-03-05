/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../file.hpp"
#include "../loader.hpp"
#include <sge/extension_set.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

namespace
{

sge::extension_set const extensions_(
	fcppt::assign::make_container<
		sge::extension_set
	>(
		FCPPT_TEXT("wav")
	)
);

}

sge::wave::loader::loader()
{
}

sge::wave::loader::~loader()
{
}

sge::audio::file_ptr const
sge::wave::loader::load(
	fcppt::filesystem::path const &filename
)
{
	return
		fcppt::make_shared_ptr<
			file
		>(
			filename
		);
}

sge::audio::file_ptr const
sge::wave::loader::load(
	sge::const_raw_range const &_range,
	sge::optional_extension const &_extension
)
{
	// TODO:
	return sge::audio::file_ptr();
}

sge::audio::loader_capabilities_field const
sge::wave::loader::capabilities() const
{
	return audio::loader_capabilities_field::null();
}

sge::extension_set const
sge::wave::loader::extensions() const
{
	return extensions_;
}
