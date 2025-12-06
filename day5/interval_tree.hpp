#pragma once

#include <memory>
#include <queue>
#include <cassert>
#include <vector>
#include <iostream>

struct IntervalNode;
typedef std::shared_ptr<IntervalNode> NodePtr;

struct IntervalNode: std::enable_shared_from_this<IntervalNode> {
    size_t min;
    size_t max;
    std::shared_ptr<IntervalNode> left;
    std::shared_ptr<IntervalNode> right;
    std::shared_ptr<IntervalNode> parent;
    IntervalNode(size_t min, size_t max) : min(min), max(max), left(nullptr), right(nullptr), parent(nullptr) {}


};

struct IntervalTree {
    NodePtr root;
    IntervalTree() : root(nullptr) {}


    bool overlap(NodePtr a, NodePtr b) {
        if (!a || !b) return false;
        if (a->max < b->min || a->min > b->max) return false;
        else return true;
    }

    void insert(NodePtr child, NodePtr par) {
        bool inserted = false;
        while (!inserted) {
            if (overlap(par, child)) {
                merge(par, child);
                inserted = true;
            } else {
                if (child->max < par->min) {
                    if (!par->left) {
                        par->left = child;
                        child->parent = par;
                        inserted = true;
                    } else {
                        par = par->left;
                    }
                } else if (child->min > par->max) {
                    if (!par->right) {
                        par->right = child;
                        child->parent = par;
                        inserted = true;
                    } else {
                        par = par->right;
                    }
                }
            }
        }
    }

    void insert(NodePtr child) {
        if (!root) {
            root = child;
            return;
        }
        insert(child, root);
    }

    void insert(size_t nmin, size_t nmax) {
        NodePtr new_node = std::make_shared<IntervalNode>(nmin, nmax);
        insert(new_node);
    }

    void rev_in_order(NodePtr node, std::queue<NodePtr>& res) {
        if (!node) return;
        rev_in_order(node->right, res);
        res.push(node);
        rev_in_order(node->left, res);
    }

    void fwd_in_order(NodePtr node, std::queue<NodePtr>& res) {
        if (!node) return;
        fwd_in_order(node->left, res);
        res.push(node);
        fwd_in_order(node->right, res);
    }

    void merge(NodePtr o_node, NodePtr n_node) {
        assert(!n_node->parent && !n_node->left && !n_node->right);
        NodePtr merged_node = std::make_shared<IntervalNode>(
            std::min(o_node->min, n_node->min), std::max(o_node->max, n_node->max)
        );
        std::queue<NodePtr> o_left_children;
        std::queue<NodePtr> o_right_children;
        std::vector<NodePtr> merged_children;
        rev_in_order(o_node->left, o_left_children);
        fwd_in_order(o_node->right, o_right_children);
        while (!o_left_children.empty() || !o_right_children.empty()) {
            if (!o_left_children.empty()) {
                NodePtr left_child = o_left_children.front();
                o_left_children.pop();
                if (overlap(left_child, merged_node)) {
                    merged_node->min = std::min(merged_node->min, left_child->min);
                    merged_node->max = std::max(merged_node->max, left_child->max);
                } else {
                    left_child->parent = nullptr;
                    left_child->left = nullptr;
                    left_child->right = nullptr;
                    merged_children.push_back(left_child);
                }
            }
            if (!o_right_children.empty()) {
                NodePtr right_child = o_right_children.front();
                o_right_children.pop();
                if (overlap(right_child, merged_node)) {
                    merged_node->min = std::min(merged_node->min, right_child->min);
                    merged_node->max = std::max(merged_node->max, right_child->max);
                } else {
                    right_child->parent = nullptr;
                    right_child->left = nullptr;
                    right_child->right = nullptr;
                    merged_children.push_back(right_child);
                }
            }
        }
        NodePtr o_parent = o_node->parent;
        o_node->parent = nullptr;
        if (o_parent) {
            if (o_parent->left == o_node) {
                o_parent->left = merged_node;
            } else {
                o_parent->right = merged_node;
            }
        } else {
            root = merged_node;
        }
        merged_node->parent = o_parent;
        for (NodePtr child : merged_children) {
            insert(child, merged_node);
        }
    }

    bool contains(size_t val, NodePtr n) {
        if (val >= n->min && val <= n->max) {
            return true;
        }
        if (n->left && contains(val, n->left)) return true;
        if (n->right && contains(val, n->right)) return true;
        return false;
    }

    bool contains(size_t val) {
        return contains(val, root);
    }


    size_t interval_span() {
        std::queue<NodePtr> q;
        q.push(root);
        size_t count = 0;
        while (!q.empty()) {
            NodePtr node = q.front();
            q.pop();
            count += (node->max - node->min + 1);

            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }
        return count;
    }


    // Credit to Claude for the below two functions.
    void print_helper(NodePtr node, std::string prefix, bool isLeft) {
        if (!node) return;

        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──");
        std::cout << "[" << node->min << ", " << node->max << "]" << std::endl;

        if (node->left || node->right) {
            if (node->left) {
                print_helper(node->left, prefix + (isLeft ? "│   " : "    "), true);
            }
            if (node->right) {
                print_helper(node->right, prefix + (isLeft ? "│   " : "    "), false);
            }
        }
    }

    void print() {
        std::cout << "========== IntervalTree ==========" << std::endl;
        if (!root) {
            std::cout << "(empty tree)" << std::endl;
            return;
        }
        std::cout << "[" << root->min << ", " << root->max << "]" << std::endl;
        if (root->left) {
            print_helper(root->left, "", true);
        }
        if (root->right) {
            print_helper(root->right, "", false);
        }
        std::cout << "==================================" << std::endl;
    }

};
