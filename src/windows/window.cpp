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


#include <sge/windows/window.hpp>
#include <sge/windows/wndclass.hpp>
#include <sge/windows/wndclass_pool.hpp>
#include <sge/windows/module_handle.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/tr1/array.hpp>

namespace
{

LRESULT CALLBACK wnd_proc(
	HWND,
	UINT,
	WPARAM,
	LPARAM);

}

// TODO: why did HackLife do this?
/*struct sge::windows::window::signal_combiner {
	typedef callback_return_type result_type;

	template<typename InputIterator>
	result_type operator()(
		InputIterator first,
		InputIterator const last) const
	{
		while (first != last)
		{
			if (*first)
				return **first;
			++first;
		}
		return result_type();
	}
};*/

sge::windows::window::window(
	dim_type const &sz,
	string const &title,
	string const &class_name)
:
	wndclass_(
		wndclass_pool(
			class_name,
			wnd_proc))
{

	DWORD const flags = (WS_VISIBLE | WS_OVERLAPPEDWINDOW);
	RECT r = { 0, 0, 0, 0 };
	if (!AdjustWindowRect(&r, flags, false))
		throw exception(
			SGE_TEXT("AdjustWindowRect() failed!"));

	decoration_size.left() = static_cast<unsigned>(-r.left);
	decoration_size.right() = static_cast<unsigned>(r.right);
	decoration_size.top() = static_cast<unsigned>(-r.top);
	decoration_size.bottom() = static_cast<unsigned>(r.bottom);

	handle = CreateWindow(
		wndclass_->name().c_str(),
		title.c_str(),
		flags,
		0,
		0,
		decoration_size.left() + decoration_size.right() + sz.w(),
		decoration_size.bottom() + decoration_size.top() + sz.h(),
		0,
		0,
		module_handle(),
		this);
	
	if(!handle)
		throw exception(
			SGE_TEXT("CreateWindow() failed!"));
}

sge::windows::window::~window()
{
	DestroyWindow(handle);
}

void sge::windows::window::size(
	dim_type const &nsz)
{
	if(SetWindowPos(
		hwnd(),
		HWND_TOP,
		0,
		0,
		decoration_size.left() + decoration_size.right() + nsz.w(),
		decoration_size.top() + decoration_size.bottom() + nsz.h(),
		SWP_SHOWWINDOW
	) == 0)
		throw exception(
			SGE_TEXT("SetWindowPos() failed!"));
}

void sge::windows::window::title(
	string const &title)
{
	if(SetWindowText(hwnd(), title.c_str()) == 0)
		throw exception(
			SGE_TEXT("SetWindowText() failed!"));
}

sge::windows::window::dim_type const
sge::windows::window::size() const
{
	RECT rect;
	if(GetWindowRect(handle, &rect) == FALSE)
		throw exception(
			SGE_TEXT("GetWindowRect() failed!"));
	return dim_type(
		rect.right - rect.left - decoration_size.left() - decoration_size.right(),
		rect.bottom - rect.top - decoration_size.top() + decoration_size.bottom()
	);
}

sge::window::pos_type const
sge::windows::window::viewport_offset() const
{
	return window::pos_type(
		0,
		-2*decoration_size.bottom()
	);
}

sge::string const
sge::windows::window::title() const
{
	// TODO: read the length first!
	std::tr1::array<TCHAR, 1024> buffer;
	if(GetWindowText(hwnd(), buffer.data(), buffer.size()) == 0)
		throw exception(
			SGE_TEXT("GetWindowText() failed!"));
	return string(buffer.data());
}

HWND sge::windows::window::hwnd() const
{
	return handle;
}

boost::signals::connection
sge::windows::window::register_callback(
	event_type const msg,
	callback_type const func)
{
	return signals[msg].connect(func);
}

sge::windows::window::callback_return_type
sge::windows::window::execute_callback(
	event_type const msg,
	WPARAM const wparam,
	LPARAM const lparam)
{
	sge::windows::window::signal_map::iterator const it = signals.find(msg);
	return it != signals.end()
		? (*(it->second))(*this, msg, wparam, lparam)
		: callback_return_type();
}

void sge::windows::window::dispatch()
{
	MSG msg;
	while(PeekMessage(&msg, handle, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

namespace
{

LRESULT CALLBACK
wnd_proc(
	HWND const hwnd,
	unsigned const msg,
	WPARAM const wparam,
	LPARAM const lparam)
{
	if (msg == WM_CREATE)
	{
		CREATESTRUCT* const s = reinterpret_cast<CREATESTRUCT*>(lparam);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(s->lpCreateParams));
	}

	sge::windows::window *const wnd = reinterpret_cast<sge::windows::window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (wnd)
	{
		sge::windows::window::callback_return_type const ret =
			wnd->execute_callback(msg, wparam, lparam);
		if (ret)
			return *ret;
	}

	switch(msg) {
	case WM_CLOSE:
		return 0;
	case WM_CREATE:
		break;
	case WM_ACTIVATE:
	{
		sge::windows::window* const wnd
			= reinterpret_cast<sge::windows::window*>(
				GetWindowLongPtr(hwnd, GWLP_USERDATA));

		bool const active = wparam != 0 ? true : false;
		if(!active)
			ShowWindow(wnd->hwnd(),SW_MINIMIZE);
		return 0;
	}
	default:
		return DefWindowProc(hwnd,msg,wparam,lparam);
	}
	return TRUE;
}

}
