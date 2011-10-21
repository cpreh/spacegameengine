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


#include "../supported_extensions.hpp"
#include <sge/extension_set.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>


namespace
{

// FIXME: add more extensions, see: http://openil.sourceforge.net/features.php
sge::extension_set const extensions_(
	fcppt::assign::make_container<
		sge::extension_set
	>
	(
		FCPPT_TEXT("bmp")
	)
	(
		FCPPT_TEXT("png")
	)
	(
		FCPPT_TEXT("jpg")
	)
	(
		FCPPT_TEXT("jpeg")
	)
	(
		FCPPT_TEXT("tga")
	)
);

}

sge::extension_set const
sge::devil::supported_extensions()
{
	return extensions_;
}
