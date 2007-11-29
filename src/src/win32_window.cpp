/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2007       Simon Stienen    (simon.stienen@slashlife.org)

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

#include <iostream>

#include "../types.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include "../exception.hpp"
#include "../win32_window.hpp"
#include "../win32_conv.hpp"

namespace
{
	LRESULT CALLBACK wnd_proc(HWND,unsigned,WPARAM,LPARAM);
}

sge::win32_window::win32_window(const window_size sz, const string& title)
: _title(title)
{
	const TCHAR* const window_classname = TEXT("SpacegameWindow");

	HINSTANCE instance = GetModuleHandle(0);

	if(!wndclass_created)
	{
		WNDCLASSEX wndclass;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
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
			throw exception("RegisterClassEx() failed");
		wndclass_created = true;
	}

	DWORD flags = (WS_VISIBLE | WS_OVERLAPPEDWINDOW);
	RECT r = { 0, 0, 0, 0 };
	if (!AdjustWindowRect(&r, flags, false))
		throw exception("AdjustWindowRect() failed");

	decoration_size.l = static_cast<unsigned>(-r.left);
	decoration_size.r = static_cast<unsigned>(r.right);
	decoration_size.t = static_cast<unsigned>(-r.top);
	decoration_size.b = static_cast<unsigned>(r.bottom);

	handle = CreateWindow(window_classname,
		sge_str_to_win(_title).c_str(),
		flags,
		0,
		0,
		decoration_size.l + decoration_size.r + sz.w(),
		decoration_size.b + decoration_size.t + sz.h(),
		0,
		0,
		instance,
		this);
	if(!handle)
		throw exception("CreateWindow() failed");
}

sge::win32_window::~win32_window()
{
	DestroyWindow(handle);
}

void sge::win32_window::size(const window_size nsz)
{
	if(SetWindowPos(
		hwnd(),
		HWND_TOP,
		0,
		0,
		decoration_size.l + decoration_size.r + nsz.w(),
		decoration_size.t + decoration_size.b + nsz.h(),
		SWP_SHOWWINDOW
	) == 0)
		throw exception("SetWindowPos() failed");
}

void sge::win32_window::title(const string& ntitle)
{
	_title = ntitle;
	if(SetWindowText(hwnd(),sge_str_to_win(_title).c_str()) == 0)
		throw exception("SetWindowText() failed");
}

sge::win32_window::window_size sge::win32_window::size() const
{
	RECT rect;
	if(GetWindowRect(handle, &rect) == FALSE)
		throw exception("GetWindowRect() failed");
	return window_size(
		rect.right - rect.left - decoration_size.l - decoration_size.r,
		rect.bottom - rect.top - decoration_size.t + decoration_size.b
	);
}

sge::win32_window::window_pos sge::win32_window::viewport_offset() const
{
	return window_pos(
		0,
		-2*decoration_size.b
	);
}

const sge::string& sge::win32_window::title() const
{
	return _title;
}

HWND sge::win32_window::hwnd() const
{
	return handle;
}

boost::signals::connection sge::win32_window::register_callback(win32_event_type msg, win32_callback_type func)
{
	return signals[msg].connect(func);
}

sge::win32_window::win32_callback_return_type sge::win32_window::execute_callback(win32_event_type msg, WPARAM wparam, LPARAM lparam)
{
	sge::win32_window::win32_signal_map::iterator it = signals.find(msg);
	if (it != signals.end())
		return (*(it->second))(*this, msg, wparam, lparam);
	else
		return sge::win32_window::win32_callback_return_type();
}

void sge::window::dispatch()
{
	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

bool sge::win32_window::wndclass_created(false);

namespace
{
	LRESULT CALLBACK wnd_proc(HWND hwnd, unsigned msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_CREATE)
		{
			CREATESTRUCT* const s = reinterpret_cast<CREATESTRUCT*>(lparam);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(s->lpCreateParams));
		}

		sge::win32_window *wnd = reinterpret_cast<sge::win32_window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		if (wnd)
		{
			sge::win32_window::win32_callback_return_type ret =
				wnd->execute_callback(msg, wparam, lparam);
			if (ret)
				return *ret;
		}

		LRESULT returnvalue = TRUE;
		switch(msg) {
		case WM_CLOSE:
			return 0;
		case WM_CREATE:
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

		return returnvalue;
	}
}

#endif
