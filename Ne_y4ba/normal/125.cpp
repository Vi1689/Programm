// Решена

#include <algorithm>
#include <iostream>
#include <vector>

struct node {
    size_t data;
    node* right;
    node* left;
    node* parent;
};

class bin_tree {
private:
    node* root;

    std::vector<size_t> arr;

    node* create_node(size_t arg)
    {
        node* temp = new node[1];
        temp->data = arg;
        temp->left = nullptr;
        temp->right = nullptr;
        temp->parent = nullptr;
        return temp;
    }

    void bin_tree_free(node* tree)
    {
        if (tree != nullptr) {
            bin_tree_free(tree->left);
            bin_tree_free(tree->right);
            delete[] tree;
        }
    }

    void print(node* tree, size_t count)
    {
        if (tree) {
            print(tree->left, count);
            print(tree->right, count);
            if (tree->left != nullptr && tree->right != nullptr) {
                arr.push_back(tree->data);
            }
        }
    }

public:
    bin_tree()
    {
        root = create_node(0);
    }

    bin_tree(size_t arg)
    {
        root = create_node(arg);
    }

    bool insert(size_t arg)
    {
        node* temp = root;
        node* parent = root;

        while (temp != nullptr) {
            parent = temp;
            if (arg > temp->data) {
                temp = temp->right;
            } else if (arg < temp->data) {
                temp = temp->left;
            } else {
                return false;
            }
        }

        temp = create_node(arg);
        temp->parent = parent;

        if (parent == nullptr) {
            root = temp;
        } else {
            if (parent->data > temp->data) {
                parent->left = temp;
            } else if (parent->data < temp->data) {
                parent->right = temp;
            }
        }
        return true;
    }

    size_t lookup(size_t arg)
    {
        node* temp = root;
        size_t count = 1;

        while (temp != nullptr) {
            if (arg > temp->data) {
                temp = temp->right;
                count++;
            } else if (arg < temp->data) {
                temp = temp->left;
                count++;
            } else {
                return count;
            }
        }
        return false;
    }

    size_t max()
    {
        node* temp = root;
        size_t max = 0;

        while (temp != nullptr) {
            max = temp->data;
            temp = temp->right;
        }

        return max;
    }

    size_t min()
    {
        node* temp = root;
        size_t min = 0;

        while (temp != nullptr) {
            min = temp->data;
            temp = temp->left;
        }

        return min;
    }

    void delete_node(size_t arg)
    {
        node* temp = root;

        while (temp != nullptr) {
            if (temp->data > arg) {
                temp = temp->left;
            } else if (temp->data < arg) {
                temp = temp->right;
            } else {
                break;
            }
        }

        if (temp == nullptr) {
            return;
        }
        if (temp->left == nullptr && temp->right == nullptr) {
            if (temp->parent != nullptr) {
                if (temp->parent->data > temp->data) {
                    temp->parent->left = nullptr;
                } else {
                    temp->parent->right = nullptr;
                }
            } else {
                root = nullptr;
            }
            delete[] temp;
        } else if (temp->left == nullptr) {
            if (temp->parent != nullptr) {
                if (temp->parent->data > temp->data) {
                    temp->parent->left = temp->right;
                } else {
                    temp->parent->right = temp->right;
                }
            } else {
                temp->right->parent = nullptr;
                root = temp->right;
            }
            delete[] temp;
        } else if (temp->right == nullptr) {
            if (temp->parent != nullptr) {
                if (temp->parent->data > temp->data) {
                    temp->parent->left = temp->left;
                } else {
                    temp->parent->right = temp->left;
                }
            } else {
                temp->left->parent = nullptr;
                root = temp->left;
            }
            delete[] temp;
        } else {
            node* conservation = temp;
            if (temp->parent != nullptr) {
                temp = temp->right;
                while (temp != nullptr) {
                    if (temp->left == nullptr) {
                        break;
                    }
                    temp = temp->left;
                }
                if (conservation != temp->parent) {
                    temp->parent->left = temp->right;
                }
                if (conservation->right != temp) {
                    temp->right = conservation->right;
                    temp->right->parent = temp;
                }
                temp->left = conservation->left;
                temp->parent = conservation->parent;
                temp->left->parent = temp;
                if (temp->parent->data > temp->data) {
                    temp->parent->left = temp;
                } else {
                    temp->parent->right = temp;
                }
            } else {
                temp = temp->right;
                while (temp != nullptr) {
                    if (temp->left == nullptr) {
                        break;
                    }
                    temp = temp->left;
                }
                if (conservation != temp->parent) {
                    temp->parent->left = temp->right;
                }
                if (conservation->right != temp) {
                    temp->right = conservation->right;
                    temp->right->parent = temp;
                }
                temp->left = conservation->left;
                temp->parent = conservation->parent;
                temp->left->parent = temp;
                root = temp;
            }
            delete[] conservation;
        }
    }

    void my_print()
    {
        print(root, 1);
    }

    void task_124()
    {
        std::sort(arr.begin(), arr.end());

        for (const auto i : arr) {
            std::cout << i << "\n";
        }
    }

    ~bin_tree()
    {
        bin_tree_free(root);
    }
};

int main()
{
    size_t a;
    std::cin >> a;
    bin_tree tree(a);
    while (std::cin >> a) {
        if (!a) {
            goto end;
        }
        tree.insert(a);
    }
end:
    tree.my_print();
    tree.task_124();
    return 0;
}