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


#ifndef SGE_GUI_UTILITY_CHANNEL_ADDER_HPP_INCLUDED
#define SGE_GUI_UTILITY_CHANNEL_ADDER_HPP_INCLUDED

namespace sge
{
namespace gui
{
namespace utility
{
template<class Pixel0,class Pixel1,class PixelResult>
class channel_adder 
{
public:
	channel_adder(
		Pixel0 const &p0,
		Pixel1 const &p1,
		PixelResult &result);

	template<class T>
	void operator()(T &) const;
private:
	Pixel0 const &p0,
	Pixel1 const &p1;
	PixelResult &result;
};
}
}
}

template<class Pixel0,class Pixel1,class PixelResult>
sge::gui::utility::channel_adder<Pixel>::channel_adder(
	Pixel0 const &p0,
	Pixel1 const &p1,
	PixelResult &result)
: p0(p0),
  p1(p1),
	result(result)
{}

template<class Pixel>
template<class T>
void sge::gui::utility::channel_adder<Pixel>::operator()(T &t) const
{
	result[t] = p0[t]+p1[t];
}

#endif
