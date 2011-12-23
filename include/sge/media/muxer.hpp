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


#ifndef SGE_MEDIA_MUXER_HPP_INCLUDED
#define SGE_MEDIA_MUXER_HPP_INCLUDED

#include <sge/media/extension_set.hpp>
#include <sge/media/muxer_fwd.hpp>
#include <sge/media/muxer_parameters_fwd.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/plugin/context.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{

template<
	typename System,
	typename Capabilities
>
class muxer
{
	FCPPT_NONCOPYABLE(
		muxer
	);
public:
	typedef System system;

	typedef Capabilities capabilities_field;

	typedef fcppt::shared_ptr<
		System
	> system_ptr;

	typedef media::muxer_parameters<
		capabilities_field
	> parameters;

	explicit muxer(
		parameters const &
	);

	~muxer();

	system &
	mux_path(
		fcppt::filesystem::path const &
	) const;

	system &
	mux_extension(
		media::optional_extension const &
	) const;

	capabilities_field const
	capabilities() const;

	sge::media::extension_set const
	extensions() const;
private:
	typedef std::vector<
		system_ptr
	> system_container;

	typedef typename plugin::context<
		system
	>::ptr_type plugin_ptr;

	typedef std::vector<
		plugin_ptr
	> plugin_container;

	plugin_container plugins_;

	system_container systems_;

	capabilities_field capabilities_;

	sge::media::extension_set extensions_;
};

}
}

#endif
