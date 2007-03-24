/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../types.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include "../win32_window.hpp"
#include "../win32_conv.hpp"
#include <stdexcept>

namespace
{
	LRESULT CALLBACK wnd_proc(HWND,unsigned,WPARAM,LPARAM);
}

sge::win32_window::win32_window(const window_size sz, const bool _fullscreen, const string& _title)
: _title(_title),
  _fullscreen(_fullscreen)
{
	const TCHAR* const window_classname = TEXT("SpacegameWindow");

	HINSTANCE instance = GetModuleHandle(0);

	if(!wndclass_created)
	{
		const COLORREF bgcolor = RGB(255,255,255);
		WNDCLASSEX wndclass;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hbrBackground = CreateSolidBrush(bgcolor);
		wndclass.hCursor = 0;
		wndclass.hIcon = 0;
		wndclass.hIconSm = 0;
		wndclass.hInstance = instance;
		wndclass.lpfnWndProc = wnd_proc;
		wndclass.lpszClassName = window_classname;
		wndclass.lpszMenuName = 0;
		wndclass.cbSize = sizeof(WNDCLASSEX);
		wndclass.style = 0;
		if(!RegisterClassEx(&wndclass))
			throw std::runtime_error("RegisterClassEx() failed");
		wndclass_created = true;
	}

	handle = CreateWindow(window_classname,
		sge_str_to_win(_title).c_str(),
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		0,
		0,
		sz.w(),
		sz.h(),
		0,
		0,
		instance,
		this);
	if(!handle)
		throw std::runtime_error("CreateWindow() failed");
}

sge::win32_window::~win32_window()
{
	DestroyWindow(handle);
}

void sge::win32_window::size(const window_size nsz)
{
	if(SetWindowPos(hwnd(),HWND_TOP,0,0,nsz.w(),nsz.h(),SWP_SHOWWINDOW) == 0)
		throw std::runtime_error("SetWindowPos() failed");
}

void sge::win32_window::title(const string& ntitle)
{
	_title = ntitle;
	if(SetWindowText(hwnd(),sge_str_to_win(_title).c_str()) == 0)
		throw std::runtime_error("SetWindowText() failed");
}

sge::win32_window::window_size sge::win32_window::size() const
{
	RECT rect;
	if(GetWindowRect(handle, &rect) == FALSE)
		throw std::runtime_error("GetWindowRect() failed");
	return window_size(rect.right - rect.left, rect.bottom - rect.top);
}

const sge::string& sge::win32_window::title() const
{
	return _title;
}

bool sge::win32_window::fullscreen() const
{
	return _fullscreen;
}

HWND sge::win32_window::hwnd() const
{
	return handle;
}

bool sge::win32_window::wndclass_created(false);

namespace
{
	LRESULT CALLBACK wnd_proc(HWND hwnd, unsigned msg, WPARAM wparam, LPARAM lparam)
	{
		switch(msg) {
		case WM_CLOSE:
			return 0;
		case WM_CREATE:
		{
			CREATESTRUCT* const s = reinterpret_cast<CREATESTRUCT*>(lparam);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(s->lpCreateParams));
		}
		break;
		case WM_ACTIVATE:
		{
			sge::win32_window* const wnd = reinterpret_cast<sge::win32_window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			const bool active = wparam != 0 ? true : false;
			//wnd->set_active(active); // FIXME
			if(!active)
				ShowWindow(wnd->hwnd(),SW_MINIMIZE);
		}
		return 0;
		default:
			return DefWindowProc(hwnd,msg,wparam,lparam);
		}
		return TRUE;
	}
}

#endif
