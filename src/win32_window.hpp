#ifndef SGE_WIN32_WINDOW_HPP_INCLUDED
#define SGE_WIN32_WINDOW_HPP_INCLUDED

#include "./window.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace sge
{

class win32_window : public window {
public:
	win32_window(window_size sz, const std::string& title = "");
	~win32_window();

	void title(const std::string& t);
	void size(window_size newsize);
	window_size size() const { return sz; }
	const std::string& title() const { return _title; }
	HWND get_hwnd() const { return handle; }
private:
	HWND        handle;
	window_size sz;
	std::string _title;
	bool        active;
	static bool wndclass_created;
};

typedef shared_ptr<win32_window> win32_window_ptr;

}

#endif
