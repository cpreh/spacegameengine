#ifndef SGE_SPRITE_TYPES_HPP_INCLUDED
#define SGE_SPRITE_TYPES_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include "../math/rect.hpp"
#include "./texture.hpp"
#include "./renderer.hpp"
#include "../main/types.hpp"
#include "../main/shared_ptr.hpp"
#include "../main/array2.hpp"
#include "../main/raw_vector.hpp"

namespace sge
{

class fragmented_texture;

class virtual_texture : boost::noncopyable {
public:
	typedef basic_rect<texture::size_type> rect;

	virtual_texture(const rect&, fragmented_texture*);
	~virtual_texture();
	rect lock_area() const;
	texture_ptr my_texture() const;
private:
	rect area;
	fragmented_texture* fragment;
};

typedef shared_ptr<virtual_texture> virtual_texture_ptr;
typedef shared_ptr<const virtual_texture> const_virtual_texture_ptr;

class fragmented_texture : boost::noncopyable {
public:
	fragmented_texture(renderer_ptr r, texture::size_type texsize, texture::size_type elemsize);
	virtual_texture_ptr consume_fragments(texture::size_type w, texture::size_type h);
	void return_fragments(const virtual_texture&);
	texture_ptr get_texture() const { return tex; }
private:
	typedef array2<raw_vector<bool> > fragment_matrix;
	texture::size_type elemsize;
	fragment_matrix fragments;
	texture_ptr tex;
};

}

#endif
