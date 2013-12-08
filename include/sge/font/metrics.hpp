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


#ifndef SGE_FONT_METRICS_HPP_INCLUDED
#define SGE_FONT_METRICS_HPP_INCLUDED

#include <sge/font/ascent.hpp>
#include <sge/font/descent.hpp>
#include <sge/font/height.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/symbol.hpp>


namespace sge
{
namespace font
{

class metrics
{
public:
	SGE_FONT_SYMBOL
	metrics(
		sge::font::ascent,
		sge::font::descent,
		sge::font::height
	);

	SGE_FONT_SYMBOL
	sge::font::ascent const
	ascent() const;

	SGE_FONT_SYMBOL
	sge::font::descent const
	descent() const;

	SGE_FONT_SYMBOL
	sge::font::height const
	height() const;
private:
	sge::font::ascent ascent_;

	sge::font::descent descent_;

	sge::font::height height_;
};

}
}

#endif
