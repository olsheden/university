#ifndef __PROGTEST__
#include <cassert>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <random>
#include <type_traits>

#endif

struct Node{
    Node * parent;
    Node * left;
    Node * right;
    char value;
    size_t height;
    int m_balance;
    size_t nodes_left;
    size_t nodes_right;
    size_t lines_left;
    size_t lines_right;

    size_t balance() const{
      if(!left && !right) return 0;
      else if(!left && right) return right->height;
      else if(left && !right) return 0 - left->height;
      else return right->height - left->height;
    }

    Node(char value){
      parent = nullptr;
      left = nullptr;
      right = nullptr;
      this->value = value;
      height = 1;
      m_balance = 0;
      nodes_left = 0;
      nodes_right = 0;
      lines_left = 0;
      lines_right = 0;
    }
    ~Node(){}
};

struct TextEditorBackend {
    size_t ammount_lines;
    size_t ammount;
    Node * root;

    TextEditorBackend() {
      ammount = 0;
      ammount_lines = 1;
      root = nullptr;
    }

    void freeTree(Node * node){
      if(node){
        if(node->left)freeTree(node->left);
        if(node->right)freeTree(node->right);
        delete node;
      }
    }

    ~TextEditorBackend() {
      freeTree(root);
    }

    TextEditorBackend(const std::string& text) {
      ammount = 0;
      ammount_lines = 1;
      root = nullptr;
      for(size_t i = 0; i < text.size(); i++ ) {
        insert(i, text[i]);
      }
    }

    size_t size() const {
      return ammount;
    }
    size_t lines() const {
      return ammount_lines;
    }

    char at(size_t i) const {
      if(i >= size()) throw std::out_of_range("out of range");
      Node * tmp = root;
      while(tmp){
        if(i == tmp->nodes_left){
          return tmp->value;
        }
        else if(i < tmp->nodes_left){
          tmp = tmp->left;
        }
        else{
          i -= (tmp->nodes_left + 1);
          tmp = tmp->right;
        }
      }
      return root->value;
    }


    void edit(size_t i, char c) {
      if(i >= size()) throw std::out_of_range("out of range");
      int lines = 0;
      if(c == '\n') lines++;
      if(at(i) == '\n') lines--;
      ammount_lines+=lines;
      Node * tmp = root;
      while(tmp){
        if(i == tmp->nodes_left){
          tmp->value = c;
          return;
        }
        else if(i < tmp->nodes_left){
          tmp->lines_left += lines;
          tmp = tmp->left;
        }
        else{
          tmp->lines_right += lines;
          i -= (tmp->nodes_left + 1);
          tmp = tmp->right;
        }
      }
      return;
    }

    bool leftBalanceInsert(Node * x, Node * y){
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

    size_t newHeight(const Node * x) const{
      if(!x->left && !x->right) return 1;
      else if(!x->left && x->right) return x->right->height + 1;
      else if(x->left && !x->right) return x->left->height + 1;
      else return std::max(x->left->height, x->right->height) + 1;
    }

    bool rightBalanceInsert(Node * x, Node * y){
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

    void balanceInsert(Node * node){
      Node * tmp = node;
      while(tmp->parent){
        Node * prev = tmp;
        tmp = tmp->parent;
        if(prev == tmp->left){
          if(!leftBalanceInsert(tmp, prev)) return;
        }
        if(prev == tmp->right){
          if(!rightBalanceInsert(tmp, prev)) return;
        }
      }
    }

    void insert(size_t index, char c) {
      if(index > size()) throw std::out_of_range("out of range");
      Node * node = new Node(c);
      int line = 0;
      if(c == '\n') line = 1;
      ammount_lines += line;
      ammount++;
      if(!root){
        root = node;
        return;
      }
      Node * tmp = root;
      if(index == size() - 1){
        while(tmp->right){
          tmp->nodes_right++;
          tmp->lines_right+=line;
          tmp = tmp->right;
        }
        tmp->nodes_right++;
        tmp->lines_right+=line;
        tmp->right = node;
        node->parent = tmp;
        balanceInsert(node);
        return;
      }
      while(tmp) {
        if (index == tmp->nodes_left) {
          tmp->nodes_left++;
          tmp->lines_left+=line;
          if(!tmp->left){
            tmp->left = node;
          }
          else{
            tmp = findMax(tmp->left, line);
            tmp->right = node;
          }
          node->parent = tmp;
          balanceInsert(node);
          return;
        } else if (index < tmp->nodes_left) {
          tmp->nodes_left++;
          tmp->lines_left+=line;
          tmp = tmp->left;
        } else {
          tmp->nodes_right++;
          tmp->lines_right+=line;
          index -= (tmp->nodes_left + 1);
          tmp = tmp->right;
        }
      }
    }

    void rotateLeft(Node* x) const{
      Node * y = x->right;
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
      x->lines_right = count_Lines(x->right);
      x->lines_left = count_Lines(x->left);
      y->lines_left = count_Lines(y->left);
      y->lines_right = count_Lines(y->right);
    }

    size_t count_Nodes(Node * x) const{
      if(!x) return 0;
      return 1 + x->nodes_left + x->nodes_right;
    }

    size_t count_Lines(Node * x) const{
      if(!x) return 0;
      if(x->value == '\n') return 1 + x->lines_left + x->lines_right;
      else return 0 + x->lines_left + x->lines_right;
    }

    void rotateRight(Node* x) const{
      Node * y = x->left;
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
      x->lines_right = count_Lines(x->right);
      x->lines_left = count_Lines(x->left);
      y->lines_left = count_Lines(y->left);
      y->lines_right = count_Lines(y->right);
    }

    void bowSon(const bool & right, Node * parent, Node * son){
      if(right){
        parent->right = son;
      }
      else parent->left = son;
      if(son)son->parent = parent;
    }

    Node * findMax(Node * node, const int & line) const{
      node->nodes_right++;
      node->lines_right+=line;
      if(!node->right) return node;
      else{
        return findMax(node->right, line);
      }
    }

    Node * findMin(Node * node, const int & lines) const{
      node->nodes_left--;
      node->lines_left-=lines;
      if(!node->left) return node;
      else return findMin(node->left, lines);
    }

    Node * findMinLight(Node * node) const{
      if(!node->left) return node;
      else return findMinLight(node->left);
    }

    Node * leftBalanceDelete(Node * x, Node * y){
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

    Node * rightBalanceDelete(Node * x, Node * y){
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


    void balanceDelete(Node * node, Node * r, bool & rightson){
      Node * x = node;
      Node * y = r;

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

    void erase(size_t index) {
      if(index >= size()) throw std::out_of_range("out of range");
      int lines = 0;
      if(at(index) == '\n') lines++;
      ammount_lines-=lines;
      Node * tmp = root;
      bool rightSon = false;
      while(tmp){
        if(index == tmp->nodes_left){
          if(!tmp->right){
            bowSon(rightSon, tmp->parent, tmp->left);
          }
          else{
            if(findSucc(tmp)->value == '\n') lines = 1;
            else lines = 0;
            tmp->nodes_right--;
            tmp->lines_right-=lines;
            Node * son = findMin(tmp->right, lines);
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
          return;
        }
        else if(index < tmp->nodes_left){
          tmp->nodes_left--;
          tmp->lines_left-=lines;
          tmp = tmp->left;
          rightSon = false;
        }
        else{
          index -= (tmp->nodes_left + 1);
          tmp->nodes_right--;
          tmp->lines_right-=lines;
          tmp = tmp->right;
          rightSon = true;
        }
      }
    }

    Node * findSucc(Node * tmp) const {
      if(tmp->right) return findMinLight(tmp->right);
      Node * prev = tmp;
      tmp = tmp->parent;
      while(tmp && tmp->left != prev){
        prev = tmp;
        tmp = tmp->parent;
      }
      return tmp;
    }

    size_t line_start(size_t r) const {
      if(r >= lines()) throw std::out_of_range("out of range");
      Node * tmp = root;
      size_t res = 0;
      if(r == 0) {
        return 0;
      }
      r--;
      while(tmp) {
        if(r == tmp->lines_left  && tmp->value == '\n') {
          res+=tmp->nodes_left;
          return res + 1;
        }
        else if(r < tmp->lines_left ) {
          tmp = tmp->left;
        }
        else {
          r -= tmp->lines_left;
          res += tmp->nodes_left + 1;
          if(tmp->value == '\n') r--;
          tmp = tmp->right;
        }
      }
      return r;
    }

    size_t line_length(size_t r) const{
      if(r >= lines()) throw std::out_of_range("out of range");
      Node * tmp = root;
      size_t res = 0;
      if(r == 0) {
        while(tmp && tmp->left){
          tmp = tmp->left;
        }
        if(tmp)res++;
        while(tmp != nullptr && tmp->value != '\n'){
          tmp = findSucc(tmp);
          if(tmp)res++;
        }
        return res;
      }
      r--;
      while(tmp) {
        if(r == tmp->lines_left  && tmp->value == '\n') {
          tmp = findSucc(tmp);
          if(tmp)res++;
          while(tmp != nullptr && tmp->value != '\n'){
            tmp = findSucc(tmp);
            if(tmp)res++;
          }
          return res;
        }
        else if(r < tmp->lines_left ) {
          tmp = tmp->left;
        }
        else {
          r -= tmp->lines_left;
          if(tmp->value == '\n') r--;
          tmp = tmp->right;
        }
      }
      return r;
    }

    size_t char_to_line(size_t i) const {
      if(i >= size()) throw std::out_of_range("out of range");
      size_t res = 0;
      Node * tmp = root;
      while(tmp){
        if(i == tmp->nodes_left){
          res+=tmp->lines_left;   //dobavil
          return res;
        }
        else if(i < tmp->nodes_left){
          tmp = tmp->left;
        }
        else{
          i -= (tmp->nodes_left + 1);
          res+=tmp->lines_left;
          if(tmp->value == '\n') res++;
          tmp = tmp->right;
        }
      }
      return i;
    }
};

#ifndef __PROGTEST__

////////////////// Dark magic, ignore ////////////////////////

template < typename T >
auto quote(const T& t) { return t; }

std::string quote(const std::string& s) {
  std::string ret = "\"";
  for (char c : s) if (c != '\n') ret += c; else ret += "\\n";
  return ret + "\"";
}

#define STR_(a) #a
#define STR(a) STR_(a)

#define CHECK_(a, b, a_str, b_str) do { \
    auto _a = (a); \
    decltype(a) _b = (b); \
    if (_a != _b) { \
      std::cout << "Line " << __LINE__ << ": Assertion " \
        << a_str << " == " << b_str << " failed!" \
        << " (lhs: " << quote(_a) << ")" << std::endl; \
      fail++; \
    } else ok++; \
  } while (0)

#define CHECK(a, b) CHECK_(a, b, #a, #b)

#define CHECK_ALL(expr, ...) do { \
    std::array _arr = { __VA_ARGS__ }; \
    for (size_t _i = 0; _i < _arr.size(); _i++) \
      CHECK_((expr)(_i), _arr[_i], STR(expr) "(" << _i << ")", _arr[_i]); \
  } while (0)

#define CHECK_EX(expr, ex) do { \
    try { \
      (expr); \
      fail++; \
      std::cout << "Line " << __LINE__ << ": Expected " STR(expr) \
        " to throw " #ex " but no exception was raised." << std::endl; \
    } catch (const ex&) { ok++; \
    } catch (...) { \
      fail++; \
      std::cout << "Line " << __LINE__ << ": Expected " STR(expr) \
        " to throw " #ex " but got different exception." << std::endl; \
    } \
  } while (0)

////////////////// End of dark magic ////////////////////////


std::string text(const TextEditorBackend& t) {
  std::string ret;
  for (size_t i = 0; i < t.size(); i++) ret.push_back(t.at(i));
  return ret;
}

void test1(int& ok, int& fail) {
  TextEditorBackend s("aaaa\\n");
  CHECK(s.size(), 11);
  CHECK(text(s), "123\n456\n789");
  CHECK(s.lines(), 3);
  CHECK_ALL(s.char_to_line, 0,0,0,0, 1,1,1,1, 2,2,2);
  CHECK_ALL(s.line_start, 0, 4, 8);
  CHECK_ALL(s.line_length, 4, 4, 3);
}

void test2(int& ok, int& fail) {
  TextEditorBackend t("123\n456\n789\n");
  CHECK(t.size(), 12);
  CHECK(text(t), "123\n456\n789\n");
  CHECK(t.lines(), 4);
  CHECK_ALL(t.char_to_line, 0,0,0,0, 1,1,1,1, 2,2,2,2);
  CHECK_ALL(t.line_start, 0, 4, 8, 12);
  CHECK_ALL(t.line_length, 4, 4, 4, 0);
}

void test3(int& ok, int& fail) {
  TextEditorBackend t("asdfasdfasdf");

  CHECK(t.size(), 12);
  CHECK(text(t), "asdfasdfasdf");
  CHECK(t.lines(), 1);
  CHECK_ALL(t.char_to_line, 0,0,0,0, 0,0,0,0, 0,0,0,0);
  CHECK(t.line_start(0), 0);
  CHECK(t.line_length(0), 12);

  t.insert(0, '\n');
  CHECK(t.size(), 13);
  CHECK(text(t), "\nasdfasdfasdf");
  CHECK(t.lines(), 2);
  CHECK_ALL(t.line_start, 0, 1);

  t.insert(4, '\n');
  CHECK(t.size(), 14);
  CHECK(text(t), "\nasd\nfasdfasdf");
  CHECK(t.lines(), 3);
  CHECK_ALL(t.line_start, 0, 1, 5);

  t.insert(t.size(), '\n');
  CHECK(t.size(), 15);
  CHECK(text(t), "\nasd\nfasdfasdf\n");
  CHECK(t.lines(), 4);
  CHECK_ALL(t.line_start, 0, 1, 5, 15);

  t.edit(t.size() - 1, 'H');
  CHECK(t.size(), 15);
  CHECK(text(t), "\nasd\nfasdfasdfH");
  CHECK(t.lines(), 3);
  CHECK_ALL(t.line_start, 0, 1, 5);

  t.erase(8);
  CHECK(t.size(), 14);
  CHECK(text(t), "\nasd\nfasfasdfH");
  CHECK(t.lines(), 3);
  CHECK_ALL(t.line_start, 0, 1, 5);

  t.erase(4);
  CHECK(t.size(), 13);
  CHECK(text(t), "\nasdfasfasdfH");
  CHECK(t.lines(), 2);
  CHECK_ALL(t.line_start, 0, 1);
}

void test_ex(int& ok, int& fail) {
  TextEditorBackend t("123\n456\n789\n");
  CHECK_EX(t.at(12), std::out_of_range);

  CHECK_EX(t.insert(13, 'a'), std::out_of_range);
  CHECK_EX(t.edit(12, 'x'), std::out_of_range);
  CHECK_EX(t.erase(12), std::out_of_range);

  CHECK_EX(t.line_start(4), std::out_of_range);
  CHECK_EX(t.line_start(40), std::out_of_range);
  CHECK_EX(t.line_length(4), std::out_of_range);
  CHECK_EX(t.line_length(6), std::out_of_range);
  CHECK_EX(t.char_to_line(12), std::out_of_range);
  CHECK_EX(t.char_to_line(25), std::out_of_range);
}

int main() {
  int ok = 0, fail = 0;
  if (!fail) test1(ok, fail);
  if (!fail) test2(ok, fail);
  if (!fail) test3(ok, fail);
  if (!fail) test_ex(ok, fail);

  if (!fail) std::cout << "Passed all " << ok << " tests!" << std::endl;
  else std::cout << "Failed " << fail << " of " << (ok + fail) << " tests." << std::endl;
}

#endif


