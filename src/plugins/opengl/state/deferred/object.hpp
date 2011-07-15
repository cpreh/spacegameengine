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


#ifndef SGE_OPENGL_STATE_DEFERRED_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_STATE_DEFERRED_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "bundle.hpp"
#include "parameters.hpp"
#include <sge/renderer/state/list_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <set>

namespace sge
{
namespace opengl
{
namespace state
{
namespace deferred
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit object(
		deferred::parameters const &
	);

	~object();

	void
	add(
		deferred::bundle::type
	);

	void
	update(
		sge::renderer::state::list const &
	);
private:
	deferred::parameters const parameters_;

	typedef std::set<
		deferred::bundle::type
	> bundle_set;

	bundle_set set_;
};

}
}
}
}

#endif
