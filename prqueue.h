#pragma once

#include <iostream>  // For debugging
#include <sstream>   // For as_string

using namespace std;

template <typename T>
class prqueue {
 public:
  struct NODE {
    int priority;
    T value;
    NODE* parent;
    NODE* left;
    NODE* right;
    NODE* link;  // Link to duplicates -- Part 2 only
  };

 private:
  NODE* root;
  size_t sz;

  // Utility pointers for begin and next.
  NODE* curr;
  NODE* temp;  // Optional

  // TODO_STUDENT: add private helper function definitions here

 public:
  /// Creates an empty `prqueue`.
  ///
  /// Runs in O(1).
  prqueue() {
    root = nullptr;
    sz = 0;

    curr = nullptr;
  }

  /// Returns the number of elements in the `prqueue`.
  ///
  /// Runs in O(1).
  size_t size() const {
    // TODO_STUDENT
    return sz;
  }

  /// Returns a pointer to the root node of the BST.
  ///
  /// Used for testing the internal structure of the BST. Do not edit or
  /// change.
  ///
  /// Runs in O(1).
  NODE* getRoot() {
    // TODO_STUDENT
    return root;
  }

  /// Adds `value` to the `prqueue` with the given `priority`.
  ///
  /// Uses the priority to determine the location in the underlying tree.
  ///
  /// Runs in O(H + M), where H is the height of the tree, and M is
  /// the number of duplicate priorities.
  /*
  void enqueue(T value, int priority) {
    // TODO_STUDENT
    Node* newNode;
    newNode->value = value;
    newNode->priority = priority;
    curr = root;

    if (curr == nullptr) {
      curr = newNode;
    }
    if (priority < curr->priority) {
      node->left = enqueue(node->left, value, priority);
    }
    else {
      node->right = enqueue(node->right, value, priority);
    }
    return
  }
  */

  void enqueue(T value, int priority) {
    NODE* newNode = new NODE();

    newNode->value = value;
    newNode->priority = priority;

    if (root == nullptr) {
      root = newNode;
      sz++;
      return;
    }
    curr = root;
    NODE* Tparent = nullptr;

    while (curr != nullptr) {
      Tparent = curr;
      if (priority < curr->priority) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    if (priority < Tparent->priority) {
      Tparent->left = newNode;
      sz++;
    } else {
      Tparent->right = newNode;
      sz++;
    }

    newNode->parent = Tparent;
  }

  /// Returns the value with the smallest priority in the `prqueue`, but does
  /// not modify the `prqueue`.
  ///
  /// If the `prqueue` is empty, returns the default value for `T`.
  ///
  /// Runs in O(H + M), where H is the height of the tree, and M is
  /// the number of duplicate priorities.

  // CAUSING MEMORY LEAK
  T peek() const {
    // TODO_STUDENT
    if (root == nullptr) {
      return T{};
    }

    NODE* currNode = root;
    // NODE* parentNode = currNode->parent;

    while (currNode->left != nullptr && currNode != nullptr) {
      currNode = currNode->left;
    }

    return currNode->value;
  }

  /// Returns the value with the smallest priority in the `prqueue` and
  /// removes it from the `prqueue`.
  ///
  /// If the `prqueue` is empty, returns the default value for `T`.
  ///
  /// Runs in O(H + M), where H is the height of the tree, and M is
  /// the number of duplicate priorities.

  T dequeue() {
    if (root == nullptr) {
      return T{};
    }

    NODE* currNode = root;

    while (currNode->left != nullptr && currNode != nullptr) {
      // currNode->parent = currNode;
      currNode = currNode->left;
    }

    T lowestVal = currNode->value;

    if (currNode->parent != nullptr) {
      if (currNode->right != nullptr) {
        currNode->right->parent = currNode->parent; //WHY?
        currNode->parent->left = currNode->right;
      } else {
        currNode->parent->left = nullptr;
      }
    }
    else {
      if (currNode->right != nullptr) {
        root = currNode->right;
        currNode->right->parent = nullptr; // WHY?
      } else {
        root= nullptr;
      }
    }

    delete currNode;
    sz--;

    return lowestVal;
  }

  /// Converts the `prqueue` to a string representation, with the values
  /// in-order by priority.
  ///
  /// Example:
  ///
  /// ```c++
  /// prqueue<string> names;
  /// names.enqueue("Gwen", 3);
  /// names.enqueue("Jen", 2);
  /// names.enqueue("Ben", 1);
  /// names.enqueue("Sven", 2);
  /// ```
  ///
  /// Calling `names.as_string()` would return the following multi-line
  /// string:
  ///
  /// ```text
  /// 1 value: Ben
  /// 2 value: Jen
  /// 2 value: Sven
  /// 3 value: Gwen
  /// ```
  ///
  /// Runs in O(N), where N is the number of values.

  void asStringHelp(NODE* node, std::ostringstream& os) {
    if (node == nullptr) {
      return;
    }
    asStringHelp(node->left, os);

    os << node->priority << " value: " << node->value << "\n";

    asStringHelp(node->right, os);
  }

  string as_string() {
    ostringstream os;
    asStringHelp(root, os);
    return os.str();
  }

  void destroy(NODE* node) {
    if (node == nullptr) {
      return;
    }
    // Recursively destroy left and right children first (post-order)
    destroy(node->left);
    destroy(node->right);
    // Delete the current node
    delete node;
    sz--;
  }

  /// Empties the `prqueue`, freeing all memory it controls.
  ///
  /// Runs in O(N), where N is the number of values.
  void clear() {
    NODE* node = root;
    destroy(node);

    sz = 0;
    root = nullptr;
  }

  /// Destructor, cleans up all memory associated with `prqueue`.
  ///
  /// Runs in O(N), where N is the number of values.
  ~prqueue() {
    clear();
  }

  /// Copy constructor.
  ///
  /// Copies the value-priority pairs from the provided `prqueue`.
  /// The internal tree structure must be copied exactly.
  ///
  /// Runs in O(N), where N is the number of values in `other`.
  prqueue(const prqueue& other) {
    // TODO_STUDENT
  }

  /// Assignment operator; `operator=`.
  ///
  /// Clears `this` tree, and copies the value-priority pairs from the
  /// provided `prqueue`. The internal tree structure must be copied exactly.
  ///
  /// Runs in O(N + O), where N is the number of values in `this`, and O is
  /// the number of values in `other`.
  prqueue& operator=(const prqueue& other) {
    // TODO_STUDENT
    return *this;
  }

  /// Checks if the contents of `this` and `other` are equivalent.
  ///
  /// Two `prqueues` are equivalent if they have the same priorities and
  /// values, as well as the same internal tree structure.
  ///
  /// These two `prqueue`s would be considered equivalent, because
  /// they have the same internal tree structure:
  ///
  /// ```c++
  /// prqueue<string> a;
  /// a.enqueue("2", 2);
  /// a.enqueue("1", 1);
  /// a.enqueue("3", 3);
  /// ```
  ///
  /// and
  ///
  /// ```c++
  /// prqueue<string> b;
  /// a.enqueue("2", 2);
  /// a.enqueue("3", 3);
  /// a.enqueue("1", 1);
  /// ```
  ///
  /// While this `prqueue`, despite containing the same priority-value pairs,
  /// would not be considered equivalent, because the internal tree structure
  /// is different.
  ///
  /// ```c++
  /// prqueue<string> c;
  /// a.enqueue("1", 1);
  /// a.enqueue("2", 2);
  /// a.enqueue("3", 3);
  /// ```
  ///
  /// Runs in O(N) time, where N is the maximum number of nodes in
  /// either `prqueue`.
  ///
  bool operator==(const prqueue& other) const {
    // TODO_STUDENT
    return false;
  }

  /// Resets internal state for an iterative inorder traversal.
  ///
  /// See `next` for usage details.
  ///
  /// O(H), where H is the maximum height of the tree.
  void begin() {
    // TODO_STUDENT
  }

  /// Uses the internal state to return the next in-order value and priority
  /// by reference, and advances the internal state. Returns true if the
  /// reference parameters were set, and false otherwise.
  ///
  /// Example usage:
  ///
  /// ```c++
  /// pq.begin();
  /// T value;
  /// int priority;
  /// while (pq.next(value, priority)) {
  ///   cout << priority << " value: " << value << endl;
  /// }
  /// ```
  ///
  /// Runs in worst-case O(H + M) or O(H), depending on implementation, where
  /// H is the height of the tree, and M is the number of duplicate
  /// priorities.
  bool next(T& value, int& priority) {
    // TODO_STUDENT
    return false;
  }
};
