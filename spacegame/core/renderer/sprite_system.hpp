#ifndef SGE_SPRITE_SYSTEM_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_HPP_INCLUDED

#include <list>
#include <map>
#include <string>
#include <vector>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include "./sprite_types.hpp"
#include "./sprite.hpp"
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../renderer/texture.hpp"
#include "../renderer/renderer.hpp"
#include "../image/image.hpp"

namespace sge
{
	class sprite_system : boost::noncopyable {
	public:
		typedef boost::function<void (const std::string&)> handler_function;

		sprite_system(renderer_ptr r, texture::size_type tex_size_pow2, texture::size_type elements_per_row, handler_function not_found_handler = 0);
		bool add_texture(texture::const_pointer src, texture::size_type w, texture::size_type h, const std::string& name);
		bool add_texture(image_ptr im, const std::string& name);
		bool remove_texture(const std::string& name);
		void draw();
		void clear();

		static const char* const no_texture;
	private:
		virtual_texture_ptr vtexture(const std::string&) const;

		void insert_texture(virtual_texture_ptr, const std::string& name);
		void set_parameters();
		sprite_list::iterator attach(sprite& s);
		void detach(const sprite& s);
		vertex_buffer::size_type free_vb_pos();

		friend class sprite;

		handler_function texture_not_present_handler;
		sprite_list sprites;
		renderer_ptr r;
		texture::size_type texsize, elemsize;

		typedef std::map<std::string, virtual_texture_ptr> virtual_texture_map;
		virtual_texture_map virtual_textures;

		typedef shared_ptr<fragmented_texture> fragmented_texture_ptr;
		typedef std::list<fragmented_texture_ptr> fragmented_texture_list;
		fragmented_texture_list fragmented_textures;

		vertex_buffer_ptr vb;
		index_buffer_ptr ib;
		typedef std::vector<vertex_buffer::size_type> free_pos_vector;
		free_pos_vector free_pos;
	};
}

#endif

