#include <iostream>
#pragma warning(disable:4996)
using namespace std;

struct NODE {
   int data;      // key
   NODE* parent;   // parent
   NODE* left;      // left child
   NODE* right;   // right child
   int color;      // 1 : Red, 0 : Black
   NODE() {
      color = 0;
      parent = nullptr;
      left = NULL;
      right = NULL;
   }
   NODE(int key, NODE* p) {
      data = key;
      color = 1;
      parent = p;
   }
};

typedef NODE* NodePtr;

class RBT {
private:
   NodePtr root;
   NodePtr TNULL;
   
   NodePtr searchTreeHelper(NodePtr node, int key) {
      if (node == TNULL || key == node->data) return node;

      if (key < node->data) return searchTreeHelper(node->left, key);
      else return searchTreeHelper(node->right, key);
   }

   void fixInsert(NodePtr x) {
      NodePtr y;
      while (x != root && x->parent->color == 1) {
         if (x->parent == x->parent->parent->right) {
            y = x->parent->parent->left; 
            if (y->color == 1) {
               y->color = 0;
               x->parent->color = 0;
               x->parent->parent->color = 1;
               x = x->parent->parent;
            }
            else {
               if (x == x->parent->left) {
                  x = x->parent;
                  rightRotate(x);
               }
               x->parent->color = 0;
               x->parent->parent->color = 1;
               leftRotate(x->parent->parent);
            }
         }
         else {
            y = x->parent->parent->right;

            if (y->color == 1) {
               y->color = 0;
               x->parent->color = 0;
               x->parent->parent->color = 1;
               x = x->parent->parent;
            }
            else {
               if (x == x->parent->right) {
                  x = x->parent;
                  leftRotate(x);
               }
               x->parent->color = 0;
               x->parent->parent->color = 1;
               rightRotate(x->parent->parent);
            }
         }
      }
      root->color = 0;
   }

   void fixDelete(NodePtr node) {
      NodePtr uncle;
      while (node != root && node->color == 0) {
         if (node == node->parent->left) {
            uncle = node->parent->right;
            if (uncle->color == 1) {
               uncle->color = 0;
               node->parent->color = 1;
               leftRotate(node->parent);
               uncle = node->parent->right;
            }
            else {
               if ((uncle->left != nullptr && uncle->left->color == 0) && (uncle->right != nullptr && uncle->right->color == 0)) {
                  uncle->color = 1;
                  node = node->parent;
               }
               else {
                  if (uncle->right != nullptr && uncle->right->color == 0) {
                     uncle->left->color = 0;
                     uncle->color = 1;
                     rightRotate(uncle);
                     uncle = node->parent->right;
                  }

                  uncle->color = node->parent->color;
                  node->parent->color = 0;
                  uncle->right->color = 0;
                  leftRotate(node->parent);
                  node = root;
               }
            }            
         }
         else {
            uncle = node->parent->left;
            if (uncle->color == 1) {
               uncle->color = 0;
               node->parent->color = 1;
               rightRotate(node->parent);
               uncle = node->parent->left;
            }
            else {
               if ((uncle->left != nullptr && uncle->left->color == 0) && (uncle->right != nullptr && uncle->right->color == 0)) {
                  uncle->color = 1;
                  node = node->parent;
               }
               else {
                  if (uncle->left != nullptr && uncle->left->color == 0) {
                     uncle->right->color = 0;
                     uncle->color = 1;
                     leftRotate(uncle);
                     uncle = node->parent->left;
                  }

                  uncle->color = node->parent->color;
                  node->parent->color = 0;
                  uncle->left->color = 0;
                  rightRotate(node->parent);
                  node = root;
               }
            }
         }
      }
      node->color = 0;
   }

public:
   RBT() {
      TNULL = new NODE();
      root = TNULL;
   }

   NodePtr searchTree(int k) {
      return searchTreeHelper(this->root, k);
   }

   NodePtr minimum(NodePtr node) {
      while (node->left != TNULL) {
         node = node->left;
      }
      return node;
   }

   NodePtr successor(NodePtr x) {
      if (x->right != TNULL) {
         return minimum(x->right);
      }

      NodePtr y = x->parent;
      while (y != TNULL && x == y->right) {
         x = y;
         y = y->parent;
      }
      return y;
   }

   NodePtr maximum(NodePtr node) {
      while (node->right != TNULL) {
         node = node->right;
      }
      return node;
   }

   NodePtr predecessor(NodePtr x) {
      if (x->left != TNULL) {
         return maximum(x->left);
      }

      NodePtr y = x->parent;
      while (y != TNULL && x == y->left) {
         x = y;
         y = y->parent;
      }

      return y;
   }

   void leftRotate(NodePtr x) {
      NodePtr y = x->right;
      x->right = y->left;
      if (y->left != TNULL) y->left->parent = x;

      y->parent = x->parent;
      if (x->parent == nullptr) this->root = y;
      else if (x == x->parent->left) x->parent->left = y;
      else x->parent->right = y;

      y->left = x;
      x->parent = y;
   }

   void rightRotate(NodePtr x) {
      NodePtr y = x->left;
      x->left = y->right;
      if (y->right != TNULL) y->right->parent = x;

      y->parent = x->parent;
      if (x->parent == nullptr) this->root = y;
      else if (x == x->parent->right) x->parent->right = y;
      else x->parent->left = y;

      y->right = x;
      x->parent = y;
   }

   void insert(int key) {
      NodePtr node = new NODE;
      node->parent = nullptr;
      node->data = key;
      node->left = TNULL;
      node->right = TNULL;
      node->color = 1;

      NodePtr y = nullptr;
      NodePtr x = this->root;

      while (x != TNULL) {
         y = x;
         if (node->data < x->data) {
            x = x->left;
         }
         else {
            x = x->right;
         }
      }

      node->parent = y;
      if (y == nullptr) {
         root = node;
      }
      else if (node->data < y->data) {
         y->left = node;
      }
      else {
         y->right = node;
      }

      if (node->parent == nullptr) {
         node->color = 0;
         return;
      }
      if (node->parent->parent == nullptr) {
         return;
      }

      fixInsert(node);
   }

   void rbTransplant(NodePtr u, NodePtr v) {
      if (u->parent == nullptr) {
         root = v;
      }
      else if (u == u->parent->left) {
         u->parent->left = v;
      }
      else {
         u->parent->right = v;
      }
      v->parent = u->parent;
   }

   void deleteNode(int key) {
      NodePtr z = TNULL, x, y;
      NodePtr node = root;
      bool isLeft = 0;
      while (node != TNULL) {
         if (node->data == key) {
            z = node;
            break;
         }
         if (node->data < key) node = node->right, isLeft = 0;
         else node = node->left, isLeft = 1;
      }
      if (z == TNULL) return;

      y = z;

      int y_original_color = y->color;

      if (z->left == TNULL && z->right == TNULL) {
         if (z == root) root = TNULL, x = root;
         else {
            if (isLeft) z->parent->left = TNULL, x = z->parent->left;
            else z->parent->right = TNULL, x = z->parent->right;
            x->parent = z->parent;
         }
      }
      else if (z->left == TNULL) {
         x = z->right;
         rbTransplant(z, z->right);
      }
      else if (z->right == TNULL) {
         x = z->left;
         rbTransplant(z, z->left);
      }
      else {
         //나중에 successor로 변경
         //y = predecessor(z);
         y = successor(z);
         y_original_color = y->color;
         //y->right => y->left, y->left => y->right
         x = y->right;
         if (y->parent == z) x->parent = y;
         else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
         }
         rbTransplant(z, y);
         y->left = z->left;
         y->left->parent = y;
         y->color = z->color;
      }
      delete z;
      z = NULL;
      if (y_original_color == 0) fixDelete(x);
   }
};

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("rbt.inp", "r", stdin);
   freopen("rbt.out", "w", stdout);

   char op;
   int n;
   RBT rbtTree;

   while (cin >> op) {
      cin >> n;
      if (n == -1) 
         return 0;
      switch (op) {
      case 'i': rbtTree.insert(n); break;
      case 'd': rbtTree.deleteNode(n); break;
      case 'c': cout << "color(" << n << "): " << (rbtTree.searchTree(n)->color ? "RED" : "BLACK") << '\n'; break;
      }
   }
   return 0;
}