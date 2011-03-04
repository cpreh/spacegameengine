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


#ifndef SGE_AUDIO_LOADER_HPP_INCLUDED
#define SGE_AUDIO_LOADER_HPP_INCLUDED

#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/file_ptr.hpp>
#include <sge/audio/loader_capabilities_field.hpp>
#include <sge/class_symbol.hpp>
#include <sge/const_raw_range.hpp>
#include <sge/extension_set.hpp>
#include <sge/optional_extension.hpp>
#include <sge/symbol.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace audio
{

class SGE_CLASS_SYMBOL loader
{
	FCPPT_NONCOPYABLE(
		loader
	);
protected:
	SGE_SYMBOL loader();
public:
	virtual file_ptr const
	load(
		fcppt::filesystem::path const &
	) = 0;

	virtual audio::file_ptr const
	load(
		sge::const_raw_range const &,
		sge::optional_extension const &
	) = 0;

	virtual loader_capabilities_field const
	capabilities() const = 0;

	virtual extension_set const
	extensions() const = 0;
	
	SGE_SYMBOL virtual ~loader();
};

}
}

#endif
