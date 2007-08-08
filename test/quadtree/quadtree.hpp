#ifndef SGE_QUADTREE_HPP_INCLUDED
#define SGE_QUADTREE_HPP_INCLUDED

#include <vector>
#include <boost/scoped_ptr.hpp>
#include "../../src/math/vector.hpp"
#include "../../src/math/rect.hpp"
#include "../../src/exception.hpp"
#include "mathstuff.hpp"

namespace sge
{
class quadtree
{
	public:
	typedef long index_type;
	struct indexed_triangle { index_type vertices[3]; };
	typedef std::vector<index_type>         index_container_type;
	typedef std::vector<indexed_triangle>   triangle_container_type;
	typedef std::vector<math::vector3> vertex_container_type;
	class lock_ptr
	{
		quadtree &t;
		public:
		lock_ptr(quadtree &tree) : t(tree) { if (tree.locked_) throw exception("tree locked more than once"); tree.lock(); }
		~lock_ptr() { if(!t.locked_) throw exception("logic error: tree already unlocked"); t.unlock(); }
	};

	quadtree(unsigned tree_depth);
	void pack();
	void lock();
	void unlock();
	triangle_container_type &triangles();
	vertex_container_type &vertices();
	void get_visible(const frustum_info &frustum,index_container_type &indices);
	virtual ~quadtree() {}

	protected:
	class subtree
	{
		boost::scoped_ptr<subtree> lefttop,righttop,leftbottom,rightbottom;
		triangle_container_type    acquired_triangles;
		math::rect                 rect;
		bool                       leaf;

		void create_children(const vertex_container_type &vertices,const unsigned tree_depth);
		math::rect determine_bounds(const vertex_container_type &vertices) const;
		void add_all(index_container_type &indices) const;
		public:
		subtree();
		subtree(const vertex_container_type &vertices,const triangle_container_type &triangles,math::rect _rect,unsigned tree_depth);
		void get_visible(const frustum_info &frustum,index_container_type &indices) const;
		void reset(const unsigned tree_depth,const vertex_container_type &vertices,const triangle_container_type &triangles);
	};
	subtree                 tree_root;
	unsigned                tree_depth;
	vertex_container_type   vertices_;
	triangle_container_type triangles_;
	bool                    locked_;
};
}

#endif
