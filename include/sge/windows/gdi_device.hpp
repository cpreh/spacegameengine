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


#ifndef SGE_WINDOWS_GDI_DEVICE_HPP_INCLUDED
#define SGE_WINDOWS_GDI_DEVICE_HPP_INCLUDED

#include <sge/windows/windows.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace windows
{

class gdi_device {
	SGE_NONCOPYABLE(gdi_device)
public:
	class get_tag{};
	SGE_SYMBOL gdi_device(
		HWND,
		get_tag);
	SGE_SYMBOL ~gdi_device();
	SGE_SYMBOL HDC hdc() const;
private:
	HWND hwnd;
	HDC dc;
};

}
}

#endif
