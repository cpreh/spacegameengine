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


#ifndef SGE_D3D9_STATE_DEFERRED_OBJECT_HPP_INCLUDED
#define SGE_D3D9_STATE_DEFERRED_OBJECT_HPP_INCLUDED

#include <sge/d3d9/state/deferred/bundle.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/state/list_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace d3d9
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
		IDirect3DDevice9 *
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
	IDirect3DDevice9 *const device_;

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
