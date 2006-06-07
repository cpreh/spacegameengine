#ifndef SGE_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_VERTEX_FORMAT_HPP_INCLUDED

#include <vector>
#include <stdexcept>
#include "../main/types.hpp"
#include "./renderer_types.hpp"

namespace sge
{
	enum vertex_usage {
		VU_Pos,
		VU_Normal,
		VU_Tex,
		VU_Diffuse,
		VU_num_elements
	};
	typedef bitfield<vertex_usage,VU_num_elements> vertex_usage_t;

	typedef unsigned vertex_size;

	vertex_size vertex_element_size(vertex_usage usage);

	struct offset_info {
		typedef size_t size_type; 
		offset_info(const size_type pos_off = 0, const size_type normal_off = 0,
			    const size_type diffuse_off = 0, const size_type tex_coord_off = 0)
		: pos_off(pos_off), normal_off(normal_off), diffuse_off(diffuse_off), tex_coord_off(tex_coord_off) {}

		size_type  pos_off;
		size_type  normal_off;
		size_type  diffuse_off;
		size_type  tex_coord_off;
	};
	
	class vertex_element {
	public:
		vertex_element(const vertex_usage usage, const vertex_size count = 1)
			: usage(usage), count(count), size(vertex_element_size(usage)) {}
		vertex_usage get_usage() const { return usage; }
		vertex_size get_size() const { return size; }
		vertex_size get_count() const { return count; }
		vertex_size get_stride() const { return get_size()*get_count(); }
	private:
		vertex_usage  usage;
		vertex_size   count;
		vertex_size   size;
	};
	
	class vertex_format {
		friend vertex_format& operator<< (vertex_format&, const vertex_element&);
	public:
		typedef std::vector<vertex_element> usage_list;
		vertex_format() : stride(0) {}
		vertex_format(const vertex_usage_t& t)
		{
			for(vertex_usage_t::size_type s = 0; s < t.size(); ++s)
				if(t[vertex_usage(s)]) ulist.push_back(vertex_element(vertex_usage(s)));
		}
		const usage_list& get_elements() const { return ulist; }
		vertex_size get_stride() const { return stride; }
		vertex_format& add(const vertex_usage u) { return (*this) << u; }
	private:
		usage_list  ulist;
		vertex_size stride;
	};
	inline vertex_format create_vertex_format() { return vertex_format(); }

	inline vertex_format& operator<< (vertex_format& f, const vertex_element& e)
	{
		f.ulist.push_back(e);
		f.stride += e.get_stride();
		return f;
	}
	
	inline void fill_offset_info(offset_info& oi, const vertex_size offset,
		                     const vertex_usage u)
	{
		switch(u) {
		case VU_Pos:
			oi.pos_off = offset;
			break;
		case VU_Tex:
			oi.tex_coord_off = offset;
			break;
		case VU_Normal:
			oi.normal_off = offset;
			break;
		case VU_Diffuse:
			oi.diffuse_off = offset;
			break;
		default:
			throw std::logic_error("unsupported vertex_usage");
		}
	}

	inline vertex_size vertex_element_size(const vertex_usage usage)
	{
		const vertex_size float_size = sizeof(float);
		const vertex_size int_size = sizeof(int);
		switch(usage) {
		case VU_Pos:
		case VU_Normal:
			return 3*float_size;
		case VU_Diffuse:
			return 1*int_size;
		case VU_Tex:
			return 2*float_size;
		default:
			throw std::logic_error("wrong vertex_usage");
		}
	}
}

#endif
