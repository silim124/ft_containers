/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:44:15 by silim             #+#    #+#             */
/*   Updated: 2022/05/28 15:48:48 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include "RandomAccessIterator.hpp"
# include "ReverseIterator.hpp"
# include "IteratorTraits.hpp"
# include "Utils.hpp"
# include <memory>
# include <cstddef>
# include <stdexcept>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef RandomAccessIterator<T, T*, T&>					iterator;
			typedef RandomAccessIterator<T, const T*, const T&>		const_iterator;
			typedef ReverseIterator<iterator>						reverse_iterator;
			typedef ReverseIterator<const_iterator>					const_reverse_iterator;
			typedef ptrdiff_t										difference_type;
			typedef size_t											size_type;

		private:
			allocator_type	_alloc;
			size_type		_size;
			size_type		_capacity;
			pointer			_data;

		// Constructor
		public:
			// default
			explicit vector(const allocator_type &alloc = allocator_type()) :
				_alloc(alloc), _size(0), _capacity(0), _data(0) {}

				// fill
			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _data(0)
			{
				assign(n, val);
			}

				// range
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
				typename ft::iterator_traits<InputIterator>::iterator_category* = 0,
				const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _data(0)
			{
				assign(first, last);
			}

				// copy
			vector(const vector &x) : _size(0), _capacity(0), _data(0)
			{
				*this = x;
			}

			// Destructor
			~vector()
			{
				clear();
				this->_alloc.deallocate(this->_data, this->_capacity);
			}

			// Assignment operator
			vector	&operator=(const vector &x)
			{
				assign(x.begin(), x.end());
				return (*this);
			}

		// Iterators
		public:
			// begin
			iterator				begin()
			{
				return (iterator(this->_data));
			}

			const_iterator			begin() const
			{
				return (const_iterator(this->_data));
			}

			// end
			iterator				end()
			{
				return (iterator(&this->_data[this->_size]));
			}

			const_iterator			end() const
			{
				return (const_iterator(&this->_data[this->_size]));
			}

			// rbegin
			reverse_iterator		rbegin()
			{
				return (reverse_iterator(&this->_data[this->_size - 1]));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(&this->_data[this->_size - 1]));
			}

			// rend
			reverse_iterator		rend()
			{
				return (reverse_iterator(_data - 1));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(_data - 1));
			}

		// capacity
		public:
			// size
			size_type	size() const
			{
				return (this->_size);
			}

			// max size
			size_type	max_size() const
			{
				return (this->_alloc.max_size());
			}

			// resize
			void		resize(size_type n, value_type val= value_type())
			{
				_set_capacity(n);
				while (this->_size > n)
					pop_back();
				while (this->_size < n)
					push_back(val);
			}

			// capacity
			size_type	capacity() const
			{
				return (this->_capacity);
			}

			// empty
			bool		empty() const
			{
				return (this->_size == 0);
			}

			// reserve
			void		reserve(size_type n)
			{
				_set_capacity(n, true);
			}

		// Dereference
		public:
			// subscript
			reference		operator[](size_type n)
			{
				return (this->_data[n]);
			}

			const_reference	operator[](size_type n) const
			{
				return (this->_data[n]);
			}

			// at
			reference		at(size_type n)
			{
				if (n >= this->_size)
					throw (std::out_of_range("out of range"));
				return (this->_data[n]);
			}

			const_reference	at(size_type n) const
			{
				if (n >= this->_size)
					throw (std::out_of_range("out of range"));
				return (this->_data[n]);
			}

			// front
			reference		front()
			{
				return (this->_data[0]);
			}

			const_reference	front() const
			{
				return (this->_data[0]);
			}

			// back
			reference		back()
			{
				return (this->_data[this->_size - 1]);
			}

			const_reference	back() const
			{
				return (this->_data[this->_size - 1]);
			}

		// Modifiers
		public:
			// assign
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last,
						typename ft::iterator_traits<InputIterator>::iterator_category* = 0)
			{
				clear();
				_set_capacity(ft::distance(first, last), true);
				while (first != last)
				{
					push_back(*first);
					first++;
				}
			}

			void		assign(size_type n, const value_type &val)
			{
				clear();
				_set_capacity(n, true);
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			// push back
			void		push_back(const value_type &val)
			{
				_set_capacity(this->_size + 1);
				_add_val(val, size());
			}

			// pop back
			void	pop_back()
			{
				this->_size--;
				this->_alloc.destroy(&this->_data[this->_size]);
			}

			// insert
			iterator	insert(iterator pos, const value_type &val)
			{
				difference_type	insert_pos = ft::distance(begin(), pos);

				insert(pos, 1, val);
				return (begin() + insert_pos);
			}

			void		insert(iterator pos, size_type n, const value_type &val)
			{
				difference_type	insert_pos = ft::distance(begin(), pos);

				_set_capacity(this->_size + n);
				_move_forward(n, insert_pos);
				for (size_type i = 0; i < n; i++)
					_add_val(val, insert_pos + i);
			}

			template <class InputIterator>
			void		insert(iterator pos, InputIterator first, InputIterator last,
										typename ft::iterator_traits<InputIterator>::iterator_category* = 0)
			{
				difference_type	insert_pos = ft::distance(begin(), pos);
				difference_type n = ft::distance(first, last);

				_set_capacity(this->_size + n);
				_move_forward(n, insert_pos);
				for (difference_type i = 0; i < n; i++)
					_add_val(*(first + i), insert_pos + i);
			}

			//// erase
			//iterator	erase(iterator pos)
			//{
			//	return (erase(pos, pos + 1));
			//}

			//iterator	erase(iterator first, iterator last)
			//{
			//	difference_type	pos = ft::distance(begin(), first);
			//	difference_type	n = ft::distance(first, last);

			//	_move_backward(n, pos);
			//	for (difference_type i = 0; i < n; i++)
			//		pop_back();
			//	return (begin() + pos);
			//}

			iterator erase(iterator pos)
		{
			return (erase(pos, pos + 1));
		}

		iterator erase(iterator first, iterator last)
		{
			if (first == last)
				return last;
			size_type erase_idx = \
				static_cast<size_type>(ft::distance(begin(), first));
			size_type rest_idx =
				static_cast<size_type>(ft::distance(begin(), last));
			size_type n = rest_idx - erase_idx;
			for (size_type i = erase_idx; rest_idx < size(); i++)
				_alloc.construct(_data + i, _data[rest_idx++]);
			for (size_type i = size() - n; i < size(); i++)
				_alloc.destroy(_data + i);
			_size -= n;
			return iterator(_data + erase_idx);
		}

			// swap
			void		swap(vector &x)
			{
				size_type		tmpSize = this->_size;
				size_type		tmpCapacity = this->_capacity;
				pointer			tmpData = this->_data;

				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_data = x._data;
				x._size = tmpSize;
				x._capacity = tmpCapacity;
				x._data = tmpData;
			}

			// clear
			void		clear()
			{
				while (this->_size)
					pop_back();
			}

		// Allocator
		public:
			// getter
			allocator_type	get_alloc() const
			{
				return (this->_alloc);
			}

		private:
			void	_add_val(const value_type &val, size_type pos)
			{
				this->_alloc.construct(&this->_data[pos], val);
				this->_size++;
			}

			void	_move_forward(size_type n, size_type pos)
			{
				for (size_type i = this->_size + n - 1; i >= pos + n; i--)
					this->_data[i] = this->_data[i - n];
			}

			void	_move_backward(size_type n, size_type pos)
			{
				for (size_type i = 0; i <= this->_size - n; i++)
					this->_data[pos + i] = this->_data[pos + i + n];
			}

			void	_set_capacity(size_type n, bool is_fixed = false)
			{
				if (n <= this->_capacity)
					return ;
				size_type	newCapacity = n;

				if (is_fixed == false)
				{
					if (n > this->_capacity && n < this->_capacity * 2)
						newCapacity = this->_capacity * 2;
				}

				pointer		tmp = this->_alloc.allocate(newCapacity);

				for (size_t i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(&tmp[i], this->_data[i]);
					this->_alloc.destroy(&this->_data[i]);
				}
				this->_alloc.deallocate(this->_data, this->_capacity);
				this->_capacity = newCapacity;
				this->_data = tmp;
			}
	};
			// Relational operators
			template <class T, class Alloc>
			bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return (lhs.size() == rhs.size() &&
						ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}

			template <class T, class Alloc>
			bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(lhs == rhs);
			}

			template <class T, class Alloc>
			bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
							rhs.begin(), rhs.end()));
			}

			template <class T, class Alloc>
			bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(rhs < lhs);
			}

			template <class T, class Alloc>
			bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return (rhs < lhs);
			}

			template <class T, class Alloc>
			bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(lhs < rhs);
			}

			// swap
			template <class T, class Alloc>
			void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
			{
				x.swap(y);
			}
}

#endif
