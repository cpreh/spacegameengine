#ifndef SGE_VERTEX_POINTER_HPP_INCLUDED
#define SGE_VERTEX_POINTER_HPP_INCLUDED

#include <cstddef>
#include "../math/vector2.hpp"
#include "../math/vector3.hpp"
#include "../main/algorithm.hpp"

namespace sge
{
	class const_vertex_pointer;

        class vertex_pointer {
        public:
                typedef char                       value_type;
                typedef std::ptrdiff_t             difference_type;
                typedef std::size_t                size_type;
                typedef value_type*                pointer;
                typedef const value_type*          const_pointer;
                typedef sge::vector2<space_unit>   vector2;
                typedef sge::vector3<space_unit>   vector3;

                const vector3& pos() const { return *reinterpret_cast<vector3*>(data + oi.pos_off); }
                vector3& pos()  { return *reinterpret_cast<vector3*>(data + oi.pos_off); }

                const vector3& normal() const { return *reinterpret_cast<vector3*>(data + oi.normal_off); }
                vector3& normal() { return *reinterpret_cast<vector3*>(data + oi.normal_off); }

                const color& diffuse() const { return *reinterpret_cast<color*>(data + oi.diffuse_off); }
                color& diffuse() { return *reinterpret_cast<color*>(data + oi.diffuse_off); }

                const vector2* tex() const { return reinterpret_cast<vector2*>(data + oi.tex_coord_off); }
                vector2* tex() { return reinterpret_cast<vector2*>(data + oi.tex_coord_off); }

                vertex_pointer(pointer data, size_type stride, const offset_info& oi)
                        : data(data), stride(stride), oi(oi) {}
        private:
                pointer data;
                size_type stride;
                const offset_info& oi;
                friend class const_vertex_pointer;
        };

        class const_vertex_pointer {
        public:
                typedef vertex_pointer::value_type         value_type;
                typedef vertex_pointer::difference_type    difference_type;
                typedef vertex_pointer::size_type          size_type;
                typedef vertex_pointer::const_pointer      const_pointer;
		typedef const_pointer                      pointer;
                typedef vertex_pointer::vector2            vector2;
                typedef vertex_pointer::vector3            vector3;

                const vector3& pos() const { return *reinterpret_cast<const vector3*>(data + oi.pos_off); }
                const vector3& normal() const { return *reinterpret_cast<const vector3*>(data + oi.normal_off); }
                const color& diffuse() const { return *reinterpret_cast<const color*>(data + oi.diffuse_off); }
                const vector2* tex() const { return reinterpret_cast<const vector2*>(data + oi.tex_coord_off); }

                const_vertex_pointer(const_pointer data, const offset_info& oi)
                        : data(data), oi(oi) {}
		const_vertex_pointer(const vertex_pointer& v)
                        : data(v.data), oi(v.oi) {}
        private:
		const_pointer  data;
		offset_info    oi;
        };

}

#endif
