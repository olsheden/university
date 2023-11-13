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

// We use std::vector as a reference to check our implementation.
// It is not available in progtest :)
#include <vector>

template < typename T >
struct Ref {
    bool empty() const { return _data.empty(); }
    size_t size() const { return _data.size(); }

    const T& operator [] (size_t index) const { return _data.at(index); }
    T& operator [] (size_t index) { return _data.at(index); }

    void insert(size_t index, T value) {
      if (index > _data.size()) throw std::out_of_range("oops");
      _data.insert(_data.begin() + index, std::move(value));
    }

    T erase(size_t index) {
      T ret = std::move(_data.at(index));
      _data.erase(_data.begin() + index);
      return ret;
    }

    auto begin() const { return _data.begin(); }
    auto end() const { return _data.end(); }

private:
    std::vector<T> _data;
};

#endif


namespace config {
    inline constexpr bool PARENT_POINTERS = true;
    inline constexpr bool CHECK_DEPTH = true;
}

template< typename T>
struct Node{
    Node * parent;
    Node * left;
    Node * right;
    T value;
    size_t height;
    int m_balance;
    size_t nodes_left;
    size_t nodes_right;
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
      nodes_left = 0;
      nodes_right = 0;
    }
    ~Node(){}
};

// TODO implement
template < typename T >
struct Array {

    void freeTree(Node<T> * node){
      if(node){
        if(node->left)freeTree(node->left);
        if(node->right)freeTree(node->right);
        delete node;
      }
    }

    Array(){
      root = nullptr;
      ammount = 0;
    }

    ~Array(){
      freeTree(root);
    }

    size_t ammount;
    Node<T> * root;

    bool empty() const{
      return ammount == 0;
    }
    size_t size() const{
      return ammount;
    }

    const T& operator [] (size_t index) const{
      if(index >= size()) throw std::out_of_range("out of range");
      Node<T> * tmp = root;
      while(tmp){
        if(index == tmp->nodes_left){
          return tmp->value;
        }
        else if(index < tmp->nodes_left){
          tmp = tmp->left;
        }
        else{
          index-= (tmp->nodes_left + 1);
          tmp = tmp->right;
        }
      }
      return root->value;
    }
    T& operator [] (size_t index){
      if(index >= size()) throw std::out_of_range("out of range");
      Node<T> * tmp = root;
      while(tmp){
        if(index == tmp->nodes_left){
          return tmp->value;
        }
        else if(index < tmp->nodes_left){
          tmp = tmp->left;
        }
        else{
          index-= (tmp->nodes_left + 1);
          tmp = tmp->right;
        }
      }
      return root->value;
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

    size_t newHeight(const Node<T> * x) const{
      if(!x->left && !x->right) return 1;
      else if(!x->left && x->right) return x->right->height + 1;
      else if(x->left && !x->right) return x->left->height + 1;
      else return std::max(x->left->height, x->right->height) + 1;
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

    void insert(size_t index, T value){
      if(index > size()) throw std::out_of_range("out of range");
      Node<T> * node = new Node<T>(value);
      ammount++;
      if(!root){
        root = node;
        return;
      }
      Node<T> * tmp = root;
      if(index == size() - 1){
        while(tmp->right){
          tmp->nodes_right++;
          tmp = tmp->right;
        }
        tmp->nodes_right++;
        tmp->right = node;
        node->parent = tmp;
        balanceInsert(node);
        return;
      }
      while(tmp) {
        if (index == tmp->nodes_left) {
          tmp->nodes_left++;
          if(!tmp->left){
            tmp->left = node;
          }
          else{
            tmp = findMax(tmp->left);
            tmp->right = node;
          }
          node->parent = tmp;
          balanceInsert(node);
          return;
        } else if (index < tmp->nodes_left) {
          tmp->nodes_left++;
          tmp = tmp->left;
        } else {
          tmp->nodes_right++;
          index -= (tmp->nodes_left + 1);
          tmp = tmp->right;
        }
      }
    }
    void rotateLeft(Node<T>* x) const{
      Node<T> * y = x->right;
      if(x->right)x->right = y->left;
      y->left = x;
      if(x->right)x->right->parent = x;
      y->parent = x->parent;
      if(x->parent && x->parent->right == x) x->parent->right = y;
      else if(x->parent) x->parent->left = y;
      x->parent = y;
      x->height = newHeight(x);
      y->height = newHeight(y);
      x->nodes_right = count_Nodes(x->right);
      x->nodes_left = count_Nodes(x->left);
      y->nodes_left = count_Nodes(y->left);
      y->nodes_right = count_Nodes(y->right);
    }

    size_t count_Nodes(Node<T> * x) const{
      if(!x) return 0;

      return 1 + x->nodes_left + x->nodes_right;
    }

    void rotateRight(Node<T>* x) const{
      Node<T> * y = x->left;
      if(x->left)x->left = y->right;
      y->right = x;
      if(x->left)x->left->parent = x;
      y->parent = x->parent;
      if(x->parent && x->parent->right == x) x->parent->right = y;
      else if(x->parent) x->parent->left = y;
      x->parent = y;
      x->height = newHeight(x);
      y->height = newHeight(y);
      x->nodes_right = count_Nodes(x->right);
      x->nodes_left = count_Nodes(x->left);
      y->nodes_left = count_Nodes(y->left);
      y->nodes_right = count_Nodes(y->right);
    }

    void bowSon(const bool & right, Node<T> * parent, Node<T> * son){
      if(right){
        parent->right = son;
      }
      else parent->left = son;
      if(son)son->parent = parent;
    }

    Node<T> * findMax(Node<T> * node) const{
      node->nodes_right++;
      if(!node->right) return node;
      else{
        return findMax(node->right);
      }
    }

    Node<T> * findMin(Node<T> * node) const{
      node->nodes_left--;
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



    T erase(size_t index){
      if(index >= size()) throw std::out_of_range("out of range");
      T res;
      Node<T> * tmp = root;
      bool rightSon = false;
      while(tmp){
        if(index == tmp->nodes_left){
          res = tmp->value;
          if(!tmp->right){
            bowSon(rightSon, tmp->parent, tmp->left);
          }
          else{
            tmp->nodes_right--;
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
          return res;
        }
        else if(index < tmp->nodes_left){
          tmp->nodes_left--;
          tmp = tmp->left;
          rightSon = false;
        }
        else{
          index -= (tmp->nodes_left + 1);
          tmp->nodes_right--;
          tmp = tmp->right;
          rightSon = true;
        }
      }
      return root->value;
    }

    // Needed to test the structure of the tree.
    // Replace Node with the real type of your nodes
    // and implementations with the ones matching
    // your attributes.
    struct TesterInterface {
        // using Node = ...
        static const Node<T> *root(const Array *t) { return t->root; }
        // Parent of root must be nullptr, ignore if config::PARENT_POINTERS == false
        static const Node<T> *parent(const Node<T> *n) { return n->parent; }
        static const Node<T> *right(const Node<T> *n) { return n->right; }
        static const Node<T> *left(const Node<T> *n) { return n->left; }
        static const T& value(const Node<T> *n) { return n->value; }
    };
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

    size_t size() const {
      bool te = tested.empty();
      size_t r = ref.size();
      size_t t = tested.size();
      if (te != !t) throw TestFailed(fmt("Size: size %zu but empty is %s.",
                                         t, te ? "true" : "false"));
      if (r != t) throw TestFailed(fmt("Size: got %zu but expected %zu.", t, r));
      return r;
    }

    const T& operator [] (size_t index) const {
      const T& r = ref[index];
      const T& t = tested[index];
      if (r != t) throw TestFailed("Op [] const mismatch.");
      return t;
    }

    void assign(size_t index, T x) {
      ref[index] = x;
      tested[index] = std::move(x);
      operator[](index);
    }

    void insert(size_t i, T x, bool check_tree_ = false) {
      ref.insert(i, x);
      tested.insert(i, std::move(x));
      size();
      if (check_tree_) check_tree();
    }

    T erase(size_t i, bool check_tree_ = false) {
      T r = ref.erase(i);
      T t = tested.erase(i);
      if (r != t) TestFailed(fmt("Erase mismatch at %zu.", i));
      size();
      if (check_tree_) check_tree();
      return t;
    }

    void check_tree() const {
      using TI = typename Array<T>::TesterInterface;
      auto ref_it = ref.begin();
      bool check_value_failed = false;
      auto check_value = [&](const T& v) {
          if (check_value_failed) return;
          check_value_failed = (ref_it == ref.end() || *ref_it != v);
          if (!check_value_failed) ++ref_it;
      };

      size();

      check_node(TI::root(&tested), decltype(TI::root(&tested))(nullptr), check_value);

      if (check_value_failed) throw TestFailed(
                "Check tree: element mismatch");
    }

    template < typename Node, typename F >
    int check_node(const Node* n, const Node* p, F& check_value) const {
      if (!n) return -1;

      using TI = typename Array<T>::TesterInterface;
      if constexpr(config::PARENT_POINTERS) {
        if (TI::parent(n) != p) throw TestFailed("Parent mismatch.");
      }

      auto l_depth = check_node(TI::left(n), n, check_value);
      check_value(TI::value(n));
      auto r_depth = check_node(TI::right(n), n, check_value);

      if (config::CHECK_DEPTH && abs(l_depth - r_depth) > 1) throw TestFailed(fmt(
                "Tree is not avl balanced: left depth %i and right depth %i.",
                l_depth, r_depth
        ));

      return std::max(l_depth, r_depth) + 1;
    }

    static void _throw(const char *msg, bool s) {
      throw TestFailed(fmt("%s: ref %s.", msg, s ? "succeeded" : "failed"));
    }

    Array<T> tested;
    Ref<T> ref;
};


void test_insert() {
  Tester<int> t;

  for (int i = 0; i < 10; i++) t.insert(i, i, true);
  for (int i = 0; i < 10; i++) t.insert(i, -i, true);
  for (size_t i = 0; i < t.size(); i++) t[i];

  for (int i = 0; i < 5; i++) t.insert(15, (1 + i * 7) % 17, true);
  for (int i = 0; i < 10; i++) t.assign(2*i, 3*t[2*i]);
  for (size_t i = 0; i < t.size(); i++) t[i];
}

void test_erase() {
  Tester<int> t;

  for (int i = 0; i < 10; i++) t.insert(i, i, true);
  for (int i = 0; i < 10; i++) t.insert(i, -i, true);

  for (size_t i = 3; i < t.size(); i += 2) t.erase(i, true);
  for (size_t i = 0; i < t.size(); i++) t[i];

  for (int i = 0; i < 5; i++) t.insert(3, (1 + i * 7) % 17, true);
  for (size_t i = 1; i < t.size(); i += 3) t.erase(i, true);

  for (int i = 0; i < 20; i++) t.insert(3, 100 + i, true);

  for (int i = 0; i < 5; i++) t.erase(t.size() - 1, true);
  for (int i = 0; i < 5; i++) t.erase(0, true);

  for (int i = 0; i < 4; i++) t.insert(i, i, true);
  for (size_t i = 0; i < t.size(); i++) t[i];
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

  for (size_t i = 0; i < size; i++) {
    size_t pos = seq ? 0 : my_rand() % (i + 1);
    t.insert(pos, my_rand() % (3*size), check_tree);
  }

  t.check_tree();

  for (size_t i = 0; i < t.size(); i++) t[i];

  for (size_t i = 0; i < 30*size; i++) switch (my_rand() % 7) {
      case 1: {
        if (!erase && i % 3 == 0) break;
        size_t pos = seq ? 0 : my_rand() % (t.size() + 1);
        t.insert(pos, my_rand() % 1'000'000, check_tree);
        break;
      }
      case 2:
        if (erase) t.erase(my_rand() % t.size(), check_tree);
        break;
      case 3:
        t.assign(my_rand() % t.size(), 155 + i);
        break;
      default:
        t[my_rand() % t.size()];
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

    std::cout << "Bigger random test..." << std::endl;
    test_random(5'000);

    std::cout << "Bigger sequential test..." << std::endl;
    test_random(5'000, SEQ);

    std::cout << "All tests passed." << std::endl;
  } catch (const TestFailed& e) {
    std::cout << "Test failed: " << e.what() << std::endl;
  }
}

#endif


