/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_MEDIA_MUXER_IMPL_HPP_INCLUDED
#define SGE_SRC_MEDIA_MUXER_IMPL_HPP_INCLUDED

#include <sge/media/extension_set.hpp>
#include <sge/media/muxer.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/src/media/detail/muxer_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename System,
	typename File,
	typename Capabilities
>
sge::media::muxer<
	System,
	File,
	Capabilities
>::muxer(
	parameters const &_parameters
)
:
	impl_(
		fcppt::make_unique_ptr<
			muxer_impl
		>(
			_parameters
		)
	)
{
}

template<
	typename System,
	typename File,
	typename Capabilities
>
sge::media::muxer<
	System,
	File,
	Capabilities
>::~muxer()
{
}

template<
	typename System,
	typename File,
	typename Capabilities
>
typename sge::media::muxer<
	System,
	File,
	Capabilities
>::file_unique_ptr
sge::media::muxer<
	System,
	File,
	Capabilities
>::mux_path(
	boost::filesystem::path const &_file,
	load_function const &_function
) const
{
	return
		impl_->mux_path(
			_file,
			_function
		);
}

template<
	typename System,
	typename File,
	typename Capabilities
>
typename sge::media::muxer<
	System,
	File,
	Capabilities
>::file_unique_ptr
sge::media::muxer<
	System,
	File,
	Capabilities
>::mux_extension(
	sge::media::optional_extension const &_extension,
	load_function const &_function
) const
{
	return
		impl_->mux_extension(
			_extension,
			_function
		);
}

template<
	typename System,
	typename File,
	typename Capabilities
>
typename sge::media::muxer<
	System,
	File,
	Capabilities
>::capabilities_field const
sge::media::muxer<
	System,
	File,
	Capabilities
>::capabilities() const
{
	return
		impl_->capabilities();
}

template<
	typename System,
	typename File,
	typename Capabilities
>
sge::media::extension_set
sge::media::muxer<
	System,
	File,
	Capabilities
>::extensions() const
{
	return
		impl_->extensions();
}

#endif
