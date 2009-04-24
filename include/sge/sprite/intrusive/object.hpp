/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_SPRITE_INTRUSIVE_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_OBJECT_HPP_INCLUDED

#include <sge/sprite/intrusive/object_fwd.hpp>
#include <sge/sprite/intrusive/system_fwd.hpp>
#include <sge/sprite/intrusive/order.hpp>
#include <sge/sprite/object.hpp>
#include <sge/export.hpp>
#include <boost/intrusive/list_hook.hpp>

namespace sge
{
namespace sprite
{
namespace intrusive
{

namespace detail
{

typedef boost::intrusive::list_base_hook<
	boost::intrusive::link_mode<
		boost::intrusive::auto_unlink
	>
> object_base_hook;

}

class object : public sprite::object, public detail::object_base_hook {
public:
	typedef intrusive::order order_type;

	SGE_SYMBOL object(
		system &,
		order_type,
		point const &,
		texture::const_part_ptr,
		dim const &,
		sprite::color const &,
		depth_type,
		rotation_type,
		bool visible);
	
	SGE_SYMBOL object(
		object const &);

	SGE_SYMBOL object &
	operator=(
		object const &);

	SGE_SYMBOL void order(
		order_type);
	SGE_SYMBOL order_type order() const;

	SGE_SYMBOL void transfer(
		system &);
private:
	void add_me();

	system *sys;
	order_type order_;
};

}
}
}

#endif
