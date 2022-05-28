/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:43:51 by silim             #+#    #+#             */
/*   Updated: 2022/05/28 15:49:10 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include "Node.hpp"
# include "MapIterator.hpp"
# include "ReverseIterator.hpp"
# include "IteratorTraits.hpp"
# include "Utils.hpp"
# include "Pair.hpp"
# include <memory>
# include <cstddef>

namespace ft
{
	template < class Key,
			 class T,
			 class Compare = std::less<Key>,
			 class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef Node<value_type>								node;
			typedef	MapIterator<node, value_type>					iterator;
			typedef	MapIterator<node, const value_type>				const_iterator;
			typedef ReverseIterator<iterator>						reverse_iterator;
			typedef ReverseIterator<const_iterator>					const_reverse_iterator;
			typedef ptrdiff_t										difference_type;
			typedef size_t											size_type;
			typedef typename Alloc::template rebind<node>::other	node_allocator;

		public:
			class value_compare
			{
				friend class map;
				protected:
					key_compare		comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()(const value_type& lhs, const value_type& rhs) const
					{
						return comp(lhs.first, rhs.first);
					}
			};

		private:
			key_compare		_compare;
			node_allocator	_allocator;
			size_type		_size;
			node			*_root;
			node			_begin;
			node			_end;

		// Constructor
		public:
			// default
			explicit map(const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type())	:
				_compare(comp), _allocator(alloc), _size(0), _root(0)
			{
				_setup();
			}

			// range
			template <class InputIterator>
			map(InputIterator begin, InputIterator end,
				const key_compare &comp = key_compare(),
				typename ft::iterator_traits<InputIterator>::iterator_category* = 0,
				const allocator_type &alloc = allocator_type()) :
				_compare(comp), _allocator(alloc), _size(0), _root(0)
			{
				_setup();
				insert(begin, end);
			}

			// copy
			map(const map &x) :
				_compare(x._compare), _allocator(x._allocator), _size(0), _root(0)
			{
				_setup();
				*this = x;
			}

			// Destructor
			~map()
			{
				clear();
			}

			// Assignment operator
			map	&operator=(const map &x)
			{
				this->_compare = x._compare;
				clear();
				insert(x.begin(), x.end());
				return (*this);
			}

		// Iterators
		public:
			// begin
			iterator				begin()
			{
				return (iterator(this->_begin.next()));
			}

			const_iterator			begin() const
			{
				return (const_iterator(this->_begin.next()));
			}

			// end
			iterator				end()
			{
				return (iterator(&this->_end));
			}

			const_iterator			end() const
			{
				return (const_iterator(const_cast<node*>(&this->_end)));
			}

			// rbegin
			reverse_iterator		rbegin()
			{
				return (reverse_iterator(this->_end.prev()));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(const_cast<node*>(this->_end.prev())));
			}

			// rend
			reverse_iterator		rend()
			{
				return (reverse_iterator(&this->_begin));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(&this->_begin));
			}

		// Capacity
		public:
			// empty
			bool		empty() const
			{
				return (this->_size == 0);
			}

			// size
			size_type	size() const
			{
				return (this->_size);
			}

			// max size
			size_type	max_size() const
			{
				return (this->_allocator.max_size());
			}

		// Dereference
		public:
			// subscript
			mapped_type	&operator[](const key_type &k)
			{
				return ((*((insert(ft::make_pair(k, mapped_type()))).first)).second);
			}

		// Modifiers
		public:
			// insert
			ft::pair<iterator, bool>	insert(const value_type &val)
			{
				size_type	old_size = this->_size;

				this->_root = _insert_node(val, this->_root, 0);
				_replace();
				return (ft::make_pair(find(val.first), (this->_size != old_size)));
			}

			iterator	insert(iterator pos, const value_type &val)
			{
				(void) pos;
				return (insert(val).first);
			}

			template <class InputIterator>
			void		insert(InputIterator begin, InputIterator end,
							typename iterator_traits<InputIterator>::iterator_category* = 0)
			{
				while (begin != end)
					insert(*(begin++));
			}

			// erase
			void		erase(iterator pos)
			{
				this->_root = _erase_node(pos->first, this->_root);
				_replace();
			}

			size_type	erase(const key_type &k)
			{
				size_type	old_size = this->_size;

				this->_root = _erase_node(k, this->_root);
				_replace();
				return (old_size - this->_size);
			}

			void	erase(iterator begin, iterator end)
			{
				while (begin != end)
					erase(begin++);
			}

			// clear
			void	clear()
			{
				_clear(this->_root);
			}

			// swap
			void	swap(map &other)
			{
				ft::swap(this->_root, other._root);
				ft::swap(this->_allocator, other._allocator);
				ft::swap(this->_compare, other._compare);
				ft::swap(this->_size, other._size);
				if (this->_root)
					this->_root->update_sentinel(&this->_begin, &this->_end);
				if (other._root)
					other._root->update_sentinel(&other._begin, &other._end);
				_replace();
				other._replace();
			}

		// Key comparison
		public:
			key_compare		key_comp() const
			{
				return (this->_compare);
			}

			value_compare	value_comp() const
			{
				return (value_compare(this->_compare));
			}

		// Lookup
		public:
			// find
			iterator		find(const key_type &k)
			{
				node	*find_node = _find_node(k);

				if (!find_node)
					return (end());
				return (iterator(find_node));
			}

			const_iterator	find(const key_type &k) const
			{
				node	*find_node = _find_node(k);

				if (!find_node)
					return (end());
				return (const_iterator(find_node));
			}

			// count
			size_type		count(const key_type &k) const
			{
				if (_find_node(k))
					return (1);
				return (0);
			}

			// lower bound
			iterator		lower_bound(const key_type &k)
			{
				iterator	bound = begin();

				while (bound != end() && this->_compare(bound->first, k))
					bound++;
				return (bound);
			}

			const_iterator	lower_bound(const key_type &k) const
			{
				const_iterator	bound = begin();

				while (bound != end() && this->_compare(bound->first, k))
					bound++;
				return (bound);
			}

			// upper bound
			iterator		upper_bound(const key_type &k)
			{
				iterator	bound = begin();

				while (bound != end() && !this->_compare(k, bound->first))
					bound++;
				return (bound);
			}

			const_iterator	upper_bound(const key_type &k) const
			{
				const_iterator	bound = begin();

				while (bound != end() && !this->_compare(k, bound->first))
					bound++;
				return (bound);
			}

			// equal range
			ft::pair<iterator, iterator>				equal_range(const key_type &k)
			{
				return (make_pair(lower_bound(k), upper_bound(k)));
			}

			ft::pair<const_iterator, const_iterator>	equal_range(const key_type &k) const
			{
				return (make_pair(lower_bound(k), upper_bound(k)));
			}

		// Allocator
		public:
			// getter
			allocator_type	get_allocator() const
			{
				return (this->_allocator);
			}

		private:
			void	_setup()
			{
				this->_begin.begin = &this->_begin;
				this->_begin.end = &this->_end;
				this->_end.end = &this->_end;
				this->_end.begin = &this->_begin;
			}

			node	*_find_node(const key_type &k) const
			{
				node	*tmp = this->_root;

				while (tmp->data.first != k)
				{
					if (ft::isEqual(tmp->data.first, k) == false)
					{
						if (this->_compare(tmp->data.first, k) && tmp->right)
							tmp = tmp->right;
						else if (tmp->left)
							tmp = tmp->left;
						else
							break ;
					}
					else
						break ;
				}
				if (tmp->data.first != k)
					return (0);
				return (tmp);
			}

			node	*_erase_node(const key_type &k, node *cur)
			{
				if (!cur)
					return (cur);
				// check right or left
				if (k < cur->data.first)
					cur->left = _erase_node(k, cur->left);
				else if (k > cur->data.first)
					cur->right = _erase_node(k, cur->right);
				else
					cur = _delete_node(cur);
				// check only node
				if (!cur)
					return (cur);
				cur->update_height();
				// check need rotation
				if (_should_rotate_erase(cur))
					return (cur->parent);
				return (cur);
			}

			node	*_delete_node(node *cur)
			{
				// check only or no child
				if (!cur->left || !cur->right)
				{
					node	*tmp = cur->left ? cur->left : cur->right;

					// no child
					if (!cur->left && !cur->right)
					{
						tmp = cur;
						this->_allocator.destroy(tmp);
						this->_allocator.deallocate(tmp, 1);
						cur = 0;
						this->_size--;
					}
					else // one child
					{
						tmp->parent = cur->parent;

						node	*tmp2 = cur;

						cur = tmp;
						this->_allocator.destroy(tmp2);
						this->_allocator.deallocate(tmp2, 1);
						this->_size--;
					}
				}
				else // or two
				{
					node	*tmp = cur->right;

					while (tmp->left)
						tmp = tmp->left;
					// link pointers to the nodes
					_swap_node(cur, tmp);
					ft::swap(cur, tmp);
					cur->right = _erase_node(tmp->data.first, cur->right);
				}
				return (cur);
			}

			node	*_insert_node(const value_type &val, node *cur, node *parent)
			{
				key_type	key = val.first;

				if (!cur)
					return (_create_node(val, parent));
				// check place left or right
				if (this->_compare(key, cur->data.first))
					cur->left = _insert_node(val, cur->left, cur);
				else if (this->_compare(cur->data.first, key))
					cur->right = _insert_node(val, cur->right, cur);
				else
					return (cur);
				cur->update_height();
				if (_should_rotate(key, cur))
					return (cur->parent);
				return (cur);
			}

			node	*_create_node(const value_type &val, node *parent)
			{
				node	*newNode = this->_allocator.allocate(1);

				this->_allocator.construct(newNode, val);
				newNode->begin = &this->_begin;
				newNode->end = &this->_end;
				newNode->parent = parent;
				this->_size++;
				return (newNode);
			}

			bool	_should_rotate(const key_type &key, node *cur)
			{
				// l-l rotate
				if (cur->get_balance() > 1 && this->_compare(key, cur->left->data.first))
				{
					cur->rotate_right();
					return (true);
				}
				// r-r rotate
				if (cur->get_balance() < -1 && this->_compare(cur->right->data.first, key))
				{
					cur->rotate_left();
					return (true);
				}
				// l-r rotate
				if (cur->get_balance() > 1 && this->_compare(cur->left->data.first, key))
				{
					cur->left->rotate_left();
					cur->rotate_right();
					return (true);
				}
				// r-l rotate
				if (cur->get_balance() < -1 && this->_compare(key, cur->right->data.first))
				{
					cur->right->rotate_right();
					cur->rotate_left();
					return (true);
				}
				return (false);
			}

			bool	_should_rotate_erase(node *cur)
			{
				// l-l rotate
				if (cur->get_balance() > 1 && cur->left->get_balance() >= 0)
				{
					cur->rotate_right();
					return (true);
				}
				// r-r rotate
				if (cur->get_balance() < -1 && cur->right->get_balance() <= 0)
				{
					cur->rotate_left();
					return (true);
				}
				// l-r rotate
				if (cur->get_balance() > 1 && cur->left->get_balance() < 0)
				{
					cur->left->rotate_left();
					cur->rotate_right();
					return (true);
				}
				// r-l rotate
				if (cur->get_balance() < -1 && cur->right->get_balance() > 0)
				{
					cur->right->rotate_right();
					cur->rotate_left();
					return (true);
				}
				return (false);
			}

			void	_replace()
			{
				this->_begin.parent = this->_root;
				this->_end.parent = this->_root;
			}

			void	_swap_node(node *first, node *second)
			{
				if (first == second)
					return ;
				if (first->parent)
				{
					if (first == first->parent->right)
						first->parent->right = second;
					else
						first->parent->left = second;
				}
				if (second->parent)
				{
					if (second == second->parent->right)
						second->parent->right = first;
					else
						second->parent->left = first;
				}
				ft::swap(first->parent, second->parent);
				// connect child parents with node
				if (first->left)
					first->left->parent = second;
				if (first->right)
					first->right->parent = second;
				if (second->left)
					second->left->parent = first;
				if (second->right)
					second->right->parent = first;
				ft::swap(first->left, second->left);
				ft::swap(first->right, second->right);
				ft::swap(first->height, second->height);
			}

			// clear no balance
			void	_clear(node *cur)
			{
				if (!cur || !this->_size)
					return ;
				_clear(cur->left);
				_clear(cur->right);
				this->_allocator.destroy(cur);
				this->_allocator.deallocate(cur, 1);
				this->_size--;
				if (cur == this->_root)
				   this->_root = 0;
				_replace();
			}
	};

			// Relational operators
			template <class Key, class T, class Compare, class Alloc>
			bool operator==(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
			{
				if (lhs.size() != rhs.size())
					return (false);

				typename ft::map<Key, T, Compare, Alloc>::const_iterator 	it_lhs, it_rhs;

				it_lhs = lhs.begin();
				it_rhs = rhs.begin();
				while (it_lhs != lhs.end() && it_rhs != rhs.end())
				{
					if (*it_lhs != *it_rhs)
						return (false);
					it_lhs++;
					it_rhs++;
				}
				return (true);
			}

			template <class Key, class T, class Compare, class Alloc>
			bool operator!=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
			{
				return !(lhs == rhs);
			}

			template <class Key, class T, class Compare, class Alloc>
			bool operator<(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
			{
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}

			template <class Key, class T, class Compare, class Alloc>
			bool operator<=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
			{
				return !(rhs < lhs);
			}

			template <class Key, class T, class Compare, class Alloc>
			bool operator>(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
			{
				return (rhs < lhs);
			}

			template <class Key, class T, class Compare, class Alloc>
			bool operator>=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
			{
				return !(lhs < rhs);
			}

			// Swap
			template <class Key, class T, class Compare, class Alloc>
			void	swap(ft::map<Key,T,Compare,Alloc> &lhs, ft::map<Key,T,Compare,Alloc> &rhs)
			{
				lhs.swap(rhs);
			}
}

#endif
