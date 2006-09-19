#ifndef SGE_WIN32_WINDOW_HPP_INCLUDED
#define SGE_WIN32_WINDOW_HPP_INCLUDED

#include "./window.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace sge
{
	class win32_window : public window {
	public:
		SGECOREDLLAPI win32_window(window_size sz, const std::string& title = "");
		SGECOREDLLAPI ~win32_window();

		SGECOREDLLAPI void title(const std::string& t);
		SGECOREDLLAPI void size(window_size newsize);
		SGECOREDLLAPI window_size size() const { return sz; }
		SGECOREDLLAPI const std::string& title() const { return _title; }
		SGECOREDLLAPI HWND get_hwnd() const { return handle; }
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
