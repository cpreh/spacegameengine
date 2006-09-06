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
#include "./types.hpp"
#include "./details.hpp"

namespace sge
{

class sprite_system;
class sprite;
typedef std::list<sprite*> sprite_list;

namespace detail
{
	const index_buffer::size_type indices_per_sprite = 6;
	const vertex_buffer::size_type vertices_per_sprite = 4;
}

class sprite {
public:
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
	rect get_rect() const { return rect(pos(),size()); }
	
	void draw();
	~sprite();

	static bool equal_texture(const sprite& l, const sprite& r);
	static bool less(const sprite& l, const sprite& r);
private:
	friend class sprite_system;

	texture_ptr get_texture() const;
	void update_where(vertex_buffer::iterator where);
	void update();
	index_buffer::iterator update_ib(index_buffer::iterator where);

	point p;
	dim sz;
	unsigned _z;
	bool _visible;
	sprite_system& s;
	const_virtual_texture_ptr tex;
	vertex_buffer::size_type vb_pos;
	sprite_list::iterator my_place;
};

typedef shared_ptr<sprite> sprite_ptr;

}
#endif

