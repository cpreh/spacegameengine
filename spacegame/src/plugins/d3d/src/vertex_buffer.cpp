#include "../../../core/renderer/lock_ptr.hpp"
#include "../vertex_buffer.hpp"
#include "../vertex_format.hpp"
#include "../conversion.hpp"

sge::d3d::vertex_buffer::vertex_buffer(renderer* const r, const d3d_device_ptr device, const sge::vertex_format& format, const size_type sz, const resource_flag_t nflags, const const_pointer src)
: resource(r, nflags & RF_Dynamic),
  device(device), lock_dest(0), _flags(nflags), sz(sz), format(format), d3d_format(device,format)
{
	init(src);
}

void sge::d3d::vertex_buffer::init(const const_pointer src)
{
	const DWORD fvf = d3d_format.fvf();
	const DWORD usage = convert_cast<DWORD>(flags);
	const D3DPOOL pool = convert_cast<D3DPOOL>(flags);

	IDirect3DVertexBuffer9* p;
	if(device->CreateVertexBuffer(unsigned(get_stride() * size()),usage,fvf,pool,&p,0) != D3D_OK)
		throw std::runtime_error("cannot create vertex buffer");
	buffer = p;
	if(src)
	{
		lock_ptr<vertex_buffer> l(this);
		copy(src,src+sz*stride(),lock_dest);
	}
}

sge::d3d::vertex_buffer::iterator sge::d3d::vertex_buffer::begin()
{
	return create_iterator(lock_dest);
}

sge::d3d::vertex_buffer::const_iterator sge::d3d::vertex_buffer::begin() const
{
	return create_iterator(const_pointer(lock_dest));
}

sge::d3d::vertex_buffer::iterator sge::d3d::vertex_buffer::end()
{
	return create_iterator(lock_dest + size());
}

sge::d3d::vertex_buffer::const_iterator sge::d3d::vertex_buffer::end() const
{
	return create_iterator(const_pointer(lock_dest + size()));
}

sge::d3d::vertex_buffer::reverse_iterator sge::d3d::vertex_buffer::rbegin()
{
	return reverse_iterator(end());
}

sge::d3d::vertex_buffer::const_reverse_iterator sge::d3d::vertex_buffer::rbegin() const
{
	return const_reverse_iterator(end());
}

sge::d3d::vertex_buffer::reverse_iterator sge::d3d::vertex_buffer::rend()
{
	return reverse_iterator(begin());
}

sge::d3d::vertex_buffer::const_reverse_iterator sge::d3d::vertex_buffer::rend() const
{
	return const_reverse_iterator(begin());
}

sge::d3d::vertex_buffer::iterator sge::d3d::vertex_buffer::create_iterator(const pointer data) const
{
	return iterator(data,d3d_format.stride(),d3d_format.get_offset_info());
}

sge::d3d::vertex_buffer::const_iterator sge::d3d::vertex_buffer::create_iterator(const const_pointer data) const
{
	return const_iterator(data,d3d_format.stride(),d3d_format.get_offset_info());
}

void sge::d3d::vertex_buffer::lock(const lock_flag_t flags, const size_type first, const size_type count)
{
	// TODO: convert here too?
	if(lock_dest)
		throw std::logic_error("d3d::vertex_buffer::lock() you have to unlock first!");
	void* p = 0;
	const DWORD lflags = convert_lock_flags(flags,flags);
	if(buffer->Lock(first*get_stride(),count*get_stride(),&p,lflags) != D3D_OK)
		throw std::runtime_error("Cannot lock d3d vertex buffer!");
	lock_dest = static_cast<pointer>(p);
}

void sge::d3d::vertex_buffer::unlock()
{
	if(!lock_dest)
		throw std::logic_error("d3d::vertex_buffer::unlock() you have to lock first!");

	if(get_vertex_format().uses(VU_Diffuse))
		for(iterator it = begin(); it != end(); ++it)
			it->diffuse() = rgba_to_argb(it->diffuse());
	
	if(buffer->Unlock() != D3D_OK)
		throw std::runtime_error("Cannot unlock d3d vertex buffer!");
	lock_dest = 0;
}

void sge::d3d::vertex_buffer::resize(const size_type newsize)
{
	if(lock_dest)
		throw std::logic_error("d3d::vertex_buffer::resize() you have to unlock before resizing!");

	sz = newsize;
	init(0);
}

void sge::d3d::vertex_buffer::on_loss()
{
	buffer = 0;
}

void sge::d3d::vertex_buffer::on_reset()
{
	init();
}

sge::d3d::vertex_buffer::size_type sge::d3d::vertex_buffer::size() const
{
	return sz;
}

sge::vertex_size sge::d3d::vertex_buffer::stride() const
{
	return d3d_format.get_stride();
}

sge::resource_flag_t sge::d3d::vertex_buffer::flags() const
{
	return _flags;
}

sge::d3d::vertex_buffer::pointer sge::d3d::vertex_buffer::data()
{
	return lock_dest;
}

sge::d3d::vertex_buffer::const_pointer sge::d3d::vertex_buffer::data() const
{
	return lock_dest;
}

const sge::vertex_format& sge::d3d::vertex_buffer::get_vertex_format() const
{
	return format;
}
