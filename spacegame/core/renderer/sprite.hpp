#ifndef SGE_SPRITE_HPP_INCLUDED
#define SGE_SPRITE_HPP_INCLUDED

#include <list>
#include <string>
#include "../math/rect.hpp"
#include "../math/vector2.hpp"
#include "../math/dim.hpp"
#include "../math/rect.hpp"
#include "../main/shared_ptr.hpp"
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../renderer/texture.hpp"

namespace sge
{
	struct texture_fragment;
	class sprite_system;
	class sprite;
	typedef std::list<sprite*> sprite_list;

	class sprite {
	public:
		typedef basic_rect<space_unit> rect;

		sprite(sprite_system& s, point pos, dim sz, unsigned z, const std::string& tex, bool visible = true);
		sprite(const sprite& s);

		void x(space_unit nx) { p.x = nx; }
		void y(space_unit ny) { p.y = ny; }
		void pos(point np) { p = np; }
		void width(space_unit w) { sz.w = w; }
		void height(space_unit h) { sz.h = h; }
		void size(dim nsz) { sz = nsz; }
		void z(unsigned nz) { _z = nz; }
		void visible(bool nvisible) { _visible = nvisible; }
		void set_texture(const std::string& name);
		
		space_unit x() const { return p.x; }
		space_unit y() const { return p.y; }
		point pos() const { return p; }
		space_unit width() const { return sz.w; }
		space_unit height() const { return sz.h; }
		dim size() const { return sz; }
		unsigned z() const { return _z; }
		bool visible() const { return _visible; }
		rect get_rect() const { return rect(x(),y(),x()+width(),y()+height()); }
		
		void draw();
		~sprite();
	private:
		friend class sprite_system;
		void update_where(vertex_buffer::iterator where);
		void update();
		index_buffer::iterator update_ib(index_buffer::iterator where);

		point p;
		dim sz;
		unsigned _z;
		bool _visible;
		sprite_system& s;
		const virtual_texture* tex;
		vertex_buffer::size_type vb_pos;
		sprite_list::iterator my_place;
	};
	typedef shared_ptr<sprite> sprite_ptr;
}
#endif

