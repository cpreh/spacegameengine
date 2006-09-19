#ifndef SGE_X_WINDOW_HPP_INCLUDED
#define SGE_X_WINDOW_HPP_INCLUDED

#include "./window.hpp"
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <stdexcept>

namespace sge
{
	class x_window : public window {
	public:
		x_window(window_size sz, const std::string& title, Display* dsp, int screen, XVisualInfo* vi, Colormap& cmap);
		~x_window();

		void title(const std::string& title);
		void size(window_size sz);
		window_size size() const { return sz; }
		const std::string& title() const { return _title; }
		bool active() const { return _active; }

		Window get_window() const { return wnd; }
		int get_screen() const { return screen; }
		Display* get_display() const { return dsp; }
	private:
		Window wnd;
		window_size sz;
		std::string _title;
		bool _active;
		Display* dsp;
		int screen;
		Visual* vi;
	};
	typedef shared_ptr<x_window> x_window_ptr;
}

#endif
