#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

  

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
    m_heap = values;
    for (unsigned int i=0;i<m_heap.size();i++) {
      percolate_up(i,m_heap);
    }
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
    m_heap.push_back(entry);
    percolate_up(m_heap.size()-1,m_heap);
  }

  void pop() 
  {
    assert( !m_heap.empty() );
    m_heap[0] = m_heap[m_heap.size()-1];
    m_heap.pop_back();
    percolate_down(0,m_heap);

  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
    for (unsigned int i=1;i<heap.size();i++) {
      unsigned int parent = i;//(i-1)/2;
      unsigned int left = (2*i)+1;
      unsigned int right = (2*i) +2;
      if (right < heap.size()) {
        if (heap[parent] > heap[right]) {
          return false;
        }
      }
      if (left < heap.size()) {
        if (heap[parent] > heap[left]) {
          return false;
        }
      }
    }
    return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }

  void percolate_up(int loc, std::vector<T>& heap) {
    /*percolate_up(TreeNode<T> * p) {
      while (p->parent)
        if (p->value < p->parent->value) {
          swap(p, parent); // value and other non-pointer member vars
          p = p->parent;
        } else
          break;
      }*/


    while (true) {
      unsigned int parent_index = (loc-1)/2;
      if (parent_index>heap.size()) {
        break;
      } else {
        if (heap[loc] < heap[parent_index]) {
          T cur_val = heap[loc];
          T par_val = heap[parent_index];
          heap[loc] = par_val;
          heap[parent_index] = cur_val;
          loc = parent_index;
        } else {
          break;
        }
      }
    }


  }

  void percolate_down(int loc, std::vector<T>& heap, int range=0) {
  /*  
    percolate_down(TreeNode<T> * p) {
      while (p->left) {
        TreeNode<T>* child;
        // Choose the child to compare against
        if (p->right && p->right->value < p->left->value)
          child = p->right;
        else
          child = p->left;
        if (child->value < p->value) {
          swap(child, p); // value and other non-pointer member vars
          p = child;
        }
        else
          break;
      }
    }
  */
    if (range==0) {
      range = heap.size()-1;
    }

    while (true) {
      unsigned int left = (2*loc)+1;
      unsigned int right = (2*loc)+2;
      unsigned int child = 0;

      if (left>range) {
        break;
      } 


      if ((right<range+1)&&(heap[right]<heap[left])) {
        child = right;
      } else {
        child = left;
      }
      if (heap[child]<heap[loc]) {
        T cur_val = heap[loc];
        T chi_val = heap[child];
        heap[child] = cur_val;
        heap[loc] = chi_val;
        loc = child;
      } else {
        break;
      }

    }
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v )
{
  priority_queue<T> blah;
  /*std::cout << std::endl << "This is what the vector starts as:" << std::endl;
  for (unsigned int i=0;i<v.size();i++) {
    std::cout << v[i] << std::endl;
  }

  std::cout << std::endl << "This is what the heapified vector should be:" << std::endl;
  priority_queue<T> test(v);
  test.print_heap(std::cout);*/

  if (v.empty()) {
    return;
  }

  for (unsigned int i=0;i<v.size();i++) {
    blah.percolate_up(i,v);
  }

  T temp;

  unsigned int end = v.size()-1;
  while (end>0) {
    temp = v[0];
    v[0] = v[end];
    v[end] = v[0];
    blah.percolate_down(0,v,end);
    end--;
  }




}

/*procedure heapsort(a, count) is
    input: an unordered array a of length count
 
    (Build the heap in array a so that largest value is at the root)
    heapify(a, count)

    (The following loop maintains the invariants that a[0:end] is a heap and every element
     beyond end is greater than everything before it (so a[end:count] is in sorted order))
    end ← count - 1
    while end > 0 do
        (a[0] is the root and largest value. The swap moves it in front of the sorted elements.)
        swap(a[end], a[0])
        (the heap size is reduced by one)
        end ← end - 1
        (the swap ruined the heap property, so restore it)
        siftDown(a, 0, end)*/

#endif
