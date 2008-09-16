/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2007       Simon Stienen    (s.stienen@slashlife.org)

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


#include <sge/exception.hpp>
#include <sge/windows/window.hpp>
#include <sge/windows/conv.hpp>
#include <boost/array.hpp>

namespace
{
	LRESULT CALLBACK wnd_proc(HWND,unsigned,WPARAM,LPARAM);
}

sge::windows::window::window(
	window_size const sz,
	string const &title)
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
			throw exception(SGE_TEXT("RegisterClassEx() failed!"));
		wndclass_created = true;
	}

	DWORD flags = (WS_VISIBLE | WS_OVERLAPPEDWINDOW);
	RECT r = { 0, 0, 0, 0 };
	if (!AdjustWindowRect(&r, flags, false))
		throw exception(SGE_TEXT("AdjustWindowRect() failed!"));

	decoration_size.l = static_cast<unsigned>(-r.left);
	decoration_size.r = static_cast<unsigned>(r.right);
	decoration_size.t = static_cast<unsigned>(-r.top);
	decoration_size.b = static_cast<unsigned>(r.bottom);

	handle = CreateWindow(window_classname,
		sge_str_to_win(title).c_str(),
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
		throw exception(SGE_TEXT("CreateWindow() failed!"));
}

sge::windows::window::~window()
{
	DestroyWindow(handle);
}

void sge::windows::window::size(
	window_size const &nsz)
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
		throw exception(SGE_TEXT("SetWindowPos() failed!"));
}

void sge::windows::window::title(
	string const &title)
{
	if(SetWindowText(hwnd(),sge_str_to_win(title).c_str()) == 0)
		throw exception(SGE_TEXT("SetWindowText() failed!"));
}

sge::windows::window::window_size const
sge::windows::window::size() const
{
	RECT rect;
	if(GetWindowRect(handle, &rect) == FALSE)
		throw exception(SGE_TEXT("GetWindowRect() failed!"));
	return window_size(
		rect.right - rect.left - decoration_size.l - decoration_size.r,
		rect.bottom - rect.top - decoration_size.t + decoration_size.b
	);
}

sge::windows::window::window_pos const
sge::windows::window::viewport_offset() const
{
	return window_pos(
		0,
		-2*decoration_size.b
	);
}

sge::string const
sge::windows::window::title() const
{
	// TODO: read the length first!
	boost::array<TCHAR, 1024> buffer;
	if(GetWindowText(hwnd(), buffer.c_array(), buffer.size()) == 0)
		throw exception(
			SGE_TEXT("GetWindowText() failed!"));
	return string(buffer.data());
}

HWND sge::windows::window::hwnd() const
{
	return handle;
}

boost::signals::connection sge::windows::window::register_callback(win32_event_type msg, win32_callback_type func)
{
	return signals[msg].connect(func);
}

sge::windows::window::win32_callback_return_type sge::windows::window::execute_callback(win32_event_type msg, WPARAM wparam, LPARAM lparam)
{
	sge::windows::window::win32_signal_map::iterator it = signals.find(msg);
	if (it != signals.end())
		return (*(it->second))(*this, msg, wparam, lparam);
	else
		return sge::windows::window::win32_callback_return_type();
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

bool sge::windows::window::wndclass_created(false);

namespace
{
	LRESULT CALLBACK wnd_proc(HWND hwnd, unsigned msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_CREATE)
		{
			CREATESTRUCT* const s = reinterpret_cast<CREATESTRUCT*>(lparam);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(s->lpCreateParams));
		}

		sge::windows::window *wnd = reinterpret_cast<sge::windows::window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		if (wnd)
		{
			sge::windows::window::win32_callback_return_type ret =
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
			sge::windows::window* const wnd = reinterpret_cast<sge::windows::window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
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
