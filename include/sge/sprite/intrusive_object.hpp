/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "object.hpp"
#include "../export.hpp"
#include <boost/intrusive/list_hook.hpp>
#include <boost/optional.hpp>

namespace sge
{
namespace sprite
{

class intrusive_system;

namespace detail
{

typedef boost::intrusive::list_base_hook<
	boost::intrusive::link_mode<
		boost::intrusive::auto_unlink
	>
> object_base_hook;

}

class intrusive_object : public object, public detail::object_base_hook {
public:
	typedef unsigned order_type;

	SGE_SYMBOL intrusive_object(
		intrusive_system &,
		order_type,
		boost::optional<point> = defaults::pos_,
		boost::optional<texture::part_ptr> = defaults::texture_,
		boost::optional<dim> = defaults::dim_,
		boost::optional<color_t> = defaults::color_,
		boost::optional<depth_type> = defaults::depth_,
		boost::optional<rotation_type> = defaults::rotation_,
		boost::optional<bool> visible = defaults::visible_);
	
	SGE_SYMBOL intrusive_object(
		intrusive_object const &);

	SGE_SYMBOL intrusive_object &
	operator=(
		intrusive_object const &);

	SGE_SYMBOL void order(
		order_type);
	SGE_SYMBOL order_type order() const;
private:
	void add_me();

	intrusive_system &sys;
	order_type       order_;
};


}
}

#endif
