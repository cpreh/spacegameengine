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


#include <sge/opengl/state/deferred/apply.hpp>
#include <sge/opengl/state/deferred/object.hpp>


sge::opengl::state::deferred::object::object(
	deferred::parameters const &_parameters
)
:
	parameters_(_parameters),
	set_()
{
}

sge::opengl::state::deferred::object::~object()
{
}

void
sge::opengl::state::deferred::object::add(
	deferred::bundle::type const _bundle
)
{
	set_.insert(
		_bundle
	);
}

void
sge::opengl::state::deferred::object::update(
	sge::renderer::state::list const &_list
)
{
	for(
		bundle_set::const_iterator it(
			set_.begin()
		);
		it != set_.end();
		++it
	)
		deferred::apply(
			parameters_,
			*it,
			_list
		);
}
