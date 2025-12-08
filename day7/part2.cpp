#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

struct Node;
typedef std::shared_ptr<Node> NodePtr;

struct Node: std::enable_shared_from_this<Node> {
    size_t value;
    std::vector<NodePtr> parents;
    std::vector<NodePtr> children;

    Node() : value(0), parents(), children() {}
};

void print_nodeset(const std::vector<NodePtr>& nodeset) {
    for (NodePtr n : nodeset) {
        if (n) {
            std::cout << "(" << n->value << ") ";
        } else {
            std::cout << "... ";
        }
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]) {
    std::ifstream input_file(argv[1]);
    std::string line;

    std::vector<NodePtr> nodes;
    Node root;
    NodePtr root_ptr = std::make_shared<Node>(root);
    if (std::getline(input_file, line)) {
        nodes.resize(line.size(), nullptr);
        nodes[line.find('S')] = root_ptr;
    }

    root_ptr->value = 1;
    //print_nodeset(nodes);
    while (std::getline(input_file, line)) {
        std::vector<NodePtr> running_nodes(line.size(), nullptr);
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '^' && nodes[i]) {
                if((i - 1) >= 0) {
                    if (!running_nodes[i-1]) {
                        Node left;
                        NodePtr left_ptr = std::make_shared<Node>(left);
                        left_ptr->value = nodes[i]->value;
                        left_ptr->parents.push_back(nodes[i]);
                        nodes[i]->children.push_back(left_ptr);
                        running_nodes[i-1] = left_ptr;
                    } else {
                        running_nodes[i-1]->value += nodes[i]->value;
                        running_nodes[i-1]->parents.push_back(nodes[i]);
                        nodes[i]->children.push_back(running_nodes[i-1]);
                    }
                }
                if((i + 1) < line.size()) {
                    if (!running_nodes[i+1]) {
                        Node right;
                        NodePtr right_ptr = std::make_shared<Node>(right);
                        right_ptr->value = nodes[i]->value;
                        right_ptr->parents.push_back(nodes[i]);
                        nodes[i]->children.push_back(right_ptr);
                        running_nodes[i+1] = right_ptr;
                    } else {
                        running_nodes[i+1]->value += nodes[i]->value;
                        running_nodes[i+1]->parents.push_back(nodes[i]);
                        nodes[i]->children.push_back(running_nodes[i+1]);
                    }
                }
                running_nodes[i] = nullptr;
            } else if (line[i] == '.' && nodes[i]) {
                if(!running_nodes[i]) {
                    running_nodes[i] = nodes[i];
                } else {
                    running_nodes[i]->value += nodes[i]->value;
                    running_nodes[i]->parents.push_back(nodes[i]);
                    nodes[i]->children.push_back(running_nodes[i]);
                }
            }
        }
        nodes = running_nodes;

        //print_nodeset(nodes);
    }

    size_t paths = 0;
    for (NodePtr node : nodes) {
        if (node) paths += node->value;
    }
    std::cout << paths << std::endl;

    return 0;
}
