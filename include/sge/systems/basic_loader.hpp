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


#ifndef SGE_SYSTEMS_BASIC_LOADER_HPP_INCLUDED
#define SGE_SYSTEMS_BASIC_LOADER_HPP_INCLUDED

#include <sge/media/extension_set.hpp>
#include <sge/systems/basic_loader_fwd.hpp>
#include <sge/systems/symbol.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace systems
{

template<
	typename Capabilities
>
class basic_loader
{
	FCPPT_NONASSIGNABLE(
		basic_loader
	);
public:
	typedef Capabilities capabilities_type;

	SGE_SYSTEMS_SYMBOL
	explicit
	basic_loader(
		capabilities_type const &,
		sge::media::extension_set const &
	);

	SGE_SYSTEMS_SYMBOL
	sge::media::extension_set const &
	extensions() const;

	SGE_SYSTEMS_SYMBOL
	capabilities_type const &
	capabilities() const;
private:
	sge::media::extension_set const extensions_;

	capabilities_type const capabilities_;
};

}
}

#endif
