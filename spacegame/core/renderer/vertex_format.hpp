#ifndef SGE_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_VERTEX_FORMAT_HPP_INCLUDED

#include <cstddef>
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

        template<vertex_usage u> struct vertex_traits;
        template<> struct vertex_traits<VU_Pos> {
		typedef space_unit            element_type;
		typedef vector3<element_type> packed_type;
	};
        template<> struct vertex_traits<VU_Normal> {
		typedef space_unit            element_type;
		typedef vector3<element_type> packed_type;
	};
        template<> struct vertex_traits<VU_Tex> {
		typedef space_unit             element_type;
		typedef vector2<element_type>* packed_type;
	};
        template<> struct vertex_traits<VU_Diffuse> {
		typedef int          element_type;
		typedef element_type packed_type;
	};
	
	typedef std::size_t vertex_size;

	const vertex_size vertex_element_size[] = {
		3*sizeof(vertex_traits<VU_Pos>::element_type),
		3*sizeof(vertex_traits<VU_Normal>::element_type),
		2*sizeof(vertex_traits<VU_Tex>::element_type),
		1*sizeof(vertex_traits<VU_Diffuse>::element_type)
	};

	typedef vertex_size offset_info[VU_num_elements];
	
	class vertex_element {
	public:
		vertex_element(const vertex_usage _usage, const vertex_size _count)
			: _usage(_usage), _count(_count), _size(vertex_element_size[_usage]) {}
		vertex_usage usage() const { return _usage; }
		vertex_size  size() const { return _size; }
		vertex_size  count() const { return _count; }
		vertex_size  stride() const { return size()*count(); }
	private:
		vertex_usage  _usage;
		vertex_size   _count;
		vertex_size   _size;
	};
	
	class vertex_format {
	public:
		typedef std::vector<vertex_element> usage_list;
		vertex_format() : _stride(0) {}
		const usage_list& elements() const { return ulist; }
		vertex_size stride() const { return _stride; }
		vertex_format& add(const vertex_usage u, const vertex_size count = 1)
		{
			oi[u] = _stride;
			ulist.push_back(vertex_element(u,count));
			_stride += vertex_element_size[u] * count;
			return *this;
		}
		const offset_info& offsets() const { return oi; }
	private:
		offset_info oi;
		usage_list  ulist;
		vertex_size _stride;
	};

	template<typename T> struct is_const { static const bool value = false; };
	template<typename T> struct is_const<const T&> { static const bool value = true; };
	template<typename T> struct is_const<const T*> { static const bool value = true; };
	
	template<bool,typename T> struct apply_const_if { typedef T type; };
	template<typename T> struct apply_const_if<true,T*> { typedef const T* type; };
	template<typename T> struct apply_const_if<true,T&> { typedef const T& type; };

        template<bool Is_Const> class vertex_pointer_impl {
        public:
                typedef char              value_type;
                typedef std::ptrdiff_t    difference_type;
                typedef std::size_t       size_type;
                typedef typename apply_const_if<Is_Const,char*>::type pointer;

                template<vertex_usage U> typename apply_const_if<is_const<pointer>::value,typename vertex_traits<U>::packed_type>::type element() const
		{
			return *reinterpret_cast<typename apply_const_if<is_const<pointer>::value,typename vertex_traits<U>::packed_type>::type*>(data + oi[U]);
		}
                typename vertex_traits<VU_Pos>::packed_type pos() const { return element<VU_Pos>(); }
                typename vertex_traits<VU_Normal>::packed_type normal() const { return element<VU_Normal>(); }
                typename vertex_traits<VU_Tex>::packed_type tex() const { return element<VU_Tex>(); }
                typename vertex_traits<VU_Diffuse>::packed_type diffuse() const { return element<VU_Diffuse>(); }
		
                vertex_pointer_impl(const pointer data, const size_type stride, const offset_info& oi)
                        :data(data), stride(stride), oi(oi) {}

                template<bool OtherConst>
                vertex_pointer_impl(const vertex_pointer_impl<OtherConst>& o)
                        : data(o.data), stride(o.stride), oi(o.oi) {}
        private:
                pointer data;
                size_type stride;
                const offset_info& oi;
        };
        
	typedef vertex_pointer_impl<true>  const_vertex_pointer;
        typedef vertex_pointer_impl<false> vertex_pointer;
}

#endif
