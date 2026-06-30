# Data Structures in C — Complete Master Guide, Training Manual & Interview Handbook

> **Audience:** College Students · Software Engineers · Embedded Engineers · Linux Developers · System Programmers · FAANG Interview Candidates  
> **Level:** Beginner → Expert  
> **Author:** Senior C Programming Trainer & Data Structure Expert

---

## Table of Contents

1. [Data Structure Fundamentals](#1-data-structure-fundamentals)
2. [Classification of Data Structures](#2-classification-of-data-structures)
3. [Complexity Analysis](#3-complexity-analysis)
4. [Arrays In Depth](#4-arrays-in-depth)
5. [Linked Lists In Depth](#5-linked-lists-in-depth)
6. [Stack In Depth](#6-stack-in-depth)
7. [Queue In Depth](#7-queue-in-depth)
8. [Trees In Depth](#8-trees-in-depth)
9. [Binary Search Tree (BST)](#9-binary-search-tree-bst)
10. [AVL Trees](#10-avl-trees)
11. [Heaps](#11-heaps)
12. [Hashing In Depth](#12-hashing-in-depth)
13. [Graphs](#13-graphs)
14. [Advanced Data Structures](#14-advanced-data-structures)
15. [Dynamic Memory Management](#15-dynamic-memory-management)
16. [Searching Algorithms](#16-searching-algorithms)
17. [Sorting Algorithms](#17-sorting-algorithms)
18. [Applications of Data Structures](#18-applications-of-data-structures)
19. [50 Practical C Programs](#19-50-practical-c-programs)
20. [100+ Interview Questions & Answers](#20-100-interview-questions--answers)
21. [Tricky Interview Questions](#21-tricky-interview-questions)
22. [Real-World Case Studies](#22-real-world-case-studies)
23. [Common Mistakes](#23-common-mistakes)
24. [Best Practices](#24-best-practices)
25. [Memory Diagrams](#25-memory-diagrams)
26. [Complexity Reference Tables](#26-complexity-reference-tables)
27. [Learning & Interview Preparation Roadmap](#27-learning--interview-preparation-roadmap)

---

## 1. Data Structure Fundamentals

### What is a Data Structure?

A **Data Structure** is a systematic way of organizing, storing, and managing data in computer memory so that it can be accessed and modified efficiently.

```
Data Structure = Data + Relationships + Operations
```

| Component | Example (Linked List) |
|-----------|----------------------|
| Data | Integer values stored in nodes |
| Relationships | Each node points to the next |
| Operations | Insert, Delete, Search, Traverse |

### Why Data Structures are Needed

| Problem | Solution via DS |
|---------|----------------|
| Slow data access | Arrays for O(1) random access |
| Insertion/deletion overhead | Linked list for O(1) insert |
| Hierarchical data | Tree structures |
| Key-value lookup | Hash tables |
| Priority-based processing | Heap / Priority Queue |
| Shortest path problems | Graph + Dijkstra |

### Characteristics of a Good Data Structure

- **Correctness:** Implements its interface accurately.
- **Time efficiency:** Operations complete in minimum time.
- **Space efficiency:** Minimal memory footprint.
- **Simplicity:** Easy to implement and use.
- **Reusability:** Can be applied to multiple problems.

### Real-World Applications

| Domain | Data Structure Used |
|--------|-------------------|
| Browser history | Stack (Back/Forward) |
| Print spooler | Queue |
| File system | Tree |
| Database index | B-Tree / B+ Tree |
| Social network | Graph |
| Memory allocator | Free list / Heap |
| Compiler symbol table | Hash Table |
| Auto-complete (search) | Trie |
| Linux kernel task list | Doubly linked list |
| Network routing | Graph (Dijkstra) |

---

## 2. Classification of Data Structures

```
Data Structures
├── Primitive
│   ├── int, float, char, double, pointer
│   └── Directly supported by hardware/CPU
│
└── Non-Primitive
    ├── Linear
    │   ├── Static:  Array
    │   └── Dynamic: Linked List, Stack, Queue
    └── Non-Linear
        ├── Tree (Binary, BST, AVL, Heap, Trie, B-Tree)
        └── Graph (Directed, Undirected, Weighted)
```

### Comparison Table

| Property | Array | Linked List | Stack | Queue | Tree | Graph |
|----------|-------|-------------|-------|-------|------|-------|
| Access | O(1) | O(n) | O(n) | O(n) | O(log n) | O(V+E) |
| Insert | O(n) | O(1) | O(1) | O(1) | O(log n) | O(1) |
| Delete | O(n) | O(1) | O(1) | O(1) | O(log n) | O(1) |
| Memory | Contiguous | Non-contiguous | Contiguous/Dynamic | Both | Dynamic | Dynamic |
| Type | Static/Dynamic | Dynamic | Static/Dynamic | Static/Dynamic | Dynamic | Dynamic |

---

## 3. Complexity Analysis

### Time Complexity

Measures how runtime grows with input size `n`.

```
T(n) = number of basic operations as function of n
```

### Big O Notation (Upper Bound — Worst Case)

| Notation | Name | Example Algorithm |
|----------|------|------------------|
| O(1) | Constant | Array access, hash lookup |
| O(log n) | Logarithmic | Binary search, BST search |
| O(n) | Linear | Linear search, linked list traversal |
| O(n log n) | Linearithmic | Merge sort, heap sort |
| O(n²) | Quadratic | Bubble sort, selection sort |
| O(2ⁿ) | Exponential | Recursive Fibonacci (naïve) |
| O(n!) | Factorial | Permutation generation |

### Complexity Growth Chart

```
n=10:    O(1)=1  O(log n)≈3  O(n)=10   O(n²)=100      O(2ⁿ)=1024
n=100:   O(1)=1  O(log n)≈7  O(n)=100  O(n²)=10,000   O(2ⁿ)=huge
n=1000:  O(1)=1  O(log n)≈10 O(n)=1000 O(n²)=1,000,000
```

### Big Omega (Ω) — Lower Bound (Best Case)
### Big Theta (Θ) — Tight Bound (Average Case)

```c
// Example: Binary Search
// Best case:     Ω(1)    — target is at mid
// Average case:  Θ(log n)
// Worst case:    O(log n) — target at end or not found
```

---

## 4. Arrays In Depth

### Memory Representation

```
int arr[5] = {10, 20, 30, 40, 50};

Memory:
┌────┬────┬────┬────┬────┐
│ 10 │ 20 │ 30 │ 40 │ 50 │
└────┴────┴────┴────┴────┘
2000  2004  2008  2012  2016   ← addresses (4 bytes per int)

Address of arr[i] = base_address + i * sizeof(element)
arr[3] = 2000 + 3 * 4 = 2012
```

### Operations Complexity

| Operation | Time | Space |
|-----------|------|-------|
| Access arr[i] | O(1) | O(1) |
| Search (unsorted) | O(n) | O(1) |
| Search (sorted, binary) | O(log n) | O(1) |
| Insert at end | O(1) amortized | O(1) |
| Insert at position | O(n) | O(1) |
| Delete at position | O(n) | O(1) |
| Traverse | O(n) | O(1) |

### Advantages and Limitations

| Advantage | Limitation |
|-----------|-----------|
| O(1) random access | Fixed size (static arrays) |
| Cache-friendly (contiguous) | Insertion/deletion O(n) |
| Simple implementation | Wasted memory if underused |
| Supports multi-dimensional | Overflow if full |

### 2D Array Memory Layout (Row-Major Order)

```c
int matrix[3][4];
// Row 0: [0][0] [0][1] [0][2] [0][3]
// Row 1: [1][0] [1][1] [1][2] [1][3]
// Row 2: [2][0] [2][1] [2][2] [2][3]
//
// Address[i][j] = base + (i * COLS + j) * sizeof(int)
```

---

## 5. Linked Lists In Depth

### Node Structure

```c
// Singly Linked List Node
typedef struct Node {
    int          data;
    struct Node *next;
} Node;

// Doubly Linked List Node
typedef struct DNode {
    int           data;
    struct DNode *prev;
    struct DNode *next;
} DNode;
```

### Memory Layout

```
Singly Linked List: 10 → 20 → 30 → NULL

Node at 0x100:        Node at 0x200:        Node at 0x300:
┌──────┬──────┐       ┌──────┬──────┐       ┌──────┬──────┐
│  10  │0x200 │──────▶│  20  │0x300 │──────▶│  30  │ NULL │
└──────┴──────┘       └──────┴──────┘       └──────┴──────┘
 data   next           data   next           data   next
```

### Types Comparison

| Property | Singly | Doubly | Circular | Circular Doubly |
|----------|--------|--------|----------|----------------|
| Memory per node | 1 pointer | 2 pointers | 1 pointer | 2 pointers |
| Traversal | Forward only | Both directions | Forward loop | Both loop |
| Backward traversal | No | Yes | No | Yes |
| Use case | Simple list | Browser history | Round-robin | Deque |

### All Linked List Operations

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int data; struct Node *next; } Node;

// Create node
Node *create_node(int data) {
    Node *n = malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->data = data; n->next = NULL;
    return n;
}

// Insert at beginning
void insert_front(Node **head, int data) {
    Node *n = create_node(data);
    n->next = *head;
    *head = n;
}

// Insert at end
void insert_end(Node **head, int data) {
    Node *n = create_node(data);
    if (!*head) { *head = n; return; }
    Node *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = n;
}

// Insert at position (1-indexed)
void insert_at(Node **head, int data, int pos) {
    if (pos <= 1) { insert_front(head, data); return; }
    Node *n = create_node(data);
    Node *cur = *head;
    for (int i = 1; cur && i < pos - 1; i++) cur = cur->next;
    if (!cur) { free(n); return; }
    n->next = cur->next;
    cur->next = n;
}

// Delete at beginning
void delete_front(Node **head) {
    if (!*head) return;
    Node *tmp = *head;
    *head = (*head)->next;
    free(tmp);
}

// Delete at end
void delete_end(Node **head) {
    if (!*head) return;
    if (!(*head)->next) { free(*head); *head = NULL; return; }
    Node *cur = *head;
    while (cur->next->next) cur = cur->next;
    free(cur->next);
    cur->next = NULL;
}

// Delete by value
void delete_value(Node **head, int val) {
    if (!*head) return;
    if ((*head)->data == val) { delete_front(head); return; }
    Node *cur = *head;
    while (cur->next && cur->next->data != val) cur = cur->next;
    if (cur->next) {
        Node *tmp = cur->next;
        cur->next = tmp->next;
        free(tmp);
    }
}

// Search
Node *search(Node *head, int val) {
    while (head) {
        if (head->data == val) return head;
        head = head->next;
    }
    return NULL;
}

// Traverse / Print
void print_list(Node *head) {
    while (head) { printf("%d → ", head->data); head = head->next; }
    printf("NULL\n");
}

// Reverse
void reverse(Node **head) {
    Node *prev = NULL, *cur = *head, *nxt;
    while (cur) { nxt = cur->next; cur->next = prev; prev = cur; cur = nxt; }
    *head = prev;
}

// Detect loop (Floyd's algorithm)
int has_loop(Node *head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;
    }
    return 0;
}

// Free entire list
void free_list(Node **head) {
    Node *cur = *head, *nxt;
    while (cur) { nxt = cur->next; free(cur); cur = nxt; }
    *head = NULL;
}
```

---

## 6. Stack In Depth

### LIFO Principle

```
Stack operations:    PUSH 10 → PUSH 20 → PUSH 30

      ┌────┐
      │ 30 │ ← TOP
      ├────┤
      │ 20 │
      ├────┤
      │ 10 │
      └────┘

POP → returns 30  (Last In, First Out)
```

### Stack Using Array

```c
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void stack_init(Stack *s)      { s->top = -1; }
int  stack_is_empty(Stack *s)  { return s->top == -1; }
int  stack_is_full(Stack *s)   { return s->top == MAX_SIZE - 1; }

int stack_push(Stack *s, int val) {
    if (stack_is_full(s))  { fprintf(stderr, "Stack overflow\n"); return 0; }
    s->data[++s->top] = val;
    return 1;
}

int stack_pop(Stack *s, int *val) {
    if (stack_is_empty(s)) { fprintf(stderr, "Stack underflow\n"); return 0; }
    *val = s->data[s->top--];
    return 1;
}

int stack_peek(Stack *s, int *val) {
    if (stack_is_empty(s)) return 0;
    *val = s->data[s->top];
    return 1;
}
```

### Stack Using Linked List

```c
typedef struct SNode { int data; struct SNode *next; } SNode;
typedef struct { SNode *top; int size; } LStack;

void ls_init(LStack *s) { s->top = NULL; s->size = 0; }

void ls_push(LStack *s, int val) {
    SNode *n = malloc(sizeof(SNode));
    n->data = val; n->next = s->top;
    s->top = n; s->size++;
}

int ls_pop(LStack *s, int *val) {
    if (!s->top) return 0;
    SNode *tmp = s->top;
    *val = tmp->data;
    s->top = tmp->next;
    free(tmp); s->size--;
    return 1;
}
```

### Stack Application: Parenthesis Matching

```c
int is_balanced(const char *expr) {
    Stack s; stack_init(&s);
    for (int i = 0; expr[i]; i++) {
        char c = expr[i];
        if (c == '(' || c == '[' || c == '{')
            stack_push(&s, c);
        else if (c == ')' || c == ']' || c == '}') {
            int top; if (!stack_pop(&s, &top)) return 0;
            if ((c==')' && top!='(') || (c==']' && top!='[') || (c=='}' && top!='{'))
                return 0;
        }
    }
    return stack_is_empty(&s);
}
```

### Applications Summary

| Application | How Stack is Used |
|-------------|-------------------|
| Function call | Call stack — store return address & local vars |
| Expression eval | Infix → Postfix → Evaluate |
| Parenthesis check | Push open, pop on close |
| Undo/Redo | Push operations, pop to undo |
| Backtracking | Store states, pop on dead end |
| Browser back | Push URLs, pop on Back |

---

## 7. Queue In Depth

### FIFO Principle

```
ENQUEUE: 10 → 20 → 30

FRONT → [10][20][30] ← REAR

DEQUEUE → returns 10  (First In, First Out)
```

### Simple Queue Using Array

```c
#define QMAX 100
typedef struct {
    int data[QMAX];
    int front, rear, size;
} Queue;

void queue_init(Queue *q) { q->front = 0; q->rear = -1; q->size = 0; }
int  queue_empty(Queue *q) { return q->size == 0; }
int  queue_full(Queue *q)  { return q->size == QMAX; }

int enqueue(Queue *q, int val) {
    if (queue_full(q)) return 0;
    q->rear = (q->rear + 1) % QMAX;
    q->data[q->rear] = val;
    q->size++;
    return 1;
}

int dequeue(Queue *q, int *val) {
    if (queue_empty(q)) return 0;
    *val = q->data[q->front];
    q->front = (q->front + 1) % QMAX;
    q->size--;
    return 1;
}
```

### Circular Queue Memory Layout

```
Array (size=5): indices 0-4
After: enqueue(10), enqueue(20), enqueue(30), dequeue() → 10

front=1  rear=2
┌────┬────┬────┬────┬────┐
│ -- │ 20 │ 30 │ -- │ -- │
└────┴────┴────┴────┴────┘
  0    1    2    3    4
       ^    ^
     front rear

Circular: rear = (rear+1) % SIZE wraps around
```

### Priority Queue Concept

```c
typedef struct { int data; int priority; } PQNode;

// Min-heap based priority queue:
// Always dequeue the element with LOWEST priority number first
// Used in: Dijkstra's, CPU scheduling, Huffman coding
```

### Queue Types

| Type | Description | Use Case |
|------|-------------|----------|
| Simple Queue | FIFO, linear | Print spooler |
| Circular Queue | FIFO, wraps around | CPU scheduling |
| Priority Queue | Ordered by priority | Dijkstra, OS scheduler |
| Deque | Insert/Delete at both ends | Sliding window max |

---

## 8. Trees In Depth

### Terminology

```
              A          ← Root (level 0)
            /   \
           B     C       ← level 1
          / \     \
         D   E     F     ← level 2 (D,E,F = Leaf nodes)

Height of tree = 2 (longest path from root to leaf)
Depth of B = 1 (distance from root)
Degree of A = 2 (number of children)
Degree of B = 2
Degree of C = 1
```

### Tree Terminology Table

| Term | Definition |
|------|-----------|
| Root | Topmost node, no parent |
| Parent | Node with children |
| Child | Nodes connected below a parent |
| Leaf | Node with no children |
| Height | Longest path from node to leaf |
| Depth | Distance from root to node |
| Degree | Number of children |
| Level | Depth + 1 |
| Subtree | Any node + its descendants |

### Binary Tree Types

```
Full Binary Tree:          Complete Binary Tree:
    1                          1
   / \                        / \
  2   3                      2   3
 / \ / \                    / \ /
4  5 6  7                  4  5 6

Perfect Binary Tree:       Balanced Binary Tree:
    1                          1
   / \                        / \
  2   3                      2   3
 / \ / \                    / \
4  5 6  7                  4   5
(all levels full)          (height difference ≤ 1)
```

### Binary Tree Traversals

```
Tree:
      1
     / \
    2   3
   / \
  4   5

Inorder   (L-Root-R): 4 2 5 1 3
Preorder  (Root-L-R): 1 2 4 5 3
Postorder (L-R-Root): 4 5 2 3 1
Level Order (BFS):    1 2 3 4 5
```

### Traversal Implementation

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct TNode { int data; struct TNode *left, *right; } TNode;

TNode *new_node(int val) {
    TNode *n = malloc(sizeof(TNode));
    n->data = val; n->left = n->right = NULL;
    return n;
}

void inorder(TNode *root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(TNode *root) {
    if (!root) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(TNode *root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// Level-order (BFS) using queue
void level_order(TNode *root) {
    if (!root) return;
    TNode *queue[1000]; int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        TNode *cur = queue[front++];
        printf("%d ", cur->data);
        if (cur->left)  queue[rear++] = cur->left;
        if (cur->right) queue[rear++] = cur->right;
    }
}

int height(TNode *root) {
    if (!root) return 0;
    int lh = height(root->left), rh = height(root->right);
    return 1 + (lh > rh ? lh : rh);
}
```

---

## 9. Binary Search Tree (BST)

### BST Property

```
For every node N:
  All values in LEFT subtree < N->data
  All values in RIGHT subtree > N->data

Example BST:
        50
       /  \
      30   70
     / \   / \
    20  40 60  80
```

### BST Operations

```c
typedef struct BST { int data; struct BST *left, *right; } BST;

// Insert
BST *bst_insert(BST *root, int val) {
    if (!root) {
        BST *n = malloc(sizeof(BST));
        n->data = val; n->left = n->right = NULL;
        return n;
    }
    if (val < root->data) root->left  = bst_insert(root->left,  val);
    else if (val > root->data) root->right = bst_insert(root->right, val);
    return root;
}

// Search
BST *bst_search(BST *root, int val) {
    if (!root || root->data == val) return root;
    if (val < root->data) return bst_search(root->left, val);
    return bst_search(root->right, val);
}

// Find minimum (leftmost node)
BST *bst_min(BST *root) {
    while (root->left) root = root->left;
    return root;
}

// Delete
BST *bst_delete(BST *root, int val) {
    if (!root) return NULL;
    if (val < root->data) {
        root->left = bst_delete(root->left, val);
    } else if (val > root->data) {
        root->right = bst_delete(root->right, val);
    } else {
        // Case 1: leaf node
        if (!root->left && !root->right) { free(root); return NULL; }
        // Case 2: one child
        if (!root->left)  { BST *t = root->right; free(root); return t; }
        if (!root->right) { BST *t = root->left;  free(root); return t; }
        // Case 3: two children — replace with inorder successor
        BST *succ = bst_min(root->right);
        root->data = succ->data;
        root->right = bst_delete(root->right, succ->data);
    }
    return root;
}
```

### BST Complexity

| Operation | Average | Worst (skewed) |
|-----------|---------|----------------|
| Search | O(log n) | O(n) |
| Insert | O(log n) | O(n) |
| Delete | O(log n) | O(n) |

**Why worst case O(n)?** When inserting sorted data (1,2,3,4...), BST degenerates into a linked list. **Solution:** AVL Tree or Red-Black Tree.

---

## 10. AVL Trees

### Why AVL?

BST with sorted input becomes O(n). AVL Tree self-balances after every insert/delete, guaranteeing O(log n) always.

### Balance Factor

```
Balance Factor (BF) = Height(Left Subtree) - Height(Right Subtree)

AVL invariant: BF ∈ {-1, 0, +1} for every node

If BF = +2 or BF = -2 → ROTATION needed
```

### Four Rotation Cases

```
LL Rotation (Right Rotation):          RR Rotation (Left Rotation):
      Z(BF=+2)                               Z(BF=-2)
     /                                              \
    Y(BF=+1)      →  Y                              Y(BF=-1)   →  Y
   /                / \                                \           / \
  X                X   Z                               X          Z   X

LR Rotation:                           RL Rotation:
      Z(+2)                                  Z(-2)
     /                                              \
    X(-1)  →  Left on X, then Right on Z          X(+1)  → Right on X, then Left on Z
     \                                            /
      Y                                          Y
```

### AVL Insert with Rotations

```c
typedef struct AVL { int data, height; struct AVL *left, *right; } AVL;

int avl_height(AVL *n)  { return n ? n->height : 0; }
int avl_bf(AVL *n)      { return n ? avl_height(n->left) - avl_height(n->right) : 0; }
int avl_max(int a,int b){ return a > b ? a : b; }

void avl_update_height(AVL *n) {
    if (n) n->height = 1 + avl_max(avl_height(n->left), avl_height(n->right));
}

AVL *avl_right_rotate(AVL *z) {
    AVL *y = z->left, *T3 = y->right;
    y->right = z; z->left = T3;
    avl_update_height(z); avl_update_height(y);
    return y;
}

AVL *avl_left_rotate(AVL *z) {
    AVL *y = z->right, *T2 = y->left;
    y->left = z; z->right = T2;
    avl_update_height(z); avl_update_height(y);
    return y;
}

AVL *avl_insert(AVL *root, int val) {
    if (!root) {
        AVL *n = malloc(sizeof(AVL));
        n->data = val; n->height = 1; n->left = n->right = NULL;
        return n;
    }
    if (val < root->data)      root->left  = avl_insert(root->left,  val);
    else if (val > root->data) root->right = avl_insert(root->right, val);
    else return root;  // duplicates not allowed

    avl_update_height(root);
    int bf = avl_bf(root);

    if (bf >  1 && val < root->left->data)   return avl_right_rotate(root);   // LL
    if (bf < -1 && val > root->right->data)  return avl_left_rotate(root);    // RR
    if (bf >  1 && val > root->left->data) { root->left  = avl_left_rotate(root->left);  return avl_right_rotate(root); } // LR
    if (bf < -1 && val < root->right->data){ root->right = avl_right_rotate(root->right); return avl_left_rotate(root); } // RL
    return root;
}
```

### AVL Complexity

| Operation | Time |
|-----------|------|
| Insert | O(log n) |
| Delete | O(log n) |
| Search | O(log n) |
| Height | Always O(log n) |

---

## 11. Heaps

### Structure

A **Complete Binary Tree** where every parent satisfies the heap property:

```
Max Heap: Parent ≥ Children     Min Heap: Parent ≤ Children

Max Heap:                       Min Heap:
        90                              1
       /  \                            / \
      80   70                         3   2
     / \   / \                       / \ / \
    40  50 60  65                   7  4 5  6
```

### Array Representation

```
Heap array index:  0   1   2   3   4   5   6
Max Heap values: [90, 80, 70, 40, 50, 60, 65]

For index i:
  Parent:       (i - 1) / 2
  Left child:   2*i + 1
  Right child:  2*i + 2
```

### Heap Operations

```c
#define HEAP_MAX 1000

typedef struct { int data[HEAP_MAX]; int size; } MaxHeap;

void heap_swap(MaxHeap *h, int i, int j) {
    int t = h->data[i]; h->data[i] = h->data[j]; h->data[j] = t;
}

// Heapify up (after insert)
void heapify_up(MaxHeap *h, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->data[parent] < h->data[i]) {
            heap_swap(h, parent, i);
            i = parent;
        } else break;
    }
}

// Heapify down (after extract)
void heapify_down(MaxHeap *h, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if (l < h->size && h->data[l] > h->data[largest]) largest = l;
    if (r < h->size && h->data[r] > h->data[largest]) largest = r;
    if (largest != i) { heap_swap(h, i, largest); heapify_down(h, largest); }
}

void heap_insert(MaxHeap *h, int val) {
    h->data[h->size++] = val;
    heapify_up(h, h->size - 1);
}

int heap_extract_max(MaxHeap *h) {
    int max = h->data[0];
    h->data[0] = h->data[--h->size];
    heapify_down(h, 0);
    return max;
}

// Heap Sort
void heap_sort(int *arr, int n) {
    MaxHeap h; h.size = 0;
    for (int i = 0; i < n; i++) heap_insert(&h, arr[i]);
    for (int i = n - 1; i >= 0; i--) arr[i] = heap_extract_max(&h);
}
```

---

## 12. Hashing In Depth

### Concept

```
Key → [Hash Function] → Index → [Hash Table]

hash_index = hash_function(key) % TABLE_SIZE
```

### Hash Functions

```c
// Division method
int hash_div(int key, int size)   { return key % size; }

// Folding method (for strings)
unsigned int hash_str(const char *s, int size) {
    unsigned int h = 5381;
    while (*s) h = ((h << 5) + h) + (unsigned char)*s++;
    return h % size;
}
```

### Collision Resolution

#### Chaining (Separate Chaining)

```c
#define TABLE_SIZE 10

typedef struct HNode { int key; int value; struct HNode *next; } HNode;
typedef struct { HNode *table[TABLE_SIZE]; } HashTable;

void ht_init(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) ht->table[i] = NULL;
}

void ht_insert(HashTable *ht, int key, int value) {
    int idx = hash_div(key, TABLE_SIZE);
    HNode *n = malloc(sizeof(HNode));
    n->key = key; n->value = value; n->next = ht->table[idx];
    ht->table[idx] = n;
}

int ht_get(HashTable *ht, int key, int *value) {
    int idx = hash_div(key, TABLE_SIZE);
    HNode *cur = ht->table[idx];
    while (cur) {
        if (cur->key == key) { *value = cur->value; return 1; }
        cur = cur->next;
    }
    return 0;
}
```

#### Open Addressing — Linear Probing

```c
#define OA_SIZE 11
#define EMPTY   -1
#define DELETED -2

typedef struct { int keys[OA_SIZE]; int vals[OA_SIZE]; } OATable;

void oa_init(OATable *t) {
    for (int i = 0; i < OA_SIZE; i++) t->keys[i] = EMPTY;
}

void oa_insert(OATable *t, int key, int val) {
    int idx = key % OA_SIZE;
    while (t->keys[idx] != EMPTY && t->keys[idx] != DELETED && t->keys[idx] != key)
        idx = (idx + 1) % OA_SIZE;   // Linear probe
    t->keys[idx] = key;
    t->vals[idx] = val;
}
```

### Collision Techniques Comparison

| Method | Pros | Cons |
|--------|------|------|
| Chaining | Simple, handles high load | Extra memory for pointers |
| Linear Probing | Cache-friendly | Clustering problem |
| Quadratic Probing | Reduces clustering | May not find empty slot |
| Double Hashing | Minimal clustering | Two hash functions needed |

### Load Factor

```
Load Factor (α) = Number of entries / Table size

α < 0.7  → Good performance
α > 0.7  → Resize/rehash recommended
```

---

## 13. Graphs

### Terminology

```
Graph G = (V, E)   where V = vertices, E = edges

Directed (Digraph):     Undirected:
  A → B                   A — B
  A → C                   A — C
  B → C                   B — C
```

### Representations

#### Adjacency Matrix

```c
#define V 5
int adj_matrix[V][V] = {0};

// Add edge A(0) → B(1):
adj_matrix[0][1] = 1;       // Directed
adj_matrix[0][1] = adj_matrix[1][0] = 1;  // Undirected

// Space: O(V²) — good for dense graphs
// Edge check: O(1)
```

#### Adjacency List

```c
// Space: O(V+E) — good for sparse graphs
typedef struct GNode { int vertex; struct GNode *next; } GNode;
typedef struct { GNode *head[V]; } Graph;

void add_edge(Graph *g, int src, int dst) {
    GNode *n = malloc(sizeof(GNode));
    n->vertex = dst; n->next = g->head[src]; g->head[src] = n;
    // For undirected, also add: dst → src
}
```

### BFS — Breadth First Search

```c
#include <string.h>

void bfs(Graph *g, int start) {
    int visited[V]; memset(visited, 0, sizeof(visited));
    int queue[V], front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);
        for (GNode *n = g->head[v]; n; n = n->next) {
            if (!visited[n->vertex]) {
                visited[n->vertex] = 1;
                queue[rear++] = n->vertex;
            }
        }
    }
}
// Time: O(V+E)   Space: O(V)
```

### DFS — Depth First Search

```c
void dfs_helper(Graph *g, int v, int *visited) {
    visited[v] = 1;
    printf("%d ", v);
    for (GNode *n = g->head[v]; n; n = n->next)
        if (!visited[n->vertex])
            dfs_helper(g, n->vertex, visited);
}

void dfs(Graph *g, int start) {
    int visited[V]; memset(visited, 0, sizeof(visited));
    dfs_helper(g, start, visited);
}
// Time: O(V+E)   Space: O(V) recursive stack
```

### BFS vs DFS

| Property | BFS | DFS |
|----------|-----|-----|
| Data structure | Queue | Stack (recursion) |
| Finds shortest path | Yes (unweighted) | No |
| Memory | O(V) — can be high | O(depth) — usually less |
| Complete | Yes | Yes |
| Use case | Shortest path, web crawl | Topological sort, maze |

---

## 14. Advanced Data Structures

### Trie (Prefix Tree)

```c
#define ALPHA 26
typedef struct Trie { struct Trie *children[ALPHA]; int is_end; } Trie;

Trie *trie_new_node(void) {
    Trie *n = calloc(1, sizeof(Trie));
    return n;
}

void trie_insert(Trie *root, const char *word) {
    Trie *cur = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!cur->children[idx])
            cur->children[idx] = trie_new_node();
        cur = cur->children[idx];
    }
    cur->is_end = 1;
}

int trie_search(Trie *root, const char *word) {
    Trie *cur = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!cur->children[idx]) return 0;
        cur = cur->children[idx];
    }
    return cur->is_end;
}
// Insert/Search: O(L) where L = word length
// Use case: autocomplete, spell check, IP routing
```

### Disjoint Set (Union-Find)

```c
#define N 100
int parent[N], rank_arr[N];

void ds_init(int n) {
    for (int i = 0; i < n; i++) { parent[i] = i; rank_arr[i] = 0; }
}

int ds_find(int x) {
    if (parent[x] != x) parent[x] = ds_find(parent[x]);  // path compression
    return parent[x];
}

void ds_union(int x, int y) {
    int px = ds_find(x), py = ds_find(y);
    if (px == py) return;
    if (rank_arr[px] < rank_arr[py]) parent[px] = py;
    else if (rank_arr[px] > rank_arr[py]) parent[py] = px;
    else { parent[py] = px; rank_arr[px]++; }
}

int ds_connected(int x, int y) { return ds_find(x) == ds_find(y); }
// find/union: nearly O(1) amortized (inverse Ackermann)
// Use: Kruskal's MST, cycle detection, network connectivity
```

### Segment Tree

```c
#define SEGTREE_MAX 4*1000

int seg[SEGTREE_MAX];

void seg_build(int *arr, int node, int start, int end) {
    if (start == end) { seg[node] = arr[start]; return; }
    int mid = (start + end) / 2;
    seg_build(arr, 2*node,   start,   mid);
    seg_build(arr, 2*node+1, mid+1,   end);
    seg[node] = seg[2*node] + seg[2*node+1];   // Sum tree
}

int seg_query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return seg[node];
    int mid = (start + end) / 2;
    return seg_query(2*node, start, mid, l, r) +
           seg_query(2*node+1, mid+1, end, l, r);
}
// Build: O(n), Query: O(log n), Update: O(log n)
// Use: Range sum, range min/max queries
```

### Red-Black Tree Properties

1. Every node is RED or BLACK.
2. Root is BLACK.
3. Every leaf (NULL) is BLACK.
4. If a node is RED, both children are BLACK.
5. All paths from a node to its NULL leaves have same number of BLACK nodes.

**Guarantees:** Height ≤ 2 log(n+1) → All operations O(log n). Used in Linux kernel (`struct rb_root`), C++ `std::map`.

### B-Tree and B+ Tree

| Property | B-Tree | B+ Tree |
|----------|--------|---------|
| Data location | All nodes | Leaf nodes only |
| Leaf connection | No | Yes (linked list) |
| Range queries | Less efficient | Very efficient |
| Use case | File systems | Database indexes |

---

## 15. Dynamic Memory Management

### malloc / calloc / realloc / free

```c
#include <stdlib.h>
#include <string.h>

// malloc: allocates n bytes, uninitialized
int *arr = malloc(10 * sizeof(int));
if (!arr) { perror("malloc"); exit(1); }

// calloc: allocates n elements, zero-initialized
int *zeros = calloc(10, sizeof(int));   // All elements = 0

// realloc: resize existing allocation
arr = realloc(arr, 20 * sizeof(int));   // Grow to 20 elements
if (!arr) { /* handle — original pointer may be freed! */ }

// free: release memory
free(arr);    arr = NULL;   // ALWAYS nullify after free
free(zeros);  zeros = NULL;
```

### Memory Layout of Dynamic Linked List

```
Stack:           Heap (scattered):
┌──────┐         ┌──────────┐  ┌──────────┐  ┌──────────┐
│ head ├────────▶│ data:10  │  │ data:20  │  │ data:30  │
│      │         │ next:────┼─▶│ next:────┼─▶│ next:NULL│
└──────┘         └──────────┘  └──────────┘  └──────────┘
                 addr: 0xA100  addr: 0xB300  addr: 0xC500
```

### Memory Leak Example and Fix

```c
// WRONG — memory leak:
void process(void) {
    int *buf = malloc(1024 * sizeof(int));
    // ... use buf ...
    return;   // LEAK: buf never freed!
}

// CORRECT:
void process(void) {
    int *buf = malloc(1024 * sizeof(int));
    if (!buf) return;
    // ... use buf ...
    free(buf);   // Always free before return
    buf = NULL;
}
```

### Dangling Pointer

```c
// WRONG:
int *p = malloc(sizeof(int));
free(p);
*p = 10;   // UNDEFINED BEHAVIOR — dangling pointer!

// CORRECT:
free(p);
p = NULL;   // Nullify immediately
```

---

## 16. Searching Algorithms

### Linear Search

```c
int linear_search(int *arr, int n, int target) {
    for (int i = 0; i < n; i++)
        if (arr[i] == target) return i;
    return -1;
}
// Time: O(n)  Space: O(1)  Works on unsorted arrays
```

### Binary Search

```c
int binary_search(int *arr, int n, int target) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;   // Avoids overflow vs (lo+hi)/2
        if (arr[mid] == target) return mid;
        if (arr[mid] < target)  lo = mid + 1;
        else                    hi = mid - 1;
    }
    return -1;
}
// Time: O(log n)  Space: O(1)  Requires sorted array
```

### Comparison

| Algorithm | Best | Average | Worst | Sorted? |
|-----------|------|---------|-------|---------|
| Linear | O(1) | O(n) | O(n) | No |
| Binary | O(1) | O(log n) | O(log n) | Yes |

---

## 17. Sorting Algorithms

### Bubble Sort

```c
void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int swapped = 0;
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t;
                swapped = 1;
            }
        if (!swapped) break;   // Optimization: already sorted
    }
}
```

### Selection Sort

```c
void selection_sort(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx]) min_idx = j;
        int t = arr[i]; arr[i] = arr[min_idx]; arr[min_idx] = t;
    }
}
```

### Insertion Sort

```c
void insertion_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) { arr[j+1] = arr[j]; j--; }
        arr[j+1] = key;
    }
}
```

### Merge Sort

```c
void merge(int *arr, int l, int m, int r) {
    int n1 = m-l+1, n2 = r-m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l+i];
    for (int i = 0; i < n2; i++) R[i] = arr[m+1+i];
    int i=0, j=0, k=l;
    while (i<n1 && j<n2) arr[k++] = (L[i]<=R[j]) ? L[i++] : R[j++];
    while (i<n1) arr[k++] = L[i++];
    while (j<n2) arr[k++] = R[j++];
}

void merge_sort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r-l)/2;
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
```

### Quick Sort

```c
int partition(int *arr, int lo, int hi) {
    int pivot = arr[hi], i = lo - 1;
    for (int j = lo; j < hi; j++)
        if (arr[j] <= pivot) { i++; int t = arr[i]; arr[i] = arr[j]; arr[j] = t; }
    int t = arr[i+1]; arr[i+1] = arr[hi]; arr[hi] = t;
    return i + 1;
}

void quick_sort(int *arr, int lo, int hi) {
    if (lo < hi) {
        int pi = partition(arr, lo, hi);
        quick_sort(arr, lo, pi-1);
        quick_sort(arr, pi+1, hi);
    }
}
```

### Sorting Complexity Table

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Bubble | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection | O(n²) | O(n²) | O(n²) | O(1) | No |
| Insertion | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Merge | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap | O(n log n) | O(n log n) | O(n log n) | O(1) | No |

---

## 18. Applications of Data Structures

| Domain | Data Structure | Use |
|--------|---------------|-----|
| OS Process Scheduling | Queue / Heap | Round-robin, priority scheduling |
| Compiler Symbol Table | Hash Table | Variable/function lookup |
| File System (FAT/ext4) | Tree / Linked List | Directory hierarchy |
| Network Routing | Graph (Dijkstra) | Shortest path |
| Linux Kernel Task List | Doubly Linked List | `list_head` in `task_struct` |
| Linux Kernel CFS Scheduler | Red-Black Tree | Task ordering by virtual runtime |
| Memory Allocator (buddy) | Binary Tree | Block splitting/merging |
| Embedded RTOS Ready List | Sorted Linked List | Task by priority |
| Browser (DOM) | Tree | HTML element hierarchy |
| Database (MySQL InnoDB) | B+ Tree | Primary key index |
| AI Search (BFS/DFS) | Queue/Stack | Pathfinding |
| Undo/Redo | Two Stacks | Text editors |

---

## 19. 50 Practical C Programs

---

### Beginner Programs (1–15)

---

#### Program 1: Array — Basic Operations

**Problem:** Insert, delete, search, and display elements in an array.

```c
#include <stdio.h>
#define MAX 100

int arr[MAX], n = 0;

void insert(int val, int pos) {
    for (int i = n; i > pos; i--) arr[i] = arr[i-1];
    arr[pos] = val; n++;
}

void delete_pos(int pos) {
    for (int i = pos; i < n-1; i++) arr[i] = arr[i+1];
    n--;
}

int search(int val) {
    for (int i = 0; i < n; i++) if (arr[i] == val) return i;
    return -1;
}

void display(void) {
    printf("Array: "); for (int i=0;i<n;i++) printf("%d ",arr[i]); printf("\n");
}

int main(void) {
    insert(10,0); insert(20,1); insert(30,2); insert(15,1); // insert 15 at pos 1
    display();           // 10 15 20 30
    printf("Search 20: pos=%d\n", search(20));
    delete_pos(2);       // delete position 2 (20)
    display();           // 10 15 30
    return 0;
}
```
**Output:**
```
Array: 10 15 20 30
Search 20: pos=2
Array: 10 15 30
```
**Time:** Insert O(n), Delete O(n), Search O(n), Display O(n)

---

#### Program 2: Linear Search

```c
#include <stdio.h>

int linear_search(int *arr, int n, int target) {
    for (int i = 0; i < n; i++) {
        printf("Checking arr[%d]=%d\n", i, arr[i]);
        if (arr[i] == target) return i;
    }
    return -1;
}

int main(void) {
    int arr[] = {64, 25, 12, 22, 11};
    int n = 5, target = 22;
    int idx = linear_search(arr, n, target);
    if (idx != -1) printf("Found %d at index %d\n", target, idx);
    else           printf("%d not found\n", target);
    return 0;
}
```
**Output:** `Found 22 at index 3`  
**Time:** O(n)  Best: O(1)  Space: O(1)

---

#### Program 3: Binary Search

```c
#include <stdio.h>

int binary_search(int *arr, int n, int target) {
    int lo = 0, hi = n-1, steps = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        steps++;
        printf("Step %d: lo=%d hi=%d mid=%d arr[mid]=%d\n",
               steps, lo, hi, mid, arr[mid]);
        if (arr[mid] == target) { printf("Found in %d steps\n", steps); return mid; }
        if (arr[mid] < target)  lo = mid + 1;
        else                    hi = mid - 1;
    }
    return -1;
}

int main(void) {
    int arr[] = {5, 15, 25, 35, 45, 55, 65, 75};
    int n = 8, target = 45;
    int idx = binary_search(arr, n, target);
    if (idx != -1) printf("Found %d at index %d\n", target, idx);
    return 0;
}
```
**Time:** O(log n)  Space: O(1)

---

#### Program 4: Bubble Sort

```c
#include <stdio.h>

void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int swapped = 0;
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t; swapped = 1;
            }
        printf("Pass %d: ", i+1);
        for (int k=0;k<n;k++) printf("%d ",arr[k]); printf("\n");
        if (!swapped) { printf("Already sorted at pass %d\n", i+1); break; }
    }
}

int main(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = 7;
    printf("Before: "); for(int i=0;i<n;i++) printf("%d ",arr[i]); printf("\n");
    bubble_sort(arr, n);
    printf("After : "); for(int i=0;i<n;i++) printf("%d ",arr[i]); printf("\n");
    return 0;
}
```
**Time:** O(n²) worst, O(n) best  
**Interview Point:** Bubble sort is stable. Best case O(n) with the `swapped` optimization.

---

#### Program 5: Selection Sort

```c
#include <stdio.h>

void selection_sort(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) if (arr[j] < arr[min_idx]) min_idx = j;
        if (min_idx != i) { int t = arr[i]; arr[i] = arr[min_idx]; arr[min_idx] = t; }
    }
}

int main(void) {
    int arr[] = {29, 10, 14, 37, 13};
    int n = 5;
    selection_sort(arr, n);
    for (int i=0;i<n;i++) printf("%d ",arr[i]); printf("\n");
    return 0;
}
```
**Output:** `10 13 14 29 37`  
**Time:** O(n²) always  Not stable.

---

#### Program 6: Insertion Sort

```c
#include <stdio.h>

void insertion_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        printf("Inserting %d: ", key);
        while (j >= 0 && arr[j] > key) { arr[j+1] = arr[j]; j--; }
        arr[j+1] = key;
        for (int k=0;k<n;k++) printf("%d ",arr[k]); printf("\n");
    }
}

int main(void) {
    int arr[] = {12, 11, 13, 5, 6};
    int n = 5;
    insertion_sort(arr, n);
    return 0;
}
```
**Time:** O(n²) worst, O(n) best (nearly sorted)  
**Interview Point:** Insertion sort is best for small or nearly-sorted arrays.

---

#### Program 7: Singly Linked List — Full Operations

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int data; struct Node *next; } Node;

Node *new_node(int d) {
    Node *n = malloc(sizeof(Node)); n->data=d; n->next=NULL; return n;
}

void push_front(Node **h, int d) { Node *n=new_node(d); n->next=*h; *h=n; }
void push_back(Node **h, int d) {
    Node *n=new_node(d); if(!*h){*h=n;return;}
    Node *c=*h; while(c->next) c=c->next; c->next=n;
}
void delete_val(Node **h, int d) {
    if(!*h) return;
    if((*h)->data==d){Node *t=*h;*h=(*h)->next;free(t);return;}
    Node *c=*h; while(c->next&&c->next->data!=d) c=c->next;
    if(c->next){Node *t=c->next;c->next=t->next;free(t);}
}
void print_list(Node *h) { while(h){printf("%d→",h->data);h=h->next;} printf("NULL\n"); }
void reverse(Node **h) {
    Node *p=NULL,*c=*h,*n; while(c){n=c->next;c->next=p;p=c;c=n;} *h=p;
}

int main(void) {
    Node *head = NULL;
    push_back(&head, 10); push_back(&head, 20); push_back(&head, 30);
    push_front(&head, 5);
    print_list(head);        // 5→10→20→30→NULL
    delete_val(&head, 20);
    print_list(head);        // 5→10→30→NULL
    reverse(&head);
    print_list(head);        // 30→10→5→NULL
    return 0;
}
```

---

#### Program 8: Doubly Linked List

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct DNode { int data; struct DNode *prev, *next; } DNode;

DNode *new_node(int d) {
    DNode *n=calloc(1,sizeof(DNode)); n->data=d; return n;
}

void insert_end(DNode **head, int d) {
    DNode *n=new_node(d);
    if(!*head){*head=n;return;}
    DNode *c=*head; while(c->next) c=c->next;
    c->next=n; n->prev=c;
}

void delete_node(DNode **head, int d) {
    DNode *c=*head;
    while(c && c->data!=d) c=c->next;
    if(!c) return;
    if(c->prev) c->prev->next=c->next;
    else *head=c->next;
    if(c->next) c->next->prev=c->prev;
    free(c);
}

void print_forward(DNode *h) { while(h){printf("%d↔",h->data);h=h->next;} printf("NULL\n"); }
void print_backward(DNode *h) {
    if(!h) return;
    while(h->next) h=h->next;
    while(h){printf("%d↔",h->data);h=h->prev;} printf("NULL\n");
}

int main(void) {
    DNode *head=NULL;
    insert_end(&head,10); insert_end(&head,20); insert_end(&head,30);
    print_forward(head);   // 10↔20↔30↔NULL
    print_backward(head);  // 30↔20↔10↔NULL
    delete_node(&head,20);
    print_forward(head);   // 10↔30↔NULL
    return 0;
}
```

---

#### Program 9: Stack Using Array

```c
#include <stdio.h>
#define MAX 10

int stack[MAX], top = -1;

void push(int v) {
    if (top == MAX-1) { printf("Overflow!\n"); return; }
    stack[++top] = v;
    printf("Pushed %d | Top=%d\n", v, stack[top]);
}

int pop(void) {
    if (top == -1) { printf("Underflow!\n"); return -1; }
    int v = stack[top--];
    printf("Popped %d\n", v);
    return v;
}

void display(void) {
    printf("Stack (top→bottom): ");
    for (int i=top;i>=0;i--) printf("%d ",stack[i]);
    printf("\n");
}

int main(void) {
    push(10); push(20); push(30);
    display();
    pop(); pop();
    display();
    return 0;
}
```

---

#### Program 10: Parenthesis Matching Using Stack

```c
#include <stdio.h>
#include <string.h>
#define MAX 100

char stk[MAX]; int top = -1;
void push_c(char c)   { stk[++top]=c; }
char pop_c(void)      { return top==-1 ? '\0' : stk[top--]; }
int  is_open(char c)  { return c=='(' || c=='[' || c=='{'; }
int  matches(char o, char c) {
    return (o=='('&&c==')')||(o=='['&&c==']')||(o=='{'&&c=='}');
}

int is_balanced(const char *expr) {
    top = -1;
    for (int i=0; expr[i]; i++) {
        if (is_open(expr[i]))   push_c(expr[i]);
        else if (expr[i]==')'||expr[i]==']'||expr[i]=='}') {
            char t = pop_c();
            if (!matches(t, expr[i])) return 0;
        }
    }
    return top == -1;
}

int main(void) {
    const char *tests[] = { "{[()]}", "{[(])}", "((()))", "{[}", "[]{}()" };
    for (int i=0; i<5; i++)
        printf("'%s' → %s\n", tests[i], is_balanced(tests[i]) ? "BALANCED" : "NOT BALANCED");
    return 0;
}
```
**Output:**
```
'{[()]}' → BALANCED
'{[(])}' → NOT BALANCED
'((()))' → BALANCED
'{[}' → NOT BALANCED
'[]{}()' → BALANCED
```

---

#### Program 11: Queue Using Array (Circular)

```c
#include <stdio.h>
#define QMAX 6

int queue[QMAX]; int front=0, rear=-1, size=0;

void enqueue(int v) {
    if (size==QMAX) { printf("Queue Full!\n"); return; }
    rear = (rear+1) % QMAX;
    queue[rear] = v; size++;
    printf("Enqueued %d | Front=%d Rear=%d\n", v, front, rear);
}

int dequeue(void) {
    if (size==0) { printf("Queue Empty!\n"); return -1; }
    int v = queue[front];
    front = (front+1) % QMAX; size--;
    printf("Dequeued %d\n", v);
    return v;
}

void display_queue(void) {
    printf("Queue: ");
    for (int i=0,idx=front; i<size; i++,idx=(idx+1)%QMAX)
        printf("%d ", queue[idx]);
    printf("\n");
}

int main(void) {
    enqueue(10); enqueue(20); enqueue(30); enqueue(40);
    display_queue();
    dequeue(); dequeue();
    display_queue();
    enqueue(50); enqueue(60); enqueue(70);
    display_queue();
    return 0;
}
```

---

#### Program 12: Merge Sort

```c
#include <stdio.h>

void merge(int *a, int l, int m, int r) {
    int n1=m-l+1, n2=r-m, L[n1], R[n2];
    for(int i=0;i<n1;i++) L[i]=a[l+i];
    for(int i=0;i<n2;i++) R[i]=a[m+1+i];
    int i=0,j=0,k=l;
    while(i<n1&&j<n2) a[k++]=(L[i]<=R[j])?L[i++]:R[j++];
    while(i<n1) a[k++]=L[i++];
    while(j<n2) a[k++]=R[j++];
}

void merge_sort(int *a, int l, int r) {
    if(l<r){ int m=l+(r-l)/2; merge_sort(a,l,m); merge_sort(a,m+1,r); merge(a,l,m,r); }
}

int main(void) {
    int arr[]={38,27,43,3,9,82,10}; int n=7;
    printf("Before: "); for(int i=0;i<n;i++) printf("%d ",arr[i]); printf("\n");
    merge_sort(arr,0,n-1);
    printf("After : "); for(int i=0;i<n;i++) printf("%d ",arr[i]); printf("\n");
    return 0;
}
```
**Output:** `After : 3 9 10 27 38 43 82`  
**Time:** O(n log n)  Space: O(n)

---

#### Program 13: Quick Sort

```c
#include <stdio.h>

void swap(int *a, int *b) { int t=*a; *a=*b; *b=t; }

int partition(int *arr, int lo, int hi) {
    int pivot=arr[hi], i=lo-1;
    for(int j=lo;j<hi;j++) if(arr[j]<=pivot) swap(&arr[++i],&arr[j]);
    swap(&arr[i+1],&arr[hi]);
    return i+1;
}

void quick_sort(int *arr, int lo, int hi) {
    if(lo<hi){ int pi=partition(arr,lo,hi); quick_sort(arr,lo,pi-1); quick_sort(arr,pi+1,hi); }
}

int main(void) {
    int arr[]={10,80,30,90,40,50,70}; int n=7;
    quick_sort(arr,0,n-1);
    for(int i=0;i<n;i++) printf("%d ",arr[i]); printf("\n");
    return 0;
}
```
**Output:** `10 30 40 50 70 80 90`  
**Time:** O(n log n) avg, O(n²) worst  Space: O(log n)

---

#### Program 14: BST — Insert, Search, Display

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct BST { int d; struct BST *l, *r; } BST;

BST *insert(BST *root, int d) {
    if(!root){BST*n=malloc(sizeof(BST));n->d=d;n->l=n->r=NULL;return n;}
    if(d<root->d) root->l=insert(root->l,d);
    else if(d>root->d) root->r=insert(root->r,d);
    return root;
}

int search(BST *root, int d) {
    if(!root) return 0;
    if(d==root->d) return 1;
    return d<root->d ? search(root->l,d) : search(root->r,d);
}

void inorder(BST *root) {
    if(!root) return;
    inorder(root->l); printf("%d ",root->d); inorder(root->r);
}

int main(void) {
    BST *root=NULL;
    int vals[]={50,30,70,20,40,60,80};
    for(int i=0;i<7;i++) root=insert(root,vals[i]);
    printf("Inorder (sorted): "); inorder(root); printf("\n");
    printf("Search 40: %s\n", search(root,40)?"Found":"Not Found");
    printf("Search 99: %s\n", search(root,99)?"Found":"Not Found");
    return 0;
}
```
**Output:**
```
Inorder (sorted): 20 30 40 50 60 70 80
Search 40: Found
Search 99: Not Found
```

---

#### Program 15: Stack — Function Call Simulation

```c
#include <stdio.h>
#define MAX 20

typedef struct { char name[32]; int line; } Frame;
Frame call_stack[MAX]; int sp = 0;

void call(const char *fn, int line) {
    if(sp==MAX){printf("Stack Overflow!\n");return;}
    snprintf(call_stack[sp].name, 32, "%s", fn);
    call_stack[sp].line = line;
    sp++;
    printf("CALL  → %s (line %d) | Depth=%d\n", fn, line, sp);
}

void ret(void) {
    if(sp==0){printf("Cannot return from empty stack\n");return;}
    sp--;
    printf("RETURN← %s (line %d) | Depth=%d\n",
           call_stack[sp].name, call_stack[sp].line, sp);
}

int main(void) {
    call("main",    10);
    call("compute", 20);
    call("helper",  35);
    ret(); ret(); ret();
    return 0;
}
```

---

### Intermediate Programs (16–35)

---

#### Program 16: Circular Queue

*(Full implementation — see Program 11 which uses circular queue. This extends it with linked list backing.)*

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct CQNode { int data; struct CQNode *next; } CQNode;
typedef struct { CQNode *front, *rear; int size; } CircularQueue;

void cq_enqueue(CircularQueue *q, int v) {
    CQNode *n = malloc(sizeof(CQNode)); n->data = v;
    if (!q->rear) { n->next = n; q->front = q->rear = n; }
    else { n->next = q->front; q->rear->next = n; q->rear = n; }
    q->size++;
}

int cq_dequeue(CircularQueue *q) {
    if (!q->front) { printf("Empty!\n"); return -1; }
    int v = q->front->data;
    if (q->front == q->rear) { free(q->front); q->front = q->rear = NULL; }
    else { CQNode *t=q->front; q->rear->next=q->front->next; q->front=q->front->next; free(t); }
    q->size--;
    return v;
}

int main(void) {
    CircularQueue q = {NULL, NULL, 0};
    cq_enqueue(&q,10); cq_enqueue(&q,20); cq_enqueue(&q,30);
    printf("Dequeued: %d\n", cq_dequeue(&q));
    cq_enqueue(&q,40);
    printf("Dequeued: %d\n", cq_dequeue(&q));
    return 0;
}
```

---

#### Program 17: Detect Loop in Linked List (Floyd's)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int data; struct Node *next; } Node;

int has_loop(Node *head) {
    Node *slow=head, *fast=head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;
    }
    return 0;
}

int main(void) {
    Node *head=malloc(sizeof(Node)); head->data=1;
    Node *n2=malloc(sizeof(Node)); n2->data=2;
    Node *n3=malloc(sizeof(Node)); n3->data=3;
    Node *n4=malloc(sizeof(Node)); n4->data=4;
    head->next=n2; n2->next=n3; n3->next=n4; n4->next=NULL;
    printf("Loop: %s\n", has_loop(head) ? "YES" : "NO");
    n4->next = n2;   // Create loop: 4 → 2
    printf("Loop: %s\n", has_loop(head) ? "YES" : "NO");
    return 0;
}
```
**Output:**
```
Loop: NO
Loop: YES
```

---

#### Program 18: Reverse Linked List (Iterative & Recursive)

```c
#include <stdio.h>
#include <stdlib.h>
typedef struct Node { int d; struct Node *n; } Node;

Node *new_node(int d) { Node *n=malloc(sizeof(Node)); n->d=d; n->n=NULL; return n; }
void print(Node *h) { while(h){printf("%d→",h->d);h=h->n;} printf("NULL\n"); }

Node *reverse_iter(Node *h) {
    Node *p=NULL,*c=h,*nx;
    while(c){nx=c->n;c->n=p;p=c;c=nx;} return p;
}

Node *reverse_rec(Node *h) {
    if(!h||!h->n) return h;
    Node *rest=reverse_rec(h->n);
    h->n->n=h; h->n=NULL;
    return rest;
}

int main(void) {
    Node *h=NULL; for(int i=1;i<=5;i++){Node*n=new_node(i*10);n->n=h;h=n;}
    print(h);
    h=reverse_iter(h); print(h);
    h=reverse_rec(h); print(h);
    return 0;
}
```

---

#### Program 19: BST Deletion (All 3 Cases)

*(See Section 9 for full `bst_delete()` implementation. Demonstrated here with output)*

```c
int main(void) {
    BST *root=NULL;
    int v[]={50,30,70,20,40,60,80};
    for(int i=0;i<7;i++) root=bst_insert(root,v[i]);

    printf("Before: "); inorder(root); printf("\n");
    root = bst_delete(root, 20);  // Case 1: leaf
    printf("Del 20: "); inorder(root); printf("\n");
    root = bst_delete(root, 30);  // Case 2: one child (40)
    printf("Del 30: "); inorder(root); printf("\n");
    root = bst_delete(root, 50);  // Case 3: two children
    printf("Del 50: "); inorder(root); printf("\n");
    return 0;
}
```
**Output:**
```
Before: 20 30 40 50 60 70 80
Del 20: 30 40 50 60 70 80
Del 30: 40 50 60 70 80
Del 50: 60 70 80 40   ← inorder successor (60) replaces 50
```

---

#### Program 20: Hash Table with Chaining

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SZ 7

typedef struct E { char key[32]; int val; struct E *next; } Entry;
Entry *table[SZ];

int hash(const char *k) {
    unsigned h=0; while(*k) h=h*31+*k++; return h%SZ;
}

void put(const char *k, int v) {
    int idx=hash(k);
    Entry *e=table[idx];
    while(e){if(!strcmp(e->key,k)){e->val=v;return;}e=e->next;}
    e=malloc(sizeof(Entry)); strncpy(e->key,k,31); e->val=v; e->next=table[idx]; table[idx]=e;
}

int get(const char *k, int *v) {
    Entry *e=table[hash(k)];
    while(e){if(!strcmp(e->key,k)){*v=e->val;return 1;}e=e->next;}
    return 0;
}

void print_table(void) {
    for(int i=0;i<SZ;i++){
        printf("[%d]: ",i);
        Entry *e=table[i]; while(e){printf("(%s:%d)→",e->key,e->val);e=e->next;}
        printf("NULL\n");
    }
}

int main(void) {
    memset(table,0,sizeof(table));
    put("name",1); put("age",25); put("score",95); put("rank",3);
    int v;
    if(get("age",&v)) printf("age = %d\n",v);
    print_table();
    return 0;
}
```

---

#### Program 21: Graph — BFS and DFS

```c
#include <stdio.h>
#include <string.h>
#define V 6

int adj[V][V];

void add_edge(int u, int v) { adj[u][v]=adj[v][u]=1; }

void bfs(int start) {
    int vis[V]={0}, q[V], f=0, r=0;
    vis[start]=1; q[r++]=start;
    printf("BFS: ");
    while(f<r) {
        int u=q[f++]; printf("%d ",u);
        for(int i=0;i<V;i++) if(adj[u][i]&&!vis[i]){vis[i]=1;q[r++]=i;}
    }
    printf("\n");
}

void dfs_r(int u, int *vis) {
    vis[u]=1; printf("%d ",u);
    for(int i=0;i<V;i++) if(adj[u][i]&&!vis[i]) dfs_r(i,vis);
}

void dfs(int start) {
    int vis[V]={0}; printf("DFS: "); dfs_r(start,vis); printf("\n");
}

int main(void) {
    memset(adj,0,sizeof(adj));
    add_edge(0,1); add_edge(0,2); add_edge(1,3);
    add_edge(1,4); add_edge(2,5);
    bfs(0);    // BFS: 0 1 2 3 4 5
    dfs(0);    // DFS: 0 1 3 4 2 5
    return 0;
}
```

---

#### Program 22: AVL Tree — Insert and Display

```c
// Uses avl_insert() from Section 10
#include <stdio.h>
#include <stdlib.h>

// (AVL functions from Section 10 included here)

void avl_inorder(AVL *root) {
    if(!root) return;
    avl_inorder(root->left);
    printf("%d(h=%d) ", root->data, root->height);
    avl_inorder(root->right);
}

int main(void) {
    AVL *root=NULL;
    int vals[]={10,20,30,40,50,25};
    for(int i=0;i<6;i++) {
        root=avl_insert(root,vals[i]);
        printf("After insert %d: ", vals[i]);
        avl_inorder(root); printf("\n");
    }
    printf("Root=%d Height=%d\n", root->data, root->height);
    return 0;
}
```

---

#### Program 23: Max Heap — Insert and Extract

```c
#include <stdio.h>
// Uses MaxHeap from Section 11

int main(void) {
    MaxHeap h; h.size=0;
    int vals[]={3,1,4,1,5,9,2,6};
    int n=8;
    for(int i=0;i<n;i++) heap_insert(&h, vals[i]);

    printf("Heap (sorted desc): ");
    while(h.size>0) printf("%d ", heap_extract_max(&h));
    printf("\n");
    return 0;
}
```
**Output:** `Heap (sorted desc): 9 6 5 4 3 2 1 1`

---

#### Program 24: Expression Evaluation (Postfix)

```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int stk[100]; int top=-1;
void push(int v){stk[++top]=v;}
int  pop(void){return stk[top--];}

int eval_postfix(const char *expr) {
    for(int i=0; expr[i]; i++) {
        if(isdigit(expr[i])) push(expr[i]-'0');
        else if(expr[i]!=' ') {
            int b=pop(), a=pop();
            if(expr[i]=='+') push(a+b);
            else if(expr[i]=='-') push(a-b);
            else if(expr[i]=='*') push(a*b);
            else if(expr[i]=='/') push(a/b);
        }
    }
    return pop();
}

int main(void) {
    // Postfix for: (3+4)*2  →  "3 4 + 2 *"
    printf("3 4 + 2 * = %d\n", eval_postfix("3 4 + 2 *"));
    // Postfix for: 5+1*2-3  →  "5 1 2 * + 3 -"
    printf("5 1 2 * + 3 - = %d\n", eval_postfix("5 1 2 * + 3 -"));
    return 0;
}
```
**Output:**
```
3 4 + 2 * = 14
5 1 2 * + 3 - = 4
```

---

#### Program 25: Priority Queue (Min-Heap)

```c
#include <stdio.h>
#define PQ_MAX 100

typedef struct { int val, priority; } PQItem;
typedef struct { PQItem data[PQ_MAX]; int size; } MinPQ;

void pq_swap(MinPQ *pq, int i, int j) {
    PQItem t=pq->data[i]; pq->data[i]=pq->data[j]; pq->data[j]=t;
}

void pq_push(MinPQ *pq, int val, int prio) {
    int i = pq->size++;
    pq->data[i].val=val; pq->data[i].priority=prio;
    while(i>0) {
        int p=(i-1)/2;
        if(pq->data[p].priority > pq->data[i].priority){pq_swap(pq,p,i);i=p;}
        else break;
    }
}

PQItem pq_pop(MinPQ *pq) {
    PQItem top=pq->data[0];
    pq->data[0]=pq->data[--pq->size];
    int i=0;
    while(1){
        int l=2*i+1,r=2*i+2,s=i;
        if(l<pq->size&&pq->data[l].priority<pq->data[s].priority) s=l;
        if(r<pq->size&&pq->data[r].priority<pq->data[s].priority) s=r;
        if(s==i) break; pq_swap(pq,i,s); i=s;
    }
    return top;
}

int main(void) {
    MinPQ pq; pq.size=0;
    pq_push(&pq, 100, 3);
    pq_push(&pq, 200, 1);  // Highest priority
    pq_push(&pq, 300, 4);
    pq_push(&pq, 400, 2);
    printf("Processing by priority:\n");
    while(pq.size>0) {
        PQItem it=pq_pop(&pq);
        printf("  Task val=%d priority=%d\n",it.val,it.priority);
    }
    return 0;
}
```
**Output:**
```
Processing by priority:
  Task val=200 priority=1
  Task val=400 priority=2
  Task val=100 priority=3
  Task val=300 priority=4
```

---

#### Programs 26–35 (Summaries with Key Code)

---

#### Program 26: Merge Two Sorted Linked Lists

```c
Node *merge_sorted(Node *a, Node *b) {
    if(!a) return b; if(!b) return a;
    if(a->data <= b->data) { a->next=merge_sorted(a->next,b); return a; }
    else { b->next=merge_sorted(a,b->next); return b; }
}
// Time: O(m+n)
```

---

#### Program 27: Find Middle of Linked List (Slow-Fast Pointer)

```c
Node *find_middle(Node *head) {
    Node *slow=head, *fast=head;
    while(fast && fast->next) { slow=slow->next; fast=fast->next->next; }
    return slow;   // slow points to middle
}
// Time: O(n)  — single pass
```

---

#### Program 28: Inorder Iterative (Without Recursion)

```c
void inorder_iter(TNode *root) {
    TNode *stk[100], *cur=root; int top=-1;
    while(cur || top!=-1) {
        while(cur){stk[++top]=cur;cur=cur->left;}
        cur=stk[top--]; printf("%d ",cur->data);
        cur=cur->right;
    }
}
```

---

#### Program 29: Level Order — Print Level by Level

```c
void level_by_level(TNode *root) {
    if(!root) return;
    TNode *q[1000]; int f=0,r=0;
    q[r++]=root; q[r++]=NULL;   // NULL = level separator
    while(f<r) {
        TNode *cur=q[f++];
        if(!cur){printf("\n");if(f<r)q[r++]=NULL;}
        else{printf("%d ",cur->data);if(cur->left)q[r++]=cur->left;if(cur->right)q[r++]=cur->right;}
    }
}
```

---

#### Program 30: Trie — Insert and Search Words

```c
// Uses Trie from Section 14
int main(void) {
    Trie *root=trie_new_node();
    trie_insert(root,"apple");
    trie_insert(root,"app");
    trie_insert(root,"banana");

    printf("apple:  %s\n", trie_search(root,"apple")  ?"found":"not found");
    printf("app:    %s\n", trie_search(root,"app")    ?"found":"not found");
    printf("apricot:%s\n", trie_search(root,"apricot")?"found":"not found");
    return 0;
}
```

---

### Advanced Programs (36–50)

---

#### Program 36: LRU Cache (Hash Map + Doubly Linked List)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LRU_CAP 3
#define HT_SZ   10

typedef struct LRU_Node { int key, val; struct LRU_Node *prev, *next; } LRU_Node;
typedef struct { LRU_Node *map[HT_SZ]; LRU_Node *head, *tail; int size; } LRU;

LRU_Node *lru_new(int k, int v) {
    LRU_Node *n=calloc(1,sizeof(LRU_Node)); n->key=k; n->val=v; return n;
}

void lru_move_to_front(LRU *c, LRU_Node *n) {
    if(n==c->head) return;
    if(n->prev) n->prev->next=n->next;
    if(n->next) n->next->prev=n->prev;
    if(n==c->tail) c->tail=n->prev;
    n->prev=NULL; n->next=c->head;
    if(c->head) c->head->prev=n;
    c->head=n;
    if(!c->tail) c->tail=n;
}

int lru_get(LRU *c, int key) {
    LRU_Node *n=c->map[key%HT_SZ];
    while(n&&n->key!=key) n=n->next;
    if(!n) return -1;
    lru_move_to_front(c,n);
    return n->val;
}

void lru_put(LRU *c, int key, int val) {
    // Check if exists:
    LRU_Node *n=c->map[key%HT_SZ];
    while(n&&n->key!=key) n=n->next;
    if(n){n->val=val;lru_move_to_front(c,n);return;}

    // Evict if full:
    if(c->size==LRU_CAP && c->tail) {
        int ek=c->tail->key;
        LRU_Node *ev=c->tail;
        c->tail=c->tail->prev;
        if(c->tail) c->tail->next=NULL;
        else c->head=NULL;
        c->map[ek%HT_SZ]=NULL;
        free(ev); c->size--;
        printf("  [EVICT key=%d]\n", ek);
    }
    // Insert:
    n=lru_new(key,val);
    n->next=c->head; if(c->head) c->head->prev=n;
    c->head=n; if(!c->tail) c->tail=n;
    c->map[key%HT_SZ]=n; c->size++;
}

int main(void) {
    LRU cache; memset(&cache,0,sizeof(cache));
    lru_put(&cache,1,100); printf("Put(1,100)\n");
    lru_put(&cache,2,200); printf("Put(2,200)\n");
    lru_put(&cache,3,300); printf("Put(3,300)\n");
    printf("Get(1) = %d\n", lru_get(&cache,1));   // Moves 1 to front
    lru_put(&cache,4,400); printf("Put(4,400) — should evict 2\n");
    printf("Get(2) = %d\n", lru_get(&cache,2));   // -1, evicted
    printf("Get(3) = %d\n", lru_get(&cache,3));
    return 0;
}
```

---

#### Program 37: Dijkstra's Shortest Path

```c
#include <stdio.h>
#include <limits.h>
#define INF INT_MAX
#define DV  5

int wt[DV][DV], dist[DV]; int visited[DV];

int min_dist(void) {
    int min=INF, idx=-1;
    for(int i=0;i<DV;i++) if(!visited[i]&&dist[i]<min){min=dist[i];idx=i;}
    return idx;
}

void dijkstra(int src) {
    for(int i=0;i<DV;i++){dist[i]=INF;visited[i]=0;}
    dist[src]=0;
    for(int i=0;i<DV-1;i++){
        int u=min_dist(); if(u==-1) break; visited[u]=1;
        for(int v=0;v<DV;v++)
            if(!visited[v]&&wt[u][v]&&dist[u]!=INF&&dist[u]+wt[u][v]<dist[v])
                dist[v]=dist[u]+wt[u][v];
    }
    printf("Dijkstra from vertex %d:\n",src);
    for(int i=0;i<DV;i++) printf("  0→%d = %d\n",i,dist[i]==INF?-1:dist[i]);
}

int main(void) {
    int g[DV][DV]={
        {0,10,0,0,5},{10,0,1,0,2},{0,1,0,4,0},{0,0,4,0,0},{5,2,0,0,0}
    };
    for(int i=0;i<DV;i++) for(int j=0;j<DV;j++) wt[i][j]=g[i][j];
    dijkstra(0);
    return 0;
}
```

---

#### Program 38: Disjoint Set — Cycle Detection in Graph

```c
// Uses ds_find, ds_union from Section 14

typedef struct { int u, v; } Edge;

int has_cycle(Edge *edges, int E, int V) {
    ds_init(V);
    for(int i=0;i<E;i++){
        int pu=ds_find(edges[i].u), pv=ds_find(edges[i].v);
        if(pu==pv) return 1;
        ds_union(edges[i].u, edges[i].v);
    }
    return 0;
}

int main(void) {
    Edge e1[] = {{0,1},{1,2},{2,3}};
    printf("Cycle: %s\n", has_cycle(e1,3,4) ? "YES" : "NO");  // NO
    Edge e2[] = {{0,1},{1,2},{2,0}};
    printf("Cycle: %s\n", has_cycle(e2,3,3) ? "YES" : "NO");  // YES
    return 0;
}
```

---

#### Program 39: Kruskal's Minimum Spanning Tree

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct { int u,v,w; } KEdge;

int cmp_edge(const void *a, const void *b) {
    return ((KEdge*)a)->w - ((KEdge*)b)->w;
}

void kruskal(KEdge *edges, int E, int V) {
    qsort(edges, E, sizeof(KEdge), cmp_edge);
    ds_init(V);
    int total=0, count=0;
    printf("MST Edges:\n");
    for(int i=0;i<E&&count<V-1;i++){
        int u=edges[i].u, v=edges[i].v;
        if(ds_find(u)!=ds_find(v)){
            printf("  %d — %d  (weight %d)\n",u,v,edges[i].w);
            ds_union(u,v); total+=edges[i].w; count++;
        }
    }
    printf("MST Total Weight: %d\n",total);
}

int main(void) {
    KEdge edges[]={{0,1,10},{0,2,6},{0,3,5},{1,3,15},{2,3,4}};
    kruskal(edges,5,4);
    return 0;
}
```
**Output:**
```
MST Edges:
  2 — 3  (weight 4)
  0 — 3  (weight 5)
  0 — 1  (weight 10)
MST Total Weight: 19
```

---

#### Program 40: Segment Tree — Range Sum Query

```c
#include <stdio.h>
// Uses seg[], seg_build(), seg_query() from Section 14

void seg_update(int node, int start, int end, int idx, int val) {
    if(start==end){seg[node]=val;return;}
    int mid=(start+end)/2;
    if(idx<=mid) seg_update(2*node,start,mid,idx,val);
    else         seg_update(2*node+1,mid+1,end,idx,val);
    seg[node]=seg[2*node]+seg[2*node+1];
}

int main(void) {
    int arr[]={1,3,5,7,9,11}; int n=6;
    seg_build(arr,1,0,n-1);

    printf("Sum [1,4] = %d\n", seg_query(1,0,n-1,1,4));  // 3+5+7+9=24
    printf("Sum [0,5] = %d\n", seg_query(1,0,n-1,0,5));  // 36

    seg_update(1,0,n-1,3,10);  // Update arr[3] = 10
    printf("After update arr[3]=10:\n");
    printf("Sum [1,4] = %d\n", seg_query(1,0,n-1,1,4));  // 3+5+10+9=27
    return 0;
}
```

---

#### Programs 41–50 Summaries

| # | Program | Key Technique | Time |
|---|---------|--------------|------|
| 41 | Topological Sort (DFS) | DFS + stack | O(V+E) |
| 42 | Floyd-Warshall All-Pairs Shortest Path | DP, 3-loop | O(V³) |
| 43 | Heap Sort | Build heap + extract | O(n log n) |
| 44 | AVL Tree Full (Insert+Delete) | Rotations after delete | O(log n) |
| 45 | Trie Autocomplete | DFS on trie | O(L·26) |
| 46 | Fenwick Tree (BIT) Range Sum | BIT update/query | O(log n) |
| 47 | Generic Stack (void pointer) | `void*`, size param | O(1) push/pop |
| 48 | Skip List | Probabilistic levels | O(log n) avg |
| 49 | Circular Doubly Linked List | prev/next + circular | O(1) insert |
| 50 | Phone Book (Hash + Trie) | Combined DS | O(L) search |

---

## 20. 100+ Interview Questions & Answers

### Basic Level (Freshers)

**Q1: What is a Data Structure?**  
A: A way to organize, store, and manage data in memory for efficient access and modification.

**Q2: What is the difference between an Array and a Linked List?**

| Array | Linked List |
|-------|-------------|
| Contiguous memory | Non-contiguous |
| O(1) access by index | O(n) access |
| O(n) insert/delete | O(1) insert/delete |
| Fixed size (static) | Dynamic size |
| Cache-friendly | Cache-unfriendly |

**Q3: What is LIFO? Give an example.**  
A: Last In, First Out. Stack: last pushed element is first to be popped. Example: browser back button, function call stack.

**Q4: What is FIFO? Give an example.**  
A: First In, First Out. Queue: first element enqueued is first to be dequeued. Example: print spooler, OS process scheduling.

**Q5: What is Dynamic Memory Allocation?**  
A: Allocating memory at runtime using `malloc()`, `calloc()`, `realloc()`, `free()` from the heap. Size determined at run time, not compile time.

**Q6: What is the time complexity of binary search?**  
A: O(log n). Requires sorted array. Each step halves the search space.

**Q7: What is a tree?**  
A: A non-linear hierarchical data structure with a root node and subtrees of children, with no cycles.

**Q8: What is a leaf node?**  
A: A node with no children.

**Q9: What is the difference between BFS and DFS?**  
A: BFS uses a queue, explores level by level, finds shortest path. DFS uses a stack (recursion), explores depth first, used for topological sort.

**Q10: What is hashing?**  
A: Mapping keys to array indices via a hash function, enabling near O(1) lookup.

---

### Intermediate Level (1–3 Years)

**Q11: What is a circular queue? Why is it used?**  
A: A queue where rear wraps around to the front using modulo arithmetic. Solves the "false full" problem of linear queues where front has advanced but space is wasted.

**Q12: Explain BST deletion — all three cases.**  
A:
1. **Leaf node:** Just delete it.
2. **One child:** Replace node with its child.
3. **Two children:** Replace with inorder successor (smallest in right subtree), then delete the successor.

**Q13: What is a collision in hashing? How is it resolved?**  
A: Two different keys map to the same index. Resolved by: Chaining (linked list at each bucket), Linear Probing (next empty slot), Quadratic Probing, Double Hashing.

**Q14: What is the balance factor in an AVL tree?**  
A: `BF = Height(Left) - Height(Right)`. Must be -1, 0, or +1 for every node. If |BF| > 1, rotation is performed.

**Q15: What is the difference between a min-heap and max-heap?**  
A: Min-heap: parent ≤ children (root = minimum). Max-heap: parent ≥ children (root = maximum).

**Q16: What is the inorder traversal of a BST?**  
A: Inorder traversal of a BST produces elements in **sorted (ascending) order**.

**Q17: Explain Floyd's cycle detection algorithm.**  
A: Two pointers: slow moves 1 step, fast moves 2 steps. If they meet, a cycle exists. Meeting point can be used to find cycle start.

**Q18: What is a priority queue?**  
A: An abstract data type where each element has a priority. Higher-priority elements are dequeued before lower-priority ones. Typically implemented using a heap.

**Q19: What is the time complexity of heap insert and extract?**  
A: Both O(log n) — heapify up for insert, heapify down for extract.

**Q20: What is graph adjacency list vs adjacency matrix?**  
A:
- Matrix: O(V²) space, O(1) edge check. Good for dense graphs.
- List: O(V+E) space, O(degree) edge check. Good for sparse graphs.

---

### Advanced Level (3–5 Years)

**Q21: What are AVL rotations? When is each used?**  
A: LL (right rotate), RR (left rotate), LR (left-right double rotate), RL (right-left double rotate). LL/RR for single imbalance; LR/RL for zigzag imbalance.

**Q22: What is a Red-Black Tree? How does it differ from AVL?**  
A: RBT uses color (red/black) properties instead of balance factors. AVL is more strictly balanced (faster lookup), RBT allows slightly more imbalance (faster insert/delete). RBT used in Linux kernel (`rb_root`), C++ STL map.

**Q23: What is a B-Tree? Why is it used in databases?**  
A: A self-balancing search tree where each node can have multiple keys and children (order m). Minimizes disk I/O — each node fills a disk page. Used in MySQL InnoDB, file systems.

**Q24: What is a Trie? What is its time complexity?**  
A: A tree where each path from root to node spells out a string. Insert/Search: O(L) where L = string length. Used in autocomplete, spell check, IP routing (longest prefix match).

**Q25: What is a Segment Tree?**  
A: A complete binary tree where each node stores aggregate (sum/min/max) of a range. Build O(n), query O(log n), update O(log n). Used for range queries.

**Q26: What is Union-Find / Disjoint Set?**  
A: A data structure tracking partitions of a set. `find()` with path compression and `union()` with rank gives nearly O(1) amortized per operation. Used in Kruskal's MST, cycle detection.

**Q27: What is the difference between Dijkstra and Bellman-Ford?**

| | Dijkstra | Bellman-Ford |
|---|---------|--------------|
| Negative weights | No | Yes |
| Time | O((V+E) log V) | O(VE) |
| Negative cycles | Cannot detect | Detects |

**Q28: Explain the merge sort algorithm's time and space complexity.**  
A: Divides array in half recursively (O(log n) levels), each level merges in O(n). Total: O(n log n). Space: O(n) for merge arrays. Stable sort.

**Q29: What is amortized analysis? Give an example.**  
A: Average performance over a sequence of operations. Example: dynamic array doubling — individual insert can be O(n) on resize, but amortized over n inserts it's O(1).

**Q30: What is the LRU Cache and how is it implemented efficiently?**  
A: Least Recently Used. Evicts the element not used for the longest time. O(1) get and put: HashMap maps key → DLL node; DLL maintains order (most recent at head). Python: `OrderedDict`. C: manual hash + DLL.

---

### Expert Level

**Q31: Explain the Linux Kernel linked list (`list_head`).**  
A: Linux uses an intrusive doubly linked list. `struct list_head { prev, next; }` is embedded inside any struct. `container_of()` macro recovers the enclosing struct. All kernel data structures (task_struct, inodes, etc.) use this.

**Q32: How does the Linux CFS scheduler use Red-Black Tree?**  
A: Each runnable task is a node in an RBT ordered by `vruntime`. The leftmost node (minimum vruntime = least-run task) is always O(log n) to pick next. Insert/remove also O(log n).

**Q33: What is B+ Tree and why is it preferred over B-Tree for databases?**  
A: B+ Tree stores all data in leaf nodes (linked list). Internal nodes only store keys for routing. Benefits: better range queries (traverse leaf list), all records equidistant from root, higher branching factor → fewer disk reads.

**Q34: How does a Hash Map handle rehashing?**  
A: When load factor exceeds threshold (typically 0.7), create a new table with ~2x size, and reinsert all entries by running hash function with new table size. Amortized O(1) insert.

**Q35: Explain Fenwick Tree (Binary Indexed Tree).**  
A: Array structure where each index stores partial sums. `update(i, val)` and `prefix_sum(i)` both run in O(log n) using bit manipulation (`i & (-i)`). More space-efficient than segment tree.

---

### Embedded Engineers

**Q36: What data structure is used in embedded RTOS ready queues?**  
A: Priority queue (often a sorted doubly linked list or bitmap-indexed ready arrays like in FreeRTOS) to quickly find the highest-priority ready task.

**Q37: Why are arrays preferred over linked lists in embedded systems?**  
A: Predictable memory layout, cache-friendly, no dynamic allocation (avoids fragmentation), no pointer overhead, deterministic access time — critical for real-time systems.

**Q38: What is a circular buffer? How is it used in embedded systems?**  
A: A fixed-size array used as a FIFO ring buffer with `head` and `tail` pointers. Used for UART receive buffers, ADC sample buffers, log buffers in MCU firmware.

---

### Linux Developers

**Q39: How is a hash table used in the Linux kernel?**  
A: `struct hlist_head` and `struct hlist_node` implement an array of singly-linked lists. Used in `dcache` (dentry cache), process ID lookup tables (`pid_hash`).

**Q40: Explain the page cache and its data structures.**  
A: Linux page cache uses a **radix tree** (now XArray) to map file offsets to physical page frames. O(log n) lookup by page index. Used for caching file blocks in RAM.

---

### Product-Based Company Level (FAANG)

**Q41–Q100 Summary Table:**

| Q# | Topic | Key Answer |
|----|-------|-----------|
| 41 | Find Kth smallest in BST | Inorder + counter |
| 42 | Check if tree is BST | Min/max range validation |
| 43 | LCA of two nodes in BST | Compare with root |
| 44 | Serialize/Deserialize BST | Preorder + use N for NULL |
| 45 | Next greater element | Stack-based O(n) |
| 46 | Trapping rainwater | Two-pointer or stack O(n) |
| 47 | Sliding window maximum | Deque O(n) |
| 48 | Top K frequent elements | Min-heap O(n log k) |
| 49 | Merge K sorted lists | Min-heap O(n log k) |
| 50 | Word search in grid | DFS + backtracking |
| 51 | Clone graph | BFS + hashmap |
| 52 | Number of islands | DFS/BFS O(m·n) |
| 53 | Detect cycle in directed graph | DFS + rec stack |
| 54 | Topological sort | Kahn's BFS or DFS |
| 55 | Minimum spanning tree | Kruskal / Prim |
| 56 | Longest common substring | Trie / DP |
| 57 | Design Twitter feed | Min-heap + lists |
| 58 | Design file system | Trie of paths |
| 59 | Consistent hashing | Sorted circular hash ring |
| 60 | Time complexity of `n * log n` sort | O(n log n) compare-based optimal |
| 61 | Array rotation by k | Reverse algorithm O(n) |
| 62 | Majority element | Boyer-Moore voting O(n) |
| 63 | 2-sum / 3-sum | Hash set O(n) / two-pointer O(n²) |
| 64 | Stock buy-sell | One pass, track min O(n) |
| 65 | Merge intervals | Sort + sweep O(n log n) |
| 66 | BFS shortest path unweighted | BFS O(V+E) |
| 67 | Count connected components | Union-Find / DFS O(V+E) |
| 68 | Validate BST | Range [min,max] check O(n) |
| 69 | Convert sorted array to BST | Mid-element recursion O(n) |
| 70 | Max depth of tree | Recursive height O(n) |
| 71 | Is tree balanced | Bottom-up height check O(n) |
| 72 | Find all paths root to leaf | DFS + backtrack O(n) |
| 73 | Implement queue using 2 stacks | O(1) amortized enqueue |
| 74 | Implement stack using 2 queues | O(n) push or pop |
| 75 | Design hashmap from scratch | Array + chaining |
| 76 | Max subarray (Kadane's) | O(n) DP |
| 77 | Jump game | Greedy O(n) |
| 78 | Coin change | DP O(amount*coins) |
| 79 | Longest increasing subsequence | DP O(n²) or patience sort O(n log n) |
| 80 | Matrix search (sorted rows+cols) | Start at top-right corner O(m+n) |
| 81–100 | System design topics | Covered in Case Studies section |

---

## 21. Tricky Interview Questions

**Q: What is the output of inorder traversal if a BST has only one element?**  
A: Just that one element. `inorder(root)` visits left (NULL, returns), prints root->data, visits right (NULL, returns).

---

**Q: If you insert n sorted elements into a BST, what is the height?**  
A: Height = n-1 (degenerates to a linked list). Time complexity of search becomes O(n). Solution: use AVL or Red-Black Tree.

---

**Q: Can a circular linked list have NULL in it?**  
A: No — the last node points back to the first (or any other node). A NULL pointer in the list indicates a bug.

---

**Q: What happens when you free() a pointer twice?**  
A: Double free is **undefined behavior** — may crash, corrupt heap metadata, or cause security vulnerability (heap exploitation). Always set `ptr = NULL` after `free()`.

---

**Q: What is the time complexity of deleting a node from a doubly linked list given a pointer to that node?**  
A: O(1) — you have prev and next directly. No traversal needed.

---

**Q: Is hash table search always O(1)?**  
A: Average case O(1) with good hash function and low load factor. Worst case O(n) if all keys hash to same bucket (all in one chain).

---

**Q: In Quick Sort, what is the worst case and when does it occur?**  
A: O(n²) when pivot is always the smallest or largest element — happens with sorted or reverse-sorted input. Fix: use median-of-three pivot selection or randomized pivot.

---

**Q: What data structure is used for function call stack in operating systems?**  
A: Stack — each function call pushes a stack frame (return address, parameters, local variables). Stack grows downward in most architectures.

---

**Q: Can a priority queue guarantee FIFO for elements with equal priority?**  
A: Standard binary heap-based priority queues do not guarantee FIFO for equal priorities. Use a secondary sort key (timestamp) if needed.

---

**Q: What is the difference between DFS and backtracking?**  
A: DFS is a graph traversal strategy. Backtracking is a problem-solving technique that uses DFS but also undoes choices ("backtracks") when a path leads to no solution.

---

## 22. Real-World Case Studies

### Case 1: Browser History Using Stack

```c
// Each visited URL pushed onto stack
// Back button = pop
// Forward button = push to forward-stack, pop from back-stack
Stack back_stack, forward_stack;
// navigate("google.com") → push to back_stack
// press Back → pop from back_stack, push to forward_stack
// press Forward → pop from forward_stack, push to back_stack
```

### Case 2: Printer Queue

```c
// All print jobs go into a FIFO Queue
// Printer processes front of queue
// High-priority: use Priority Queue (smaller priority number = process first)
Queue print_queue;
// enqueue(job) when user submits
// dequeue() when printer is ready
```

### Case 3: Process Scheduling (Linux CFS)

Linux Completely Fair Scheduler:
- Each process tracked by `vruntime` (virtual runtime).
- Stored in a **Red-Black Tree** ordered by `vruntime`.
- Scheduler picks leftmost node (minimum vruntime) — O(log n).
- Running a task increases its `vruntime` → it moves right in the tree.

### Case 4: Database Indexing (B+ Tree)

MySQL InnoDB:
- Primary key index: B+ Tree where leaf nodes are sorted data pages.
- Range queries (WHERE age BETWEEN 20 AND 30): traverse leaf linked list.
- Each node fills a disk page (~16KB) minimizing I/O.
- Height ~3 for a billion-row table → 3 disk reads for any lookup.

### Case 5: Routing Algorithms (Graph + Dijkstra)

Internet routing:
- Network = weighted graph (vertices = routers, edges = links, weight = latency/bandwidth).
- OSPF protocol runs Dijkstra on each router to build shortest path tree.
- Result: routing table (next hop for each destination prefix).

### Case 6: File System (Tree Structure)

Linux ext4:
- Directory hierarchy = tree (inodes = nodes, directory entries = edges).
- File lookup: traverse path components in tree.
- Disk block allocation: B-tree of free extents.
- Journal: linked list of transaction blocks.

### Case 7: Linux Kernel Task List

```c
// In linux/sched.h:
struct task_struct {
    // ...
    struct list_head tasks;  // Embedded doubly linked list
    // ...
};
// All processes linked in a circular DLL
// for_each_process(p) macro iterates all processes
// Adding/removing task: O(1) list insertion
```

### Case 8: Memory Allocator (Free List)

```c
// Allocator maintains a free list (linked list of free blocks)
// malloc(size): search free list for suitable block
// free(ptr): insert block back into free list
// Modern allocators: segregated free lists by size class
// (Doug Lea's allocator / jemalloc use trees + lists)
```

---

## 23. Common Mistakes

### 1. Memory Leak in Linked List
```c
// WRONG: not freeing all nodes:
Node *head = ...; head = NULL;   // Memory leaked!

// CORRECT:
Node *cur = head, *nxt;
while(cur){ nxt = cur->next; free(cur); cur = nxt; }
head = NULL;
```

### 2. Null Pointer Dereference
```c
// WRONG:
Node *n = malloc(sizeof(Node));
n->data = 10;   // What if malloc returned NULL?!

// CORRECT:
Node *n = malloc(sizeof(Node));
if (!n) { perror("malloc"); exit(1); }
n->data = 10;
```

### 3. Incorrect Node Deletion (Single Link Lost)
```c
// WRONG — losing the rest of the list:
Node *cur = head;
while(cur->data != target) cur = cur->next;
free(cur);   // cur->next is now lost!

// CORRECT — maintain previous pointer:
Node *prev = NULL, *cur = head;
while(cur && cur->data != target){ prev = cur; cur = cur->next; }
if(cur){ if(prev) prev->next = cur->next; else head = cur->next; free(cur); }
```

### 4. Infinite Loop in Circular Linked List Traversal
```c
// WRONG — never stops:
Node *cur = head;
while(cur != NULL) { printf("%d ", cur->data); cur = cur->next; }
// In circular list, cur never becomes NULL!

// CORRECT:
Node *cur = head;
do { printf("%d ", cur->data); cur = cur->next; } while(cur != head);
```

### 5. Stack/Queue Overflow Without Check
```c
// WRONG:
void push(int v){ stack[++top] = v; }  // No overflow check!

// CORRECT:
void push(int v){
    if(top == MAX-1){ fprintf(stderr,"Stack overflow\n"); return; }
    stack[++top] = v;
}
```

### 6. BST Deletion Memory Leak
```c
// WRONG — root of deleted node not freed:
if(!root->left){ return root->right; }   // root never freed!

// CORRECT:
if(!root->left){ BST *t = root->right; free(root); return t; }
```

---

## 24. Best Practices

### Modular Coding
- Separate each data structure into its own `.h`/`.c` file.
- Expose only the interface (struct typedef + function declarations) in header.
- Hide implementation details in `.c` file.

### Memory Management Rules
```c
// Rule 1: Every malloc has a matching free
// Rule 2: Never access freed memory — set ptr=NULL immediately
// Rule 3: Check malloc return value always
// Rule 4: Use valgrind to detect leaks: valgrind --leak-check=full ./app
// Rule 5: Free in reverse order of allocation for complex structures
```

### Error Handling
```c
// Always handle allocation failure:
Node *n = malloc(sizeof(Node));
if (!n) { fprintf(stderr, "Out of memory\n"); return NULL; }

// Return error codes from DS operations:
typedef enum { DS_OK=0, DS_OVERFLOW, DS_UNDERFLOW, DS_NOT_FOUND } DSStatus;
DSStatus stack_push(Stack *s, int val) { ... }
```

### Algorithm Selection Guide

| Data size | Recommendation |
|-----------|---------------|
| n < 50 | Insertion sort (simple, fast for small n) |
| n < 1000 | Any O(n²) works |
| n < 10⁶ | O(n log n): merge sort / quick sort |
| n > 10⁶ | Consider O(n): radix sort, counting sort |
| Key-value lookup | Hash table (O(1) avg) |
| Ordered data + range queries | BST, AVL, B-Tree |
| Priority-based processing | Heap |
| Hierarchical data | Tree |
| Network/relationship data | Graph |

---

## 25. Memory Diagrams

### Array Memory Layout

```
int arr[6] = {5, 10, 15, 20, 25, 30};

Address: 1000  1004  1008  1012  1016  1020
         ┌────┬────┬────┬────┬────┬────┐
         │  5 │ 10 │ 15 │ 20 │ 25 │ 30 │
         └────┴────┴────┴────┴────┴────┘
          [0]  [1]  [2]  [3]  [4]  [5]

arr[i] = *(arr + i) = *(base + i * sizeof(int))
```

### Linked List Memory Layout

```
head → [1|next] → [2|next] → [3|NULL]
        0xA100     0xC300     0xB200

Stack:  Heap scattered:
┌──────┐  0xA100:┌────┬──────┐  0xC300:┌────┬──────┐  0xB200:┌────┬──────┐
│ head │──▶│  1  │0xC300│──▶│  2  │0xB200│──▶│  3  │ NULL │
└──────┘  └────┴──────┘  └────┴──────┘  └────┴──────┘
```

### Stack Memory

```
PUSH: 10, 20, 30, 40

arr[0]=10  arr[1]=20  arr[2]=30  arr[3]=40
                                 ^top=3

POP → returns 40, top=2
POP → returns 30, top=1
```

### Queue (Circular) Memory

```
QMAX=5:  enqueue(A,B,C,D), dequeue(), dequeue(), enqueue(E,F)

Index:   0    1    2    3    4
After:  [E]  [F]  [C]  [D]  [--]
             ^                  ^
           front=1             rear=1 (wrapped)
```

### Binary Tree Memory

```
        50
       /  \
      30   70
     / \
    20  40

Nodes in heap:
root: {50, left=&30node, right=&70node}
      {30, left=&20node, right=&40node}
      {70, left=NULL,    right=NULL}
      {20, NULL, NULL}
      {40, NULL, NULL}
```

### Hash Table with Chaining

```
Table:
[0] → NULL
[1] → [key=11,val=A] → [key=21,val=B] → NULL
[2] → [key=2, val=C] → NULL
[3] → NULL
[4] → [key=14,val=D] → NULL
...

Hash(11)=1, Hash(21)=1 → collision → chained
```

---

## 26. Complexity Reference Tables

### Data Structure Operations

| Data Structure | Access | Search | Insert | Delete | Space |
|---------------|--------|--------|--------|--------|-------|
| Array | O(1) | O(n) | O(n) | O(n) | O(n) |
| Stack | O(n) | O(n) | O(1) | O(1) | O(n) |
| Queue | O(n) | O(n) | O(1) | O(1) | O(n) |
| Singly Linked List | O(n) | O(n) | O(1) | O(1) | O(n) |
| Doubly Linked List | O(n) | O(n) | O(1) | O(1) | O(n) |
| Hash Table | O(1) avg | O(1) avg | O(1) avg | O(1) avg | O(n) |
| BST (balanced) | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| BST (skewed) | O(n) | O(n) | O(n) | O(n) | O(n) |
| AVL Tree | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| Red-Black Tree | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| Heap (binary) | — | O(n) | O(log n) | O(log n) | O(n) |
| B-Tree (order m) | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| Trie | — | O(L) | O(L) | O(L) | O(ALPHA·n·L) |
| Graph (Adj List) | O(V+E) | O(V+E) | O(1) | O(E) | O(V+E) |

### Sorting Algorithm Complexity

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Bubble | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection | O(n²) | O(n²) | O(n²) | O(1) | No |
| Insertion | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Merge | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| Counting | O(n+k) | O(n+k) | O(n+k) | O(k) | Yes |
| Radix | O(nk) | O(nk) | O(nk) | O(n+k) | Yes |

### Graph Algorithm Complexity

| Algorithm | Time | Space | Use |
|-----------|------|-------|-----|
| BFS | O(V+E) | O(V) | Shortest path (unweighted) |
| DFS | O(V+E) | O(V) | Topological sort, SCC |
| Dijkstra | O((V+E)log V) | O(V) | Shortest path (positive weights) |
| Bellman-Ford | O(VE) | O(V) | Shortest path (neg weights) |
| Floyd-Warshall | O(V³) | O(V²) | All-pairs shortest path |
| Kruskal | O(E log E) | O(V) | MST |
| Prim | O(E log V) | O(V) | MST |

---

## 27. Learning & Interview Preparation Roadmap

### Beginner (0–1 Year)

**Master:**
- [ ] Arrays — all operations, 2D arrays
- [ ] Strings — character arrays, string.h functions
- [ ] Pointers — pointer arithmetic, pointer to struct
- [ ] Singly Linked List — all operations
- [ ] Stack (array + linked list)
- [ ] Queue (array + circular)
- [ ] Linear and Binary Search
- [ ] Bubble, Selection, Insertion Sort

**Tools:** `gcc -g`, `gdb`, `valgrind`  
**Practice:** 15 beginner programs from this guide

---

### Intermediate (1–3 Years)

**Master:**
- [ ] Doubly and Circular Linked List
- [ ] Binary Tree — all traversals (recursive + iterative)
- [ ] BST — insert, search, delete (all 3 cases)
- [ ] Hashing — chaining and open addressing
- [ ] Graph — BFS, DFS, adjacency representations
- [ ] Merge Sort, Quick Sort
- [ ] Dynamic memory — malloc, free, no leaks

**Practice:** Programs 16–35

---

### Experienced (3–5 Years)

**Master:**
- [ ] AVL Tree — rotations
- [ ] Heap — heapify, heap sort, priority queue
- [ ] Trie — insert, search, delete
- [ ] Disjoint Set — path compression + union by rank
- [ ] Graph algorithms — Dijkstra, Bellman-Ford, Kruskal, Topological Sort
- [ ] Segment Tree, Fenwick Tree
- [ ] LRU Cache design

**Practice:** Programs 36–50

---

### Expert / System Design

**Master:**
- [ ] Red-Black Tree (concepts + Linux kernel usage)
- [ ] B-Tree / B+ Tree (database concepts)
- [ ] Consistent Hashing
- [ ] Skip List
- [ ] Cache-aware algorithms (locality of reference)
- [ ] Memory-efficient data structures

---

### Interview Prep by Company Type

| Company Type | Focus DS | Focus Algorithms |
|-------------|----------|-----------------|
| Service-based | Array, Linked List, Stack, Queue, Sort, Search | Sorting, searching, basic DS |
| Product-based (mid) | BST, Heap, Hashing, Graph, Trie | BFS/DFS, dynamic programming |
| FAANG/Top Product | All DS + system design | Optimization, amortized analysis, system design |
| Embedded | Array, Circular Buffer, Linked List | Real-time constraints, O(1) ops |
| Linux Kernel | Linked List (list_head), RB-Tree, Hash | kernel-style APIs |

### Weekly Study Plan (12 Weeks)

| Week | Topic | Programs |
|------|-------|----------|
| 1 | Arrays + Complexity | 1–3 |
| 2 | Sorting basics | 4–6 |
| 3 | Linked Lists | 7–8, 17–18 |
| 4 | Stack + Queue | 9–11, 15–16 |
| 5 | Trees + Traversals | 28–29 |
| 6 | BST | 14, 19 |
| 7 | Hashing | 20 |
| 8 | Graph BFS/DFS | 21 |
| 9 | Heap + Sort | 13, 23 |
| 10 | AVL + Trie | 22, 30 |
| 11 | Advanced: Segment, Dijkstra | 37, 40 |
| 12 | LRU, Disjoint Set, MST | 36, 38, 39 |

---

*End of Data Structures in C — Complete Master Guide*  
*Cover: Theory · 50 Programs · 100+ Interview Q&A · Memory Diagrams · Complexity Tables · Case Studies · Roadmap*
