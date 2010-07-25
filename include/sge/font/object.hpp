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


#ifndef SGE_FONT_OBJECT_HPP_INCLUDED
#define SGE_FONT_OBJECT_HPP_INCLUDED

#include <sge/font/object_fwd.hpp>
#include <sge/font/drawer_ptr.hpp>
#include <sge/font/metrics_ptr.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace font
{

class object
{
public:
	SGE_SYMBOL explicit object(
		metrics_ptr metrics,
		drawer_ptr drawer = drawer_ptr()
	);

	SGE_SYMBOL ~object();

	SGE_SYMBOL metrics_ptr const
	metrics() const;

	SGE_SYMBOL drawer_ptr const
	drawer() const;
private:
	metrics_ptr metrics_;

	drawer_ptr drawer_;
};

}
}

#endif
