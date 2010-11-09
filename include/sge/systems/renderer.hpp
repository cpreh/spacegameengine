/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_RENDERER_HPP_INCLUDED
#define SGE_SYSTEMS_RENDERER_HPP_INCLUDED

#include <sge/renderer/parameters.hpp>
#include <sge/systems/viewport/factory.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace systems
{

class renderer
{
public:
	SGE_SYMBOL
	renderer(
		sge::renderer::parameters const &,
		systems::viewport::factory const &
	);

	SGE_SYMBOL
	sge::renderer::parameters const &
	parameters() const;

	SGE_SYMBOL
	systems::viewport::factory const &
	viewport_factory() const;
private:
	sge::renderer::parameters parameters_;

	sge::systems::viewport::factory viewport_factory_;
};

}
}

#endif
