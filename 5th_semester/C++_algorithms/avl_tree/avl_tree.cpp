#ifndef __PROGTEST__
#include <cassert>
#include <cstdarg>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <array>
#include <random>
#include <type_traits>

// We use std::set as a reference to check our implementation.
// It is not available in progtest :)
#include <set>

template < typename T >
struct Ref {
    size_t size() const { return _data.size(); }
    const T* find(const T& value) const {
      auto it = _data.find(value);
      if (it == _data.end()) return nullptr;
      return &*it;
    }
    bool insert(const T& value) { return _data.insert(value).second; }
    bool erase(const T& value) { return _data.erase(value); }

    auto begin() const { return _data.begin(); }
    auto end() const { return _data.end(); }

private:
    std::set<T> _data;
};

#endif


namespace config {
    // Enable to check that the tree is AVL balanced.
    inline constexpr bool CHECK_DEPTH = false;

    // Disable if your implementation does not have parent pointers
    inline constexpr bool PARENT_POINTERS = true;
}
template< typename T>
struct Node{
    Node * parent;
    Node * left;
    Node * right;
    T value;
    size_t height;
    int m_balance;
    int balance() const{
      if(!left && !right) return 0;
      else if(!left && right) return right->height;
      else if(left && !right) return 0 - left->height;
      else return right->height - left->height;
    }

    Node(T value){
      parent = nullptr;
      left = nullptr;
      right = nullptr;
      this->value = value;
      height = 1;
      m_balance = 0;
    }
    ~Node(){}
};

// TODO implement
template < typename T >
struct Tree {
    Tree(){
      root = nullptr;
      ammount = 0;
    }

    ~Tree(){
      freeTree(root);
    }

    void freeTree(Node<T> * node){
      if(node){
        if(node->left)freeTree(node->left);
        if(node->right)freeTree(node->right);
        delete node;
      }
    }

    size_t size() const{return ammount;};

    const T* find(const T& value) const{
      Node<T>* tmp = root;
      while(tmp){
        if(value == tmp->value){
          return &tmp->value;
        }
        else if(value < tmp->value){
          tmp = tmp->left;
        }
        else if(value > tmp->value){
          tmp = tmp->right;
        }
      }
      return nullptr;
    }

    bool leftBalanceInsert(Node<T> * x, Node<T> * y){
      if(x->m_balance == 0){
        x->m_balance = -1;
        x->height++;
        return true;
      }
      if(x->m_balance == 1){
        x->m_balance = 0;
        return false;
      }
      if(x->m_balance == -1){
        if(y->m_balance == -1){
          rotateRight(x);
          x->m_balance = 0;
          y->m_balance = 0;
          if(!y->parent) root = y;
          return false;
        }
        else if(y->m_balance == 1){
          rotateLeft(y);
          rotateRight(x);
          x->parent->m_balance=0;
          x->m_balance = x->balance();
          y->m_balance = y->balance();
          if(!x->parent->parent) root = x->parent;
          return false;
        }
      }
      return false;
    }

    bool rightBalanceInsert(Node<T> * x, Node<T> * y){
      if(x->m_balance == 0){
        x->m_balance = 1;
        x->height++;
        return true;
      }
      if(x->m_balance == -1 ){
        x->m_balance = 0;
        return false;
      }
      if(x->m_balance == 1){
        if(y->m_balance == -1){
          rotateRight(y);
          rotateLeft(x);
          x->m_balance = x->balance();
          y->m_balance = y->balance();
          x->parent->m_balance = 0;
          if(!x->parent->parent) root = x->parent;
          return false;
        }
        else if(y->m_balance == 1){
          rotateLeft(x);
          x->m_balance = 0;
          y->m_balance = 0;
          if(!y->parent) root = y;
          return false;
        }

      }
      return false;
    }

    void balanceInsert(Node<T> * node){
      Node<T> * tmp = node;
      while(tmp->parent){
        Node<T> * prev = tmp;
        tmp = tmp->parent;
        if(prev == tmp->left){
          if(!leftBalanceInsert(tmp, prev)) return;
        }
        if(prev == tmp->right){
          if(!rightBalanceInsert(tmp, prev)) return;
        }
      }


    }

    bool insert(T value){
      Node<T> * node = new Node<T>(value);
      ammount++;
      if(!root){
        root = node;
        return true;
      }
      Node<T> * tmp = root;
      while(tmp){
        if(value == tmp->value){
          delete node;
          ammount--;
          return false;
        }
        else if(value < tmp->value){
          if(tmp->left)tmp = tmp->left;
          else {
            tmp->left = node;
            node->parent = tmp;
            balanceInsert(node);
            return true;
          }
        }
        else if(value > tmp->value){
          if(tmp->right)tmp = tmp->right;
          else {
            tmp->right = node;
            node->parent = tmp;
            balanceInsert(node);
            return true;
          }
        }
      }
      return false;
    }

    void bowSon(const bool & right, Node<T> * parent, Node<T> * son){
      if(right){
        parent->right = son;
      }
      else parent->left = son;
      if(son)son->parent = parent;
    }

    Node<T> * findMin(Node<T> * node) const{
      if(!node->left) return node;
      else return findMin(node->left);
    }

    Node<T> * leftBalanceDelete(Node<T> * x, Node<T> * y){
      if(x->m_balance == -1){
        x->m_balance = 0;
        x->height--;
        return x;
      }
      if(x->m_balance == 0 ){
        x->m_balance = 1;
        return nullptr;
      }
      if(x->m_balance == 1){
        if(y->m_balance == 1){
          rotateLeft(x);
          x->m_balance = 0;
          y->m_balance = 0;
          if(!y->parent) root = y;
          return y;
        }
        else if(y->m_balance == 0){
          rotateLeft(x);
          x->m_balance = 1;
          y->m_balance = -1;
          if(!y->parent) root = y;
          return nullptr;
        }
        else if(y->m_balance == -1){
          rotateRight(y);
          rotateLeft(x);
          x->m_balance = x->balance();
          y->m_balance = y->balance();
          x->parent->m_balance = 0;
          if(!x->parent->parent) root = x->parent;
          return x->parent;
        }
      }
      return nullptr;
    }

    Node<T> * rightBalanceDelete(Node<T> * x, Node<T> * y){
      if(x->m_balance == 1){
        x->m_balance = 0;
        x->height--;
        return x;
      }
      if(x->m_balance == 0 ){
        x->m_balance = -1;
        return nullptr;
      }
      if(x->m_balance == -1){
        if(y->m_balance == -1){
          rotateRight(x);
          x->m_balance = 0;
          y->m_balance = 0;
          if(!y->parent) root = y;
          return y;
        }
        else if(y->m_balance == 0){
          rotateRight(x);
          x->m_balance = -1;
          y->m_balance = 1;
          if(!y->parent) root = y;
          return nullptr;
        }
        else if(y->m_balance == 1){
          rotateLeft(y);
          rotateRight(x);
          x->m_balance = x->balance();
          y->m_balance = y->balance();
          x->parent->m_balance = 0;
          if(!x->parent->parent) root = x->parent;
          return x->parent;
        }

      }
      return nullptr;
    }


    void balanceDelete(Node<T> * node, Node<T> * r, bool & rightson){
      Node<T> * x = node;
      Node<T> * y = r;

      while(x){
        if(!rightson){
          y = leftBalanceDelete(x, y);
          if(!y) return;
          x = y->parent;
          if(!x) return;
          if(x->left == y){
            y = x->right;
            rightson = false;
          }
          else if(x->right == y) {
            y =x->left;
            rightson = true;
          }
        }
        else if(rightson){
          y = rightBalanceDelete(x, y);
          if(!y) return;
          x = y->parent;
          if(!x) return;
          if(x->left == y){
            y = x->right;
            rightson = false;
          }
          else if(x->right == y) {
            y =x->left;
            rightson = true;
          }
        }
      }
    }

    bool erase(const T& value){
      Node<T> * tmp = root;
      bool rightSon = false;
      while(tmp){
        if(value == tmp->value){
          if(!tmp->left && !tmp->right){
            bowSon(rightSon, tmp->parent, nullptr);
          }
          else if(!tmp->left){
            bowSon(rightSon, tmp->parent, tmp->right);
          }
          else if(!tmp->right){
            bowSon(rightSon, tmp->parent, tmp->left);
          }
          else{
            Node<T> * son = findMin(tmp->right);
            tmp->value = son->value;
            if(son->parent->left == son) {
              son->parent->left = son->right;
              rightSon = false;
              if(son->right){
                son->right->parent = son->parent;
              }
            }
            else {
              son->parent->right = son->right;
              rightSon = true;
              if(son->right){
                son->right->parent = son->parent;
              }
            }

            tmp = son;
          }
          if(rightSon)balanceDelete(tmp->parent, tmp->parent->left, rightSon);
          else balanceDelete(tmp->parent, tmp->parent->right, rightSon);
          delete tmp;
          ammount--;
          return true;
        }
        else if(value < tmp->value){
          tmp = tmp->left;
          rightSon = false;
        }
        else if(value > tmp->value){
          tmp = tmp->right;
          rightSon = true;
        }
      }
      return false;

    }

    size_t newHeight(const Node<T> * x) const{
      if(!x->left && !x->right) return 1;
      else if(!x->left && x->right) return x->right->height + 1;
      else if(x->left && !x->right) return x->left->height + 1;
      else return std::max(x->left->height, x->right->height) + 1;
    }

    void rotateLeft(Node<T>* x) const{
      Node<T> * y = x->right;
      if(x->right)x->right = y->left;
      y->left = x;
      if(x->right)x->right->parent = x;
      y->parent = x->parent;
      if(x->parent && x->parent->value < x->value) x->parent->right = y;
      else if(x->parent) x->parent->left = y;
      x->parent = y;
      x->height = newHeight(x);
      y->height = newHeight(y);
    }

    void rotateRight(Node<T>* x) const{
      Node<T> * y = x->left;
      if(x->left)x->left = y->right;
      y->right = x;
      if(x->left)x->left->parent = x;
      y->parent = x->parent;
      if(x->parent && x->parent->value < x->value) x->parent->right = y;
      else if(x->parent) x->parent->left = y;
      x->parent = y;
      x->height = newHeight(x);
      y->height = newHeight(y);
    }



    // Needed to test the structure of the tree.
    // Replace Node with the real type of your nodes
    // and implementations with the ones matching
    // your attributes.
    struct TesterInterface {
        // using Node = ...
        static const Node<T> *root(const Tree *t) { return t->root; }
        // Parent of root must be nullptr, ignore if config::PARENT_POINTERS == false
        static const Node<T> *parent(const Node<T> *n) { return n->parent; }
        static const Node<T> *right(const Node<T> *n) { return n->right; }
        static const Node<T> *left(const Node<T> *n) { return n->left; }
        static const T& value(const Node<T> *n) { return n->value; }
    };
    size_t ammount;
    Node<T> * root;
};


#ifndef __PROGTEST__

struct TestFailed : std::runtime_error {
    using std::runtime_error::runtime_error;
};

std::string fmt(const char *f, ...) {
  va_list args1;
  va_list args2;
  va_start(args1, f);
  va_copy(args2, args1);

  std::string buf(vsnprintf(nullptr, 0, f, args1), '\0');
  va_end(args1);

  vsnprintf(buf.data(), buf.size() + 1, f, args2);
  va_end(args2);

  return buf;
}

template < typename T >
struct Tester {
    Tester() = default;

    void size() const {
      size_t r = ref.size();
      size_t t = tested.size();
      if (r != t) throw TestFailed(fmt("Size: got %zu but expected %zu.", t, r));
    }

    void find(const T& x) const {
      auto r = ref.find(x);
      auto t = tested.find(x);
      bool found_r = r != nullptr;
      bool found_t = t != nullptr;

      if (found_r != found_t) _throw("Find mismatch", found_r);
      if (found_r && *t != x) throw TestFailed("Find: found different value");
    }

    void insert(const T& x, bool check_tree_ = false) {
      auto succ_r = ref.insert(x);
      auto succ_t = tested.insert(x);
      if (succ_r != succ_t) _throw("Insert mismatch", succ_r);
      size();
      if (check_tree_) check_tree();
    }

    void erase(const T& x, bool check_tree_ = false) {
      bool succ_r = ref.erase(x);
      auto succ_t = tested.erase(x);
      if (succ_r != succ_t) _throw("Erase mismatch", succ_r);
      size();
      if (check_tree_) check_tree();
    }

    struct NodeCheckResult {
        const T* min = nullptr;
        const T* max = nullptr;
        int depth = -1;
        size_t size = 0;
    };

    void check_tree() const {
      using TI = typename Tree<T>::TesterInterface;
      auto ref_it = ref.begin();
      bool check_value_failed = false;
      auto check_value = [&](const T& v) {
          if (check_value_failed) return;
          check_value_failed = (ref_it == ref.end() || *ref_it != v);
          if (!check_value_failed) ++ref_it;
      };

      auto r = check_node(TI::root(&tested), decltype(TI::root(&tested))(nullptr), check_value);
      size_t t_size = tested.size();

      if (t_size != r.size) throw TestFailed(
                fmt("Check tree: size() reports %zu but expected %zu.", t_size, r.size));

      if (check_value_failed) throw TestFailed(
                "Check tree: element mismatch");

      size();
    }

    template < typename Node, typename F >
    NodeCheckResult check_node(const Node* n, const Node* p, F& check_value) const {
      if (!n) return {};

      using TI = typename Tree<T>::TesterInterface;
      if constexpr(config::PARENT_POINTERS) {
        if (TI::parent(n) != p) throw TestFailed("Parent mismatch.");
      }

      auto l = check_node(TI::left(n), n, check_value);
      check_value(TI::value(n));
      auto r = check_node(TI::right(n), n, check_value);

      if (l.max && !(*l.max < TI::value(n)))
        throw TestFailed("Max of left subtree is too big.");
      if (r.min && !(TI::value(n) < *r.min))
        throw TestFailed("Min of right subtree is too small.");

      if (config::CHECK_DEPTH && abs(l.depth - r.depth) > 1) throw TestFailed(fmt(
                "Tree is not avl balanced: left depth %i and right depth %i.",
                l.depth, r.depth
        ));

      return {
              l.min ? l.min : &TI::value(n),
              r.max ? r.max : &TI::value(n),
              std::max(l.depth, r.depth) + 1, 1 + l.size + r.size
      };
    }

    static void _throw(const char *msg, bool s) {
      throw TestFailed(fmt("%s: ref %s.", msg, s ? "succeeded" : "failed"));
    }

    Tree<T> tested;
    Ref<T> ref;
};


void test_insert() {
  Tester<int> t;

  for (int i = 0; i < 10; i++) t.insert(i, true);
  for (int i = -10; i < 20; i++) t.find(i);

  for (int i = 0; i < 10; i++) t.insert((1 + i * 7) % 17, true);
  for (int i = -10; i < 20; i++) t.find(i);
}

void test_erase() {
  Tester<int> t;

  for (int i = 0; i < 10; i++) t.insert((1 + i * 7) % 17, true);
  for (int i = -10; i < 20; i++) t.find(i);

  for (int i = 3; i < 22; i += 2) t.erase(i, true);
  for (int i = -10; i < 20; i++) t.find(i);

  for (int i = 0; i < 10; i++) t.insert((1 + i * 13) % 17 - 8, true);
  for (int i = -10; i < 20; i++) t.find(i);

  for (int i = -4; i < 10; i++) t.erase(i, true);
  for (int i = -10; i < 20; i++) t.find(i);
}

enum RandomTestFlags : unsigned {
    SEQ = 1, NO_ERASE = 2, CHECK_TREE = 4
};

void test_random(size_t size, unsigned flags = 0) {
  Tester<size_t> t;
  std::mt19937 my_rand(24707 + size);

  bool seq = flags & SEQ;
  bool erase = !(flags & NO_ERASE);
  bool check_tree = flags & CHECK_TREE;

  for (size_t i = 0; i < size; i++)
    t.insert(seq ? 2*i : my_rand() % (3*size), check_tree);

  t.check_tree();

  for (size_t i = 0; i < 3*size + 1; i++) t.find(i);

  for (size_t i = 0; i < 30*size; i++) switch (my_rand() % 5) {
      case 1: t.insert(my_rand() % (3*size), check_tree);
        break;
      case 2: if (erase) t.erase(my_rand() % (3*size), check_tree);
        break;
      default:
        t.find(my_rand() % (3*size));
    }

  t.check_tree();
}

int main() {
  try {
    std::cout << "Insert test..." << std::endl;
    test_insert();

    std::cout << "Erase test..." << std::endl;
    test_erase();

    std::cout << "Tiny random test..." << std::endl;
    test_random(20, CHECK_TREE);

    std::cout << "Small random test..." << std::endl;
    test_random(200, CHECK_TREE);

    std::cout << "Big random test..." << std::endl;
    test_random(50'000);

    std::cout << "Big sequential test..." << std::endl;
    test_random(50'000, SEQ);

    std::cout << "All tests passed." << std::endl;
  } catch (const TestFailed& e) {
    std::cout << "Test failed: " << e.what() << std::endl;
  }
}

#endif


