#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// Example 1:
// key type, mapped policy, key comparison functor, data structure, order functions
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> rbtree;
  rbtree tree;
  tree.insert(5);
  tree.insert(6);
  tree.insert(-100);
  tree.insert(5);
  assert(*tree.find_by_order(0) == -100);
  assert(tree.find_by_order(4) == tree.end());
  assert(tree.order_of_key(4) == 1); // lower_bound
  tree.erase(6);

  rbtree x;
  x.insert(9);
  x.insert(10);
  tree.join(x);
  assert(x.size() == 0);
  assert(tree.size() == 4);

  tree.split(9, x);
  assert(*x.begin() == 10);
  assert(*tree.begin() == -100);

// Example 2:
template <class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct my_node_update {
  typedef int metadata_type; // maintain size with int

  int order_of_key(pair<int, int> x) {
    int ans = 0;
    auto it = node_begin();
    while (it != node_end()) {
      auto l = it.get_l_child();
      auto r = it.get_r_child();
      if (Cmp_Fn()(x, **it)) { // x < it->size
        it = l;
      } else {
        if (x == **it) return ans; // x == it->size
        ++ans;
        if (l != node_end()) ans += l.get_metadata();
        it = r;
      }
    }
    return ans;
  }
  // update policy
  void operator()(Node_Itr it, Node_CItr end_it) {
    auto l = it.get_l_child();
    auto r = it.get_r_child();
    int left = 0, right = 0;
    if (l != end_it) left = l.get_metadata();
    if (r != end_it) right = r.get_metadata();
    const_cast<int &>(it.get_metadata()) = left + right + 1;
  }

  virtual Node_CItr node_begin() const = 0;
  virtual Node_CItr node_end() const = 0;
};

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, my_node_update> rbtree;
  rbtree g;
  g.insert({3, 4});
  assert(g.order_of_key({3, 4}) == 0);

