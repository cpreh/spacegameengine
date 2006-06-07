#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include <map>
#include <string>
#include <boost/utility.hpp>
#include "./cursor.hpp"
#include "../core/main/auto_ptr.hpp"
#include "../core/main/timer.hpp"
#include "../core/renderer/renderer.hpp"
#include "../core/renderer/sprite.hpp"
#include "../core/renderer/sprite_system.hpp"
#include "../core/image/image_loader.hpp"
#include "../core/renderer/font.hpp"
#include "../core/input/input_system.hpp"
#include "./types.hpp"
#include "./element.hpp"
#include "./events.hpp"
#include "./skin.hpp"

namespace sge
{
namespace gui
{
	class manager : boost::noncopyable {
	public:
		friend class element;
	
		SGEGUIDLLAPI manager(renderer_ptr rend, font& f, image_loader_ptr il, const std::string& graphics_path);
		SGEGUIDLLAPI void process(const input_array& input);
		void focus(element* const e) { _focus = e; }
		element* focus() const { return _focus; }
		element* hover() const { return _hover; }
		element* pressed() const { return _pressed; }
		point cursor_pos() const { return cur.pos(); }
		void draw_selection(point p, dim sz);
		font& get_font() const { return gui_font; }
		sprite_system& get_sprite_system() { return sprite_sys; }
	private:
		void on_texture_not_present(const std::string& name);
		void move_mouse(unit x, unit y);

		element* root() { return &_root; }
		element* last_clicked() const { return _last_clicked; }
		void hover(element* const e) { _hover = e; }
		void pressed(element* const e) { _pressed = e; }
		void last_clicked(element* e) { _last_clicked = e; }

		struct root_elem : public element {
			root_elem(manager& m)
				: element(m,0) {}
				bool intersects(point) const { return true; }
				point relative_pos() const { return point(); }
		};

		std::string             graphics_path;
		sprite_system           sprite_sys;
		font&                   gui_font;
		image_loader_ptr        il;
		cursor                  cur;
		point                   mouse_scale;
		element*                _focus;
		element*                _hover;
		element*                _pressed;
		element*                _last_clicked;
		timer                   double_click_time;
		timer                   key_repeat_interval;
		timer                   key_repeat_time;
		timer                   mouse_repeat_interval;
		timer                   mouse_repeat_time;
		key_type                last_key;
		bool                    key_repeat;
		key_type                last_mouse;
		bool                    mouse_repeat;
		root_elem               _root;
		modifier_state          key_mod;
	};
}
}

#endif
