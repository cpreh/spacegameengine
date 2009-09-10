#ifndef SGE_THREAD_FUTURE_SHARED_OBJECT_HPP_INCLUDED
#define SGE_THREAD_FUTURE_SHARED_OBJECT_HPP_INCLUDED

#include <sge/cerr.hpp>

namespace sge
{
namespace thread
{
namespace future
{
template<typename T>
class shared_object
{
private:
	typedef shared_ptr< detail::object<T> > object_ptr;
	typedef typename boost::add_reference<T>::type reference;

	shared_object(
		unique_object<T> &);
	shared_object &operator=(
		unique_object<T> &);
public:
	shared_object();
	shared_object(
		object_ptr);
	shared_object(
		shared_object const &);
	shared_object(
		boost::detail::thread_move_t<shared_object>);
	shared_object(
		boost::detail::thread_move_t<unique_object<T> >);
	shared_object &operator=(
		shared_object const &);
	shared_object &operator=(
		boost::detail::thread_move_t<shared_object>);
	shared_object &operator=(
		boost::detail::thread_move_t<unique_object<T> >);
	operator boost::detail::thread_move_t<shared_object>();
	void swap(
		shared_object &);
	reference get();
	bool try_get(
		reference);
	template<typename Duration>
	bool timed_get(
		reference,
		Duration const&);
	bool timed_get_until(
		reference,
		boost::system_time const&);
	future::state::type state() const;
	bool is_ready() const;
	bool has_exception() const;
	bool has_value() const;
	bool was_moved() const;
	void wait() const;
	template<typename Duration>
	bool timed_wait(
		Duration const&) const;
	bool timed_wait_until(
		boost::system_time const&) const;
private:
	object_ptr object_;
};

template<>
class shared_object<void>
{
private:
	typedef shared_ptr< detail::object<void> > object_ptr;

	shared_object(
		unique_object<void> &);
	shared_object &operator=(
		unique_object<void> &);
public:
	shared_object();
	shared_object(
		object_ptr);
	shared_object(
		shared_object<void> const &);
	shared_object(
		boost::detail::thread_move_t<shared_object>);
	shared_object(
		boost::detail::thread_move_t<unique_object<void> >);
	shared_object &operator=(
		shared_object const &);
	shared_object &operator=(
		boost::detail::thread_move_t<shared_object>);
	shared_object &operator=(
		boost::detail::thread_move_t<unique_object<void> >);
	operator boost::detail::thread_move_t<shared_object>();
	void swap(
		shared_object &);
	void get();
	future::state::type state() const;
	bool is_ready() const;
	bool has_exception() const;
	bool has_value() const;
	bool was_moved() const;
	void wait() const;
	template<typename Duration>
	bool timed_wait(
		Duration const&) const;
	bool timed_wait_until(
		boost::system_time const&) const;
private:
	object_ptr object_;
};
}
}
}

template<typename T>
sge::thread::future::shared_object<T>::shared_object()
:
	object_()
{
}

template<typename T>
sge::thread::future::shared_object<T>::shared_object(
	shared_object const &_rhs)
:
	object_(
		_rhs.object_)
{
}

template<typename T>
sge::thread::future::shared_object<T>::shared_object(
	object_ptr _object)
:
	object_(
		_object)
{
}

template<typename T>
sge::thread::future::shared_object<T>::shared_object(
	boost::detail::thread_move_t<shared_object> _other)
:
	object_(
		_other->object_)
{
	_other->object_.reset();
}

template<typename T>
sge::thread::future::shared_object<T>::shared_object(
	boost::detail::thread_move_t<unique_object<T> > _other)
:
	object_(
		_other->object_)
{
	_other->object_.reset();
}

template<typename T>
sge::thread::future::shared_object<T> &sge::thread::future::shared_object<T>::operator=(
	shared_object const &_rhs)
{
	object_ = _rhs.object_;
	return *this;
}

template<typename T>
sge::thread::future::shared_object<T> &sge::thread::future::shared_object<T>::operator=(
	boost::detail::thread_move_t<shared_object> _other)
{
	object_ = _other->object_;
	_other->object_.reset();
	return *this;
}

template<typename T>
sge::thread::future::shared_object<T> &sge::thread::future::shared_object<T>::operator=(
	boost::detail::thread_move_t<unique_object<T> > _other)
{
	object_.swap(
		_other->object_);
	_other->object_.reset();
	return *this;
}

template<typename T>
sge::thread::future::shared_object<T>::operator boost::detail::thread_move_t< sge::thread::future::shared_object<T> >()
{
	return 
		boost::detail::thread_move_t<shared_object>(
			*this);
}

template<typename T>
void sge::thread::future::shared_object<T>::swap(
	shared_object &_other)
{
	object_.swap(
		_other);
}

template<typename T>
typename sge::thread::future::shared_object<T>::reference sge::thread::future::shared_object<T>::get()
{
	if (!object_)
		throw uninitialized();
	return object_->get();
}

template<typename T>
bool sge::thread::future::shared_object<T>::try_get(
	reference _dest)
{
	if (!object_)
		throw uninitialized();
	return 
		object_->try_get(
			_dest);
}

template<typename T>
template<typename Duration>
bool sge::thread::future::shared_object<T>::timed_get(
	reference _dest,
	Duration const &_time)
{
	return 
		timed_get_until(
			_dest,
			boost::get_system_time()+_time);
}

template<typename T>
bool sge::thread::future::shared_object<T>::timed_get_until(
	reference _dest,
	boost::system_time const &_time)
{
	if (!object_)
		throw uninitialized();
	return 
		object_->timed_get_until(
			_dest,
			_time);
}

template<typename T>
sge::thread::future::state::type sge::thread::future::shared_object<T>::state() const
{
	if (!object_)
		throw uninitialized();
	return object_->state();
}

template<typename T>
bool sge::thread::future::shared_object<T>::is_ready() const
{
	return state() == sge::thread::future::state::ready;
}

template<typename T>
bool sge::thread::future::shared_object<T>::has_exception() const
{
	if(!object_)
		return false;
	boost::lock_guard<boost::mutex> guard(
		object_->mutex_);
	return 
		object_->done_ && object_->exception_;
}

template<typename T>
bool sge::thread::future::shared_object<T>::has_value() const
{
	if(!object_)
		return false;
	boost::lock_guard<boost::mutex> guard(
		object_->mutex_);
	return 
		object_->done_ && object_->result_;
}

template<typename T>
bool sge::thread::future::shared_object<T>::was_moved() const
{
	return state() == sge::thread::future::state::moved;
}

template<typename T>
void sge::thread::future::shared_object<T>::wait() const
{
	sge::cerr << "warte jetzt\n";
	if (!object_)
	{
		sge::cerr << "och noe\n";
		throw uninitialized();
	}
	sge::cerr << "objekt ist gültig\n";
	object_->wait();
}

template<typename T>
template<typename Duration>
bool sge::thread::future::shared_object<T>::timed_wait(
	Duration const& _time) const
{
	return
		timed_wait_until(
			boost::get_system_time()+_time);
}

template<typename T>
bool sge::thread::future::shared_object<T>::timed_wait_until(
	boost::system_time const& _time) const
{
	if (object_)
		throw uninitialized();
	return 
		object_->timed_wait_until(
			_time);
}

sge::thread::future::shared_object<void>::shared_object(
	object_ptr _object)
:
	object_(
		_object)
{
}

sge::thread::future::shared_object<void>::shared_object()
{
}

sge::thread::future::shared_object<void>::shared_object(
	boost::detail::thread_move_t<shared_object> _other)
:
	object_(
		_other->object_)
{
	_other->object_.reset();
}

sge::thread::future::shared_object<void>::shared_object(
	boost::detail::thread_move_t<unique_object<void> > _other)
:
	object_(
		_other->object_)
{
	_other->object_.reset();
}

sge::thread::future::shared_object<void>& sge::thread::future::shared_object<void>::operator=(
	shared_object const &_other)
{
	object_ = _other.object_;
	return *this;
}

sge::thread::future::shared_object<void>& sge::thread::future::shared_object<void>::operator=(
	boost::detail::thread_move_t<shared_object> _other)
{
	object_ = _other->object_;
	_other->object_.reset();
	return *this;
}

sge::thread::future::shared_object<void>::operator boost::detail::thread_move_t<shared_object>()
{
	return 
		boost::detail::thread_move_t<shared_object>(
			*this);
}

void sge::thread::future::shared_object<void>::swap(
	shared_object& _other)
{
	object_.swap(
		_other.object_);
}

void sge::thread::future::shared_object<void>::get()
{
	if(!object_)
		throw uninitialized();
	object_->get();
}

sge::thread::future::state::type sge::thread::future::shared_object<void>::state() const
{
	if(!object_)
		return sge::thread::future::state::uninitialized;
	return object_->state();
}

bool sge::thread::future::shared_object<void>::is_ready() const
{
	return state() == sge::thread::future::state::ready;
}

bool sge::thread::future::shared_object<void>::has_exception() const
{
	if(!object_)
		return false;
	boost::lock_guard<boost::mutex> guard(
		object_->mutex_);
	return 
		object_->done_ && object_->exception_;
}

bool sge::thread::future::shared_object<void>::has_value() const
{
	if(!object_)
		return false;
	boost::lock_guard<boost::mutex> guard(
		object_->mutex_);
	return 
		object_->done_ && object_->result_;
}

bool sge::thread::future::shared_object<void>::was_moved() const
{
	return state() == sge::thread::future::state::moved;
}

void sge::thread::future::shared_object<void>::wait() const
{
	if(!object_)
		throw uninitialized();
	object_->wait();
}

template<typename Duration>
bool sge::thread::future::shared_object<void>::timed_wait(
	Duration const&_time) const
{
	return 
		timed_wait_until(
			boost::get_system_time()+_time);
}

bool sge::thread::future::shared_object<void>::timed_wait_until(
	boost::system_time const&_time) const
{
	if(!object_)
		throw uninitialized();
	return 
		object_->timed_wait_until(
			_time);
}


#endif // SGE_THREAD_FUTURE_SHARED_OBJECT_HPP_INCLUDED
