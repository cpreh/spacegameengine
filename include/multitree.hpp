/////////////////////////////////////////////////////////////////////////////
//
// This generic tree container is the property of Justin Gottschlich. It may 
// be used freely in commercial software or non-commercial software without 
// explicit permission from Mr. Gottschlich. However this header file comment 
// must always appear in this header file in its entirety.
//
// You may use this source code free of charge in any environment, pending 
// you e-mail Justin (justin@nodeka.com) so he is aware of how the tree 
// container is being used and send updates as they are made.
//
// (c) 1999-2005 Justin Gottschlich
//
/////////////////////////////////////////////////////////////////////////////

#ifndef SGE_MULTITREE_HPP_INCLUDED
#define SGE_MULTITREE_HPP_INCLUDED

#include <cstddef>
#include <memory>
#include <iterator>

namespace sge 
{

/////////////////////////////////////////////////////////////////////////////
// multitree_iterator forward declaration
/////////////////////////////////////////////////////////////////////////////
template <typename T, typename A> class multitree_iterator;

/////////////////////////////////////////////////////////////////////////////
// multitree pair object definition
/////////////////////////////////////////////////////////////////////////////
template <typename T, typename A = std::allocator<T> > class multitree
{
public:

	typedef multitree_iterator<T,A> iterator;
	typedef const multitree_iterator<T,A> const_iterator;

private:

	// Class data
	mutable T data_;

	// What level are we on?
	mutable std::size_t level_;
	mutable std::size_t size_;

	// Nobody gets any access to this
	mutable multitree *next_;
	mutable multitree *prev_;
	mutable multitree *out_;
	mutable multitree *in_;

	//////////////////////////////////////////////////////////////////////////
	// Removes a link to a node ... doesn't destroy the CTree, just rips it
	// out of it's current location. This is used so it can be placed elsewhere
	// without trouble.
	//////////////////////////////////////////////////////////////////////////
	void disconnect_()
	{
		// unlink this from the master node
		if (this->out_ != 0) {

			multitree *out = this->out_;

			// Decrement the size of the outter level
			--(out->size_);

			if (out->in_ == this) {
				if (0 == this->next_) {
					// If this is the last node of this level, zap the hidden node
					delete this->prev_;
					out->in_ = 0;
				}
				else {
					// Otherwise, just reattatch the head node to the next node
					this->prev_->next_ = this->next_;
					this->next_->prev_ = this->prev_;
					out->in_ = this->next_;
				}
			}
			else {
				// We should be able to do this absolutely.
				this->prev_->next_ = this->next_;
				if (0 != this->next_) this->next_->prev_ = this->prev_;
			}
		}
		// Point to nothing
		this->next_ = this->prev_ = 0;
	}

	//////////////////////////////////////////////////////////////////////////
	// End of the multitree list, private only
	//////////////////////////////////////////////////////////////////////////
	const multitree* end_() const { return 0; }

	//////////////////////////////////////////////////////////////////////////
	// Does the actual insert into the multitree
	//////////////////////////////////////////////////////////////////////////
	multitree& i_insert(multitree *inTree, multitree *level, bool (*pObj)(const T&, const T&))
	{
		// Do NOT move this line beyond this point. The reason is because we must
		// check to see if the node exists here because we may be removing the ONLY
		// node in the multitree. If it is then 0 == level->in_. DO NOT REMOVE THIS
		//if (false == level->mDuplicates) 

		// if there's no inner multitree, make it
		if (0 == level->in_) {
			// Dummy node, create it
			multitree *temp = new multitree;
			temp->next_ = inTree;
			inTree->prev_ = temp;
			level->in_ = inTree;
		}
		else {

			multitree *temp = level->in_->prev_;

			while (true) {
				if (0 == temp->next_) {
					temp->next_ = inTree;
					inTree->prev_ = temp;
					break;
				}
				else if ( pObj(inTree->data(), temp->next_->data()) ) {

					multitree *hold = temp->next_;

					// temp -> inTree -> hold
					temp->next_ = inTree;
					inTree->next_ = hold;

					// temp <- inTree <- hold
					hold->prev_ = inTree;
					inTree->prev_ = temp;

					// If we just inserted on the first node, we need to make sure
					// the in pointer goes to inTree
					if (hold == level->in_) level->in_ = inTree;
					break;
				}
				temp = temp->next_;
			}
		}

		inTree->out_ = level;
		++(level->size_);

		inTree->level_ = level->level() + 1;
		return (*inTree);
	}

	//////////////////////////////////////////////////////////////////////////
	multitree& i_push_back(multitree *inTree, multitree *level)
	{
		// if there's no inner tree, make it
		if (0 == level->in_) 
		{
			// Dummy node, create it
			multitree *temp = new multitree;
			temp->next_ = inTree;
			inTree->prev_ = temp;
			level->in_ = inTree;
		}
		else 
		{
			multitree *temp = level->in_->prev_;

			while (true) {
				if (0 == temp->next_) {
					temp->next_ = inTree;
					inTree->prev_ = temp;
					break;
				}
				temp = temp->next_;
			}
		}

		inTree->out_ = level;
		++(level->size_);

		inTree->level_ = level->level() + 1;
		return *inTree;
	}

	//////////////////////////////////////////////////////////////////////////
	multitree& i_push_front(multitree *inTree, multitree *level)
	{
		// if there's no inner multitree, make it
		if (0 == level->in_) 
		{
			// Dummy node, create it
			multitree *temp = new multitree;
			temp->next_ = inTree;
			inTree->prev_ = temp;
			level->in_ = inTree;
		}
		else 
		{
			multitree *temp = level->in_->prev_;

			multitree *hold = temp->next_;
			// temp -> inTree -> hold
			temp->next_ = inTree;
			inTree->next_ = hold;
			// temp <- inTree <- hold
			hold->prev_ = inTree;
			inTree->prev_ = temp;
			// If we just inserted on the first node, we need to make sure
			// the in pointer goes to inTree
			if (hold == level->in_) level->in_ = inTree;
		}

		inTree->out_ = level;
		++(level->size_);

		inTree->level_ = level->level() + 1;
		return *inTree;
	}

	//////////////////////////////////////////////////////////////////////////
	// No function object
	//////////////////////////////////////////////////////////////////////////
	multitree& i_insert(multitree *inTree, multitree *level)
	{
		// Do NOT move this line beyond this point. The reason is because we must
		// check to see if the node exists here because we may be removing the ONLY
		// node in the multitree. If it is then 0 == level->in_. DO NOT REMOVE THIS

		// if there's no inner multitree, make it
		if (0 == level->in_) {
			// Dummy node, create it
			multitree *temp = new multitree;
			temp->next_ = inTree;
			inTree->prev_ = temp;
			level->in_ = inTree;
		}
		else {

			multitree *temp = level->in_->prev_;

			while (true) {
				if (0 == temp->next_) {
					temp->next_ = inTree;
					inTree->prev_ = temp;
					break;
				}
				else if ( inTree->data() < temp->next_->data() ) {

					multitree *hold = temp->next_;

					// temp -> inTree -> hold
					temp->next_ = inTree;
					inTree->next_ = hold;

					// temp <- inTree <- hold
					hold->prev_ = inTree;
					inTree->prev_ = temp;

					// If we just inserted on the first node, we need to make sure
					// the in pointer goes to inTree
					if (hold == level->in_) level->in_ = inTree;
					break;
				}
				temp = temp->next_;
			}
		}

		inTree->out_ = level;
		++(level->size_);

		inTree->level_ = level->level() + 1;
		return (*inTree);
	}

protected:

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	std::size_t size(const multitree& in) const { return in.size(); }
	std::size_t level(const multitree& in) const { return in.level(); }

	//////////////////////////////////////////////////////////////////////////
	// Points to the beginning of the list and sets the current
	//////////////////////////////////////////////////////////////////////////
	iterator begin(const multitree& in) const { return iterator( *(in.in_) ); }

	//////////////////////////////////////////////////////////////////////////
	// Notice that we're returning a const multitree* here and not an iterator.
	// This is because the iterator itself has a member to a pointer. Doing
	// an iterator constructor here would be less efficient than just 
	// returning a multitree* which can be assigned internally inside the iterator
	// operator--(). Also because no one can call prev from a multitree itself
	// (this is protected), we don't have to worry about safety issues except
	// for iterator safety.
	//////////////////////////////////////////////////////////////////////////
	const multitree* prev(const multitree& in) const { return (in.prev_); }

	//////////////////////////////////////////////////////////////////////////
	// Notice that we're returning a const multitree* here and not an iterator.
	// This is because the iterator itself has a member to a pointer. Doing
	// an iterator constructor here would be less efficient than just 
	// returning a multitree* which can be assigned internally inside the iterator
	// operator++(). Also because no one can call prev from a multitree itself
	// (this is protected), we don't have to worry about safety issues except
	// for iterator safety.
	//////////////////////////////////////////////////////////////////////////
	const multitree* next(const multitree& in) const { return (in.next_); }

	//////////////////////////////////////////////////////////////////////////
	iterator in(const multitree& in) const { return iterator( *(in.in_) ); }

	//////////////////////////////////////////////////////////////////////////
	iterator out(const multitree& in) const { return iterator( *(in.out_) ); }

public:

	//////////////////////////////////////////////////////////////////////////
	// Default constructor
	//////////////////////////////////////////////////////////////////////////
	multitree() : level_(0), size_(0),next_(0), prev_(0), out_(0), in_(0)  {}

	//////////////////////////////////////////////////////////////////////////
	// Paired <T> constructor
	//////////////////////////////////////////////////////////////////////////
	multitree(const T &inT) : data_(inT),level_(0), size_(0),  next_(0), prev_(0), out_(0),in_(0)   {}

	//////////////////////////////////////////////////////////////////////////
	// operator==, expects operator== has been written for both t and u
	//////////////////////////////////////////////////////////////////////////
	bool operator==(const multitree &inTree) const
	{
		if (this->data_ == inTree.data_) return true;
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	// The operator= which is a real copy, hidden and undefined
	//////////////////////////////////////////////////////////////////////////
	const multitree& operator=(const multitree& in)
	{
		this->clear();

		this->data_ = in.data_;
		this->copy_tree(in);

		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	iterator tree_iterator() const { return iterator( *(this) ); }
	iterator tree_iterator() { return iterator( *(this) ); }

	//////////////////////////////////////////////////////////////////////////
	// copy constructor - now visible
	//////////////////////////////////////////////////////////////////////////
	multitree(const multitree &in) : data_(in.data_),level_(0), size_(0), next_(0), prev_(0), out_(0),in_(0)
		 { *this = in; }

	//////////////////////////////////////////////////////////////////////////
	// destructor -- cleans out all branches, destroyed entire multitree
	//////////////////////////////////////////////////////////////////////////
	virtual ~multitree()
	{
		// Disconnect ourselves -- very important for decrementing the
		// size of our parent
		this->disconnect_();

		// Now get rid of our children -- but be smart about it,
		// right before we destroy it set it's out_ to 0
		// that way Disconnect fails immediately -- much faster

		if (this->size() > 0) {
			multitree *cur = this->in_, *prev = this->in_->prev_;

			// Delete the head node
			prev->out_ = 0;
			delete prev;

			for (; this->size_ > 0; --this->size_) {

				prev = cur;
				cur = cur->next_;

				prev->out_ = 0;
				delete prev;
			}
		}
	}


	//////////////////////////////////////////////////////////////////////////
	void copy_tree(const multitree& in)
	{
		// for each branch iterate through all nodes and copy them
		for (iterator i = in.begin(); in.end() != i; ++i) {
			iterator inserted = this->push_back(i.data());

			// for each node, see if there are inners - if so, copy those too
			if (i.size() != 0) inserted.tree_ptr()->copy_tree(*i.tree_ptr());
		}
	}

	iterator append_subtree(const multitree &in)
	{
		iterator root = push_back(in.data());
		root.tree_ptr()->copy_tree(in);
		return root;
	}

	//////////////////////////////////////////////////////////////////////////
	// Returns the first element of our multitree
	//////////////////////////////////////////////////////////////////////////
	iterator begin() const { return iterator( *(this->in_) ); }
	iterator begin() { return iterator( *(this->in_) ); }

	//////////////////////////////////////////////////////////////////////////
	// Returns end_of_iterator
	//////////////////////////////////////////////////////////////////////////
	const iterator& end() const { return multitree::iterator::end_iterator(); }

	//////////////////////////////////////////////////////////////////////////
	// Returns the first element of our multitree
	//////////////////////////////////////////////////////////////////////////
	iterator in() const { return iterator( *(this->in_) ); }
	iterator in() { return iterator( *(this->in_) ); }

	//////////////////////////////////////////////////////////////////////////
	// Returns an iterator which steps out one level
	//////////////////////////////////////////////////////////////////////////
	iterator out() const { return iterator( *(this->out_) ); }
	iterator out() { return iterator( *(this->out_) ); }

	//////////////////////////////////////////////////////////////////////////
	// much like destructor with the exception that empty can be called from
	// an iterator, calling delete on an iterator will only delete the iterator
	// calling empty from an iterator will delete the multitree it's iterating.
	//////////////////////////////////////////////////////////////////////////
	void clear()
	{
		// Now get rid of our children -- but be smart about it,
		// right before we destroy it set it's out_ to 0
		// that way disconnect_ fails immediately, much faster
		if (this->size() > 0) {
			multitree *cur = this->in_, *prev = this->in_->prev_;

			// Delete the head node
			prev->out_ = 0;
			delete prev;

			for (; this->size_ > 0; --this->size_) {

				prev = cur;
				cur = cur->next_;

				prev->out_ = 0;
				delete prev;
			}

			// Set our inner pointer and our size to 0
			this->in_ = 0;
			this->size_ = 0;
		}
	}

	T& operator*() { return this->data_; }
	const T& operator*() const { return this->data_; }
	T& data() { return this->data_; }
	const T& data() const { return this->data_; }

	const T& data(const T &inData) { return (this->data_ = inData); }

	//////////////////////////////////////////////////////////////////////////
	std::size_t level() const { return (this->level_); }

	//////////////////////////////////////////////////////////////////////////
	std::size_t size() const { return this->size_; }

	//////////////////////////////////////////////////////////////////////////
	iterator push_front(const T &inT)
	{
		multitree *createdTree = new multitree(inT);
		return iterator(i_push_front(createdTree, this));
	}

	//////////////////////////////////////////////////////////////////////////
	iterator push_back(const T &inT)
	{
		multitree *createdTree = new multitree(inT);
		return iterator(i_push_back(createdTree, this));
	}

	iterator push_back(const multitree &inT)
	{
		return append_subtree(inT);
	}

	//////////////////////////////////////////////////////////////////////////
	// This creates a new multitree node from parameters and then inserts it
	// Also takes a function object which can be used for sorting on inserts
	//////////////////////////////////////////////////////////////////////////
	iterator insert(const T &inT, bool (*pObj)(const T&, const T&))
	{
		multitree *createdTree = new multitree(inT);
		return iterator(i_insert(createdTree, this, pObj));
	}

	//////////////////////////////////////////////////////////////////////////
	iterator insert(const iterator &i)
	{
		multitree *createdTree = new multitree(i.data());
		return iterator(i_insert(createdTree, this));
	}

	//////////////////////////////////////////////////////////////////////////
	// Insert with no function object
	//////////////////////////////////////////////////////////////////////////
	iterator insert(const T &inT)
	{
		multitree *createdTree = new multitree(inT);
		return iterator(i_insert(createdTree, this));
	}

	//////////////////////////////////////////////////////////////////////////
	// This takes an existing node, disconnects it from wherever it is, and then
	// inserts it into a different multitree. This does not create a new node from the
	// passed in data.
	//////////////////////////////////////////////////////////////////////////
	iterator reinsert(multitree *in, bool (*pObj)(const T&, const T&))
	{
		in->disconnect_();
		return iterator(i_insert(in, this, pObj));
	}

	//////////////////////////////////////////////////////////////////////////
	// Reinsert with no function object
	//////////////////////////////////////////////////////////////////////////
	iterator reinsert(multitree *in)
	{
		in->disconnect_();
		return iterator(i_insert(in, this));
	}

	//////////////////////////////////////////////////////////////////////////
	// removes first matching t, returns true if found, otherwise false
	//////////////////////////////////////////////////////////////////////////
	bool remove(const T &inData)
	{
		if (multitree *temp = this->in_) {
			do {
				if (inData == temp->data_) {
					delete temp;
					return true;
				}
			} while (0 != (temp = temp->next_) );
		}
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	bool erase(const iterator& i)
	{
		if (multitree *temp = this->in_) {
			do {
				if (temp == i.tree_ptr()) {
					delete temp;
					return true;
				}
			} while (0 != (temp = temp->next_) );
		}
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	iterator operator[](std::size_t loc) const
	{
		multitree *temp;
		for (temp = this->in_; loc > 0; --loc) temp = temp->next_;
		return iterator(*temp);
	}

	//////////////////////////////////////////////////////////////////////////
	iterator operator[](std::size_t loc)
	{
		multitree *temp;
		for (temp = this->in_; loc > 0; --loc) temp = temp->next_;
		return iterator(*temp);
	}

	//////////////////////////////////////////////////////////////////////////
	iterator find(const T &inT) const
	{ return find(inT, iterator(*this->in_)); }

	//////////////////////////////////////////////////////////////////////////
	iterator find(const T &inT, bool (*obj)(const T&, const T&)) const
	{ return find(inT, iterator(*this->in_), obj); }

	//////////////////////////////////////////////////////////////////////////
	iterator tree_find_depth(const T &inT) const 
	{ return tree_find_depth(inT, iterator(*this->in_)); }

	//////////////////////////////////////////////////////////////////////////
	iterator tree_find_depth(const T &inT, bool (*obj)(const T&, const T&)) const
	{ return tree_find_depth(inT, iterator(*this->in_), obj); }

	//////////////////////////////////////////////////////////////////////////
	iterator tree_find_breadth(const T &inT) const
	{ return tree_find_breadth(in, iterator(*this->in_)); }

	//////////////////////////////////////////////////////////////////////////
	iterator tree_find_breadth(const T &inT, bool (*obj)(const T&, const T&)) const
	{ return tree_find_breadth(inT, iterator(*this->in_), obj); }

	//////////////////////////////////////////////////////////////////////////
	// internal_only interface, can't be called even with derived objects due
	// to its direct reference to multitree's private members
	//////////////////////////////////////////////////////////////////////////
	iterator find(const T &inT, const iterator &iter) const
	{
		if (multitree *temp = iter.tree_ptr()) {
			do {
				if (inT == temp->data_) return ( iterator(*temp) );
			} while (0 != (temp = temp->next_) );
		}
		return multitree::iterator::end_iterator();
	}

	//////////////////////////////////////////////////////////////////////////
	iterator find(const T &inT, const iterator &iter, bool (*obj)(const T&, const T&)) const
	{
		if (multitree *temp = iter.tree_ptr()) {
			do {
				if ( obj(inT, temp->data_) ) return ( iterator(*temp) );
			} while (0 != (temp = temp->next_) );
		}
		return multitree::iterator::end_iterator();
	}

	//////////////////////////////////////////////////////////////////////////
	iterator tree_find_depth(const T &inT, const iterator &iter) const
	{
		if (multitree *temp = iter.tree_ptr()) {
			do {
				if (inT == temp->data_) return iterator(*temp);
				// do a depth search, search it for inT
				iterator i = temp->tree_find_depth(inT);
				if (i != multitree::iterator::end_iterator()) return i;
			} while (0 != (temp = temp->next_) );
		}
		return multitree::iterator::end_iterator();
	}

	//////////////////////////////////////////////////////////////////////////
	iterator tree_find_depth(const T &inT, const iterator &iter, bool (*obj)(const T&, const T&)) const
	{
		if (multitree *temp = iter.tree_ptr()) {
			do {
				if ( obj(inT, temp->data_) ) return ( iterator(*temp) );
				// do a depth search, search it for inT
				iterator i = temp->tree_find_depth(inT, obj);
				if (i != multitree::iterator::end_iterator()) return i;
			} while (0 != (temp = temp->next_) );
		}
		return multitree::iterator::end_iterator();
	}

	//////////////////////////////////////////////////////////////////////////
	iterator tree_find_breadth(const T &inT, const iterator &iter) const
	{
		// search the entire level for a find first
		if (multitree *temp = iter.tree_ptr()) {
			do {
				if (inT == temp->data_) return iterator(*temp);
			} while (0 != (temp = temp->next_) );

			// now search each branch for the find within it
			temp = iter.tree_ptr();
			do {
				iterator i = temp->tree_find_breadth(inT);
				if (i != multitree::iterator::end_iterator()) return i;
			} while (0 != (temp = temp->next_) );
		}
		return multitree::iterator::end_iterator();
	}

	//////////////////////////////////////////////////////////////////////////
	iterator tree_find_breadth(const T &inT, const iterator &iter, bool (*obj)(const T&, const T&)) const
	{
		// search the entire level for a find first
		if (multitree *temp = iter.tree_ptr()) {
			do {
				if ( obj(inT, temp->data_) ) return iterator(*temp);
			} while (0 != (temp = temp->next_) );

			// now search each branch for the find within it
			temp = iter.tree_ptr();
			do {
				iterator i = temp->tree_find_breadth(inT, obj);
				if (i != multitree::iterator::end_iterator()) return i;
			} while (0 != (temp = temp->next_) );
		}
		return multitree::iterator::end_iterator();
	}
};

/////////////////////////////////////////////////////////////////////////////
// Iterator for the multitree
//
// Derived from multitree<> only so iterator can access multitree's protected 
// methods directly and implement them in the way they make sense for the 
// iterator
//
// The actual multitree base members are never used (nor could they be since they
// are private to even iterator). When a multitree object is created an "iterator"
// object is automatically created of the specific type. Thus forming the
// perfect relationship between the multitree and the iterator, also keeping the
// template types defined on the fly for the iterator based specifically on
// the multitree types which are being created.
/////////////////////////////////////////////////////////////////////////////
template <typename T, typename A>
class multitree_iterator : private multitree<T,A>
{
private:
	typedef multitree<T,A> TreeType;

	mutable TreeType *current_;

	static multitree_iterator end_of_iterator;

	//////////////////////////////////////////////////////////////////////////
	// unaccessible from the outside world
	//////////////////////////////////////////////////////////////////////////
	TreeType* operator&();
	const TreeType* operator&() const;

public:

	typedef typename TreeType::iterator iterator;

	TreeType* tree_ptr() const { return current_; }
	TreeType& tree_ref() const { return *current_; }

	//////////////////////////////////////////////////////////////////////////
	// Returns the end_of_iterator for this <T,U,V> layout, this really speeds
	// up things like if (iter != multitree.end() ), for (;iter != multitree.end(); )
	//////////////////////////////////////////////////////////////////////////
	static const iterator& end_iterator() { return end_of_iterator; }

	//////////////////////////////////////////////////////////////////////////
	// Default constructor
	//////////////////////////////////////////////////////////////////////////
	multitree_iterator() : current_(0) {}
	
	//////////////////////////////////////////////////////////////////////////
	// Copy constructors for iterators
	//////////////////////////////////////////////////////////////////////////
	multitree_iterator(const multitree_iterator& i) : TreeType(),current_(i.current_) {}

	//////////////////////////////////////////////////////////////////////////
	// Copy constructor for trees
	//////////////////////////////////////////////////////////////////////////
	multitree_iterator(TreeType &tree_ref) : current_(&tree_ref) {}

	//////////////////////////////////////////////////////////////////////////
	// Operator= for iterators
	//////////////////////////////////////////////////////////////////////////
	iterator& operator=(const multitree_iterator& iter)
	{
		this->current_ = iter.current_;
		return (*this);
	}

	//////////////////////////////////////////////////////////////////////////
	// Operator= for iterators
	//////////////////////////////////////////////////////////////////////////
	const iterator& operator=(const multitree_iterator& iter) const
	{
		this->current_ = iter.current_;
		return (*this);
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	iterator operator[](std::size_t loc) const
	{ return (*this->current_)[loc]; }

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	iterator operator[](std::size_t loc)
	{ return (*this->current_)[loc]; }

	//////////////////////////////////////////////////////////////////////////
	// Operator= for trees
	//////////////////////////////////////////////////////////////////////////
	const iterator& operator=(const TreeType& rhs) const
	{
		this->current_ = &(const_cast< TreeType& >(rhs) );
		return (*this);
	}

	//////////////////////////////////////////////////////////////////////////
	// Destructor
	//////////////////////////////////////////////////////////////////////////
	~multitree_iterator() {};

	//////////////////////////////////////////////////////////////////////////
	// Operator equals
	//////////////////////////////////////////////////////////////////////////
	bool operator==(const multitree_iterator& rhs) const
	{
		return this->current_ == rhs.current_;
	}

	//////////////////////////////////////////////////////////////////////////
	// Operator not equals
	//////////////////////////////////////////////////////////////////////////
	bool operator!=(const multitree_iterator& rhs) const
	{ return !(*this == rhs); }

	//////////////////////////////////////////////////////////////////////////
	// operator++, prefix
	//////////////////////////////////////////////////////////////////////////
	const iterator& operator++() const
	{
		this->current_ = ( const_cast< TreeType* >
			( this->TreeType::next( *current_ ) ) );
		return (*this);
	}

	//////////////////////////////////////////////////////////////////////////
	// operator++, postfix
	//////////////////////////////////////////////////////////////////////////
	iterator operator++(int) const
	{
		iterator iTemp = *this;
		++(*this);
		return (iTemp);
	}

	//////////////////////////////////////////////////////////////////////////
	// operator--
	//////////////////////////////////////////////////////////////////////////
	const iterator& operator--() const
	{
		this->current_ = ( const_cast< TreeType* >
			( this->TreeType::prev( *current_ ) ) );
		return (*this);
	}

	//////////////////////////////////////////////////////////////////////////
	// Begin iteration through the multitree
	//////////////////////////////////////////////////////////////////////////
	iterator begin() const { return this->TreeType::begin( *current_ ); }
	iterator begin() { return this->TreeType::begin( *current_ ); }

	//////////////////////////////////////////////////////////////////////////
	// Return the in iterator of this multitree
	//////////////////////////////////////////////////////////////////////////
	iterator in() const { return this->TreeType::in( *current_ ); }
	iterator in() { return this->TreeType::in( *current_ ); }

	//////////////////////////////////////////////////////////////////////////
	// Return the out iterator of this multitree
	//////////////////////////////////////////////////////////////////////////
	iterator out() const { return this->TreeType::out( *current_ ); }
	iterator out() { return this->TreeType::out( *current_ ); }

	//////////////////////////////////////////////////////////////////////////
	// Are we at the end?
	//////////////////////////////////////////////////////////////////////////
	const iterator& end() const { return this->TreeType::end(); }

	//////////////////////////////////////////////////////////////////////////
	// Return the next guy
	//////////////////////////////////////////////////////////////////////////
	iterator next() const 
	{ return iterator (* const_cast< TreeType* >( this->TreeType::next( *current_ ) ) ); }

	//////////////////////////////////////////////////////////////////////////
	iterator push_back(const T& t)
	{ return this->current_->TreeType::push_back(t); }

	//////////////////////////////////////////////////////////////////////////
	iterator push_front(const T& t)
	{ return this->current_->TreeType::push_front(t); }

	//////////////////////////////////////////////////////////////////////////
	// Insert into the iterator's mTree
	//////////////////////////////////////////////////////////////////////////
	iterator insert(const T& t)
	{ return this->current_->TreeType::insert(t); }

	//////////////////////////////////////////////////////////////////////////
	// Insert into the iterator's mTree (with a function object)
	//////////////////////////////////////////////////////////////////////////
	iterator insert(const T& t, bool (*obj)(const T&, const T&))
	{ return this->current_->TreeType::insert(t, obj); }

	//////////////////////////////////////////////////////////////////////////
	// This takes an existing node, disconnects it from wherever it is, and then
	// inserts it into a different multitree. This does not create a new node from the
	// passed in data.
	//////////////////////////////////////////////////////////////////////////
	iterator reinsert(const iterator &in, bool (*obj)(const T&, const T&))
	{ return this->current_->TreeType::reinsert(in.current_, obj); }

	//////////////////////////////////////////////////////////////////////////
	// Reinsert with no function object
	//////////////////////////////////////////////////////////////////////////
	iterator reinsert(const iterator &in)
	{ return this->current_->TreeType::reinsert(in.current_); }

	//////////////////////////////////////////////////////////////////////////
	// get the data of the iter
	//////////////////////////////////////////////////////////////////////////
	T& operator*() { return this->current_->data(); }
	const T& operator*() const { return this->current_->data(); }
	T& data() { return this->current_->data(); }
	const T& data() const { return this->current_->data(); }

	//////////////////////////////////////////////////////////////////////////
	// sets and retrieves the t and u members of the pair
	//////////////////////////////////////////////////////////////////////////
	const T& data(const T &inData) const { return this->current_->data(inData); }

	//////////////////////////////////////////////////////////////////////////
	// Get the size of the current tree_iter
	//////////////////////////////////////////////////////////////////////////
	std::size_t size() const { return this->TreeType::size( *current_ ); }

	//////////////////////////////////////////////////////////////////////////
	std::size_t level() const { return this->TreeType::level( *current_ ); }

	//////////////////////////////////////////////////////////////////////////
	// Removes the first instance of T in the multitree
	//////////////////////////////////////////////////////////////////////////
	bool remove(const T &inT) { return current_->remove(inT); }

	//////////////////////////////////////////////////////////////////////////
	// Finds the first instance of T in the multitree
	//////////////////////////////////////////////////////////////////////////
	iterator find(const T &inT) const { return current_->find(inT); }

	iterator find(const T &inT, bool (*obj)(const T&, const T&)) const
	{ return current_->find(inT, obj); }

	iterator tree_find_depth(const T &inT) const { return current_->tree_find_depth(inT); }

	iterator tree_find_depth(const T &inT, bool (*obj)(const T&, const T&)) const
	{ return current_->tree_find_depth(inT, obj); }

	iterator tree_find_breadth(const T &inT) const { return current_->tree_find_breadth(inT); }

	iterator tree_find_breadth(const T &inT, bool (*obj)(const T&, const T&)) const
	{ return current_->tree_find_breadth(inT, obj); }

	//////////////////////////////////////////////////////////////////////////
	// Finds the next instance of T based on the iterator passed in
	//////////////////////////////////////////////////////////////////////////
	iterator find(const T &inT, const iterator &iter) const
	{ return current_->find(inT, iter); }

	iterator find(const T &inT, const iterator &iter, bool (*obj)(const T&, const T&)) const
	{ return current_->find( inT, iter, obj ); }

	iterator tree_find_depth(const T &inT, const iterator &iter) const
	{ return current_->tree_find_depth(inT, iter); }

	iterator tree_find_depth(const T &inT, const iterator &iter, bool (*obj)(const T&, const T&)) const
	{ return current_->tree_find_depth( inT, iter, obj ); }

	iterator tree_find_breadth(const T &inT, const iterator &iter) const
	{ return current_->tree_find_breadth(inT, iter); }

	iterator tree_find_breadth(const T &inT, const iterator &iter, bool (*obj)(const T&, const T&)) const
	{ return current_->tree_find_breadth( inT, iter, obj ); }

	//////////////////////////////////////////////////////////////////////////
	// Empty this entire multitree
	//////////////////////////////////////////////////////////////////////////
	void clear_tree() { delete this->current_; this->current_ = 0; }

	//////////////////////////////////////////////////////////////////////////
	// Empty this multitree's children
	//////////////////////////////////////////////////////////////////////////
	void clear_children() { this->current_->clear(); }
};

//////////////////////////////////////////////////////////////////////////
// Static iterator initialization
//////////////////////////////////////////////////////////////////////////
template <typename T, typename A>
multitree_iterator<T,A> multitree_iterator<T,A>::end_of_iterator;

}

#endif // tree_header_file
