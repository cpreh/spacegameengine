#ifndef SGE_GUI_RECTANGLE_HPP_INCLUDED
#define SGE_GUI_RECTANGLE_HPP_INCLUDED

#include "./types.hpp"
#include "./element.hpp"
#include "../core/renderer/sprite_system.hpp"
#include "../core/renderer/sprite.hpp"

namespace sge
{
	namespace gui
	{
		class manager;
	
		class rectangle : public element, private sprite {
		public:
			SGEGUIDLLAPI rectangle(manager& m, element* parent, point pos, dim sz, const std::string& texture_name, bool visible = true, bool enabled = true);
			unit x() const { return rel_pos.x; }
			void x(const unit _x) { rel_pos.x = _x; }
			unit y() const { return rel_pos.y; }
			void y(const unit _y) { rel_pos.y = _y; }
			point pos() const { return rel_pos; }
			void pos(const point p) { rel_pos = p; }
			
			using sprite::width;
			using sprite::height;
			using sprite::size;
			SGEGUIDLLAPI bool intersects(point p) const;
		protected:
			SGEGUIDLLAPI virtual void on_draw(const draw_event& event);
			using sprite::set_texture;
		private:
			point relative_pos() const { return rel_pos; }
			point rel_pos;
		};
	}
}

#endif
