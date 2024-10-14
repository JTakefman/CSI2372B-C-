#include <iostream>

using namespace std;

class Graph {
    class Node {
        public:
            Node* next;
            Node* prev;
            int val;
            Node() {
                next=nullptr;
                next=nullptr;
                val=-1;
            };
            Node(Node* in_next, Node* in_prev, int in_val){
                next= in_next;
                prev = in_prev;
                val=in_val;
            }
    };
    private:
        int current_size;
        Node **arr;
    public:
        Graph() {
            current_size=5;
            arr = new Node*[current_size];
            for (int i = 0; i < current_size; i++) {
                arr[i]= new Node(nullptr, nullptr, -1);
            }
        }
        Graph(int size) {
            current_size=size;
            arr = new Node*[current_size];
            for (int i = 0; i < current_size; i++) {
                arr[i]= new Node(nullptr, nullptr, -1);
            }
        }
        ~Graph() {
            cout << "Graph destructor called" << endl;
            for (int i = 0; i < current_size; i++) {
                clear_node(i);
            }
            for (int i = 0; i < current_size; i++) {
                delete arr[i];
            }
            delete[] arr;
        }

        void clear_node(int nd) {
            cout << "Clearing node " << nd << endl;
            Node * current = arr[nd];
            //Skip assuming nothing to clear
            if (current->val == -1) {
                return;
            }
            while (current != nullptr) {
                Node *after = current->next;
                current->next = nullptr;
                current->prev=nullptr;
                delete current;
                current = after;
            }
            //Starting point for each node
            arr[nd] = new Node(nullptr, nullptr, -1);
        }


        void print_graph() {
            for (int i = 0; i < current_size; i++) {
                cout << i << "=>";
                Node * current = arr[i];
                //Slightly jank in that it skips initial -1 due to implicit next
                //AND IT SKIPS THE END DUMBASS
                bool end = false;
                while(!end) {
                    if (current->next==nullptr) {
                        if (current->val != -1) {
                            cout << current->val;
                        }
                        end = true;
                    }
                    else {
                        if (current->val != -1) {
                            cout << current->val << ", ";
                        }
                        current = current->next;
                    }
                }
                cout << endl;
            }
        }

        bool edge_exist(int start, int end) {
            if (start > current_size-1 || end > current_size-1 or start < 0 or end < 0) {
                cout << "Invalid edge, exceeds bounds of array: \t" << end << endl;
                return false;
            }
            Node * current = arr[start];
            while (current != nullptr) {
                if (current->val == end)  {
                    cout << "Edge: \t " << start <<", " << end << " exists" << endl;
                    return true;
                }
                current = current->next;
            }
            cout << "Edge: \t " << start <<", " << end << " does not exist" << endl;
            return false;
        }

        void remove_edge(int start, int end) {
            if (start > current_size-1 || end > current_size-1 or start < 0 or end < 0) {
                cout << "Invalid edge, exceeds bounds of array: \t" << end << endl;
                return;
            }
            Node * current = arr[start];
            cout << "About to start removal of edge:\t " << start <<", " << end << endl;
            while (current != nullptr) {
                if (current->val == end) {
                    if (current->next==nullptr) {
                        Node * last = current->prev;
                        last->next = nullptr;
                        current->prev = nullptr;
                        current->next=nullptr;
                        delete current;
                    }
                    else if (current->prev == nullptr) {
                        current->next->prev=nullptr;
                        arr[start]=current->next;

                        current->next=nullptr;
                        current->prev=nullptr;
                        delete current;
                    }
                    else {
                        Node *last = current->prev;
                        Node *after = current->next;
                        last->next= after;
                        after->prev = last;
                        current->prev = nullptr;
                        current->next=nullptr;
                        delete current;
                    }
                    return;
                }
                current = current->next;
            }
            cout << "Can't remove, edge does not exist between nodes: \t " << start <<", " << end  << endl;

        }

        void add_edge(int start, int end) {
            if (start > current_size-1 || end > current_size-1 or start < 0 or end < 0) {
                cout << "Invalid edge, exceeds bounds of array: \t" << end << endl;
                return;
            }
            Node * current = arr[start];
            Node * to_add = new Node(nullptr, nullptr, end);

            bool middle = false;
            bool end_list = false;

            //If at start of list just swap value of end for first connection
            if (current->val==-1) {
                current->val = end;
                return;
            }
            //Also check if an existing start point are you greater
            else if (end < current->val) {
                to_add->next=current;
                current->prev=to_add;
                arr[start]=to_add;
                return;
            }



            while(!end_list and !middle) {
                if (current->val > end) {
                    middle = true;
                }
                else if (current->val == end) {
                    cout << "Invalid edge: duplicate: \t" << end << endl;
                    return;
                }
                else {
                    if (current->next == nullptr) {
                        end_list = true;
                    }
                    else {
                        current = current->next;
                    }

                }

            }
            if (middle) {
                Node * last = current->prev;
                //Middle points to front
                to_add->next = current;
                current->prev = to_add;
                //Middle points to back
                last->next = to_add;
                to_add->prev = last;
            }
            else {
                //If not in middle add to end
                current->next = to_add;
                to_add->prev=current;
                to_add->next=nullptr;
            }             
        }
};

int main() {
    Graph g = Graph();
    g.add_edge(0, 2);
    g.add_edge(0, 1);
    g.add_edge(0, 3);
    g.add_edge(0, 4);
    g.add_edge(0, 4);
    g.add_edge(0, 5);

    g.add_edge(1, 3);
    g.add_edge(1, 2);
    g.add_edge(1, 0);
    g.add_edge(1, 1);
    g.add_edge(1, 0);

    g.add_edge(2, 0);
    g.add_edge(2, 2);
    g.add_edge(2, 2);
    g.add_edge(2, -5);
    g.add_edge(-5, -5);

    g.add_edge(3, 1);
    g.add_edge(3, 0);
    g.add_edge(3, 2);

    g.print_graph();

    g.edge_exist(0,4);
    g.remove_edge(0,4);
    g.edge_exist(0,4);
    g.remove_edge(3,0);
    g.edge_exist(3,0);
    g.remove_edge(1,2);
    g.remove_edge(1,2);
    g.remove_edge(2,3);
    g.remove_edge(1,1);

    g.print_graph();
    g.clear_node(0);
    g.print_graph();
    return 0;
}