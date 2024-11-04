// ------------------------------------------------------------------------------
// Assignment 1
// Written by: Jordan Takefman, 300171459
// For CSI2372 Section B
// Time to complete:
// Resources: Standard C++ Documentation
// -----------------------------------------------------------------------------

#include <iostream>
#include <deque>
#include <vector>
#include <string>

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
    //Changed to protected from private for the sake of ease in the base classes.
    //I don't see anything in the assignment instructions that says we can't do this so I'm assuming
    //it's valid.
    protected:
        int current_size;
        Node **arr;
    public:
        Graph() {
            cout << "I am a graph" << endl;
            current_size=6;
            arr = new Node*[current_size];
            for (int i = 0; i < current_size; i++) {
                arr[i] = nullptr;
            }
        }
        Graph(int size) {
            current_size=size;
            arr = new Node*[current_size];
            for (int i = 0; i < current_size; i++) {
                arr[i] = nullptr;
            }
        }

        Graph(Graph& g) {
            current_size=g.current_size;
            arr = new Node*[current_size];
            for (int i = 0; i < current_size; i++) {
                arr[i] = nullptr;
            }
            
            for (int i = 0; i < g.current_size; i++) {
                Node * temp = g.arr[i];

                while (temp != nullptr) {
                    int test = temp->val;
                    add_edge(i, test);
                    temp=temp->next;
                }
            }
        }
        ~Graph() {
            //cout << "Graph destructor called" << endl;
            clear_arr();
        }

        int get_current_size() {
            return current_size;
        }

        void clear_arr() {
            for (int i = 0; i < current_size; i++) {
                clear_node(i);
            }
            delete[] arr;
        }
        //Cleans a given node, used in the destructor
        void clear_node(int nd) {
            //cout << "Clearing node " << nd << endl;
            Node * current = arr[nd];
            //Skip assuming nothing to clear
            if (current == nullptr) {
                //cout << "Empty list nothing to clear for " << nd << endl;
                return;
            }
            while (current != nullptr) {
                Node *after = current->next;
                current->next = nullptr;
                current->prev=nullptr;
                delete current;
                current = after;
            }
            arr[nd]=nullptr;
        }

        int get_degree(int nd) {
            if (nd < 0 || nd > current_size) {
                cout << "Invalid input: node does not exist can't return degree" << endl;
                return -1;
            }
            Node * current = arr[nd];
            int deg = 0;
            while (current != nullptr) {
                deg++;
                current = current->next;
            }
            return deg;
        }


        string print_graph() const{
            string ret = "\n";
            if (current_size == 0) {
                return "GRAPH IS EMPTY ADD A NODE";
            }
            for (int i = 0; i < current_size; i++) {
                ret += to_string(i) +"=>";
                Node * current = arr[i];
                

                if (current != nullptr) {
                    bool end = false;
                    while(!end) {
                        if (current->next==nullptr) {
                            if (current->val != -1) {
                                ret += to_string(current->val);
                            }
                            end = true;
                        }
                        else {
                            if (current->val != -1) {
                                ret += to_string(current->val) + ", ";
                            }
                            current = current->next;
                        }
                    }
                }
                ret+="\n";
            }
            return ret;
        }

        bool path_exists(int current, int goal, bool *visited) {
            visited[current] = true;

            if (current==goal) {
                //cout << "Start and goal are the same " << current << " -> " << goal << endl;
                return true;
            }

            if (arr[current] == nullptr) {
                //cout << "Node " << current << " is empty" << endl;
                return false;
            }            

            Node * temp = arr[current];
            while (temp != nullptr) {
                if (temp->val == goal) {
                    //cout << "Found goal " << current << " -> " << goal << endl;
                    return true;
                }
                if (temp->val != current) {
                    bool temp_check;
                    if (!visited[temp->val]) {
                        //cout << "Moving from " << current << " -> " << temp->val << endl;
                        temp_check = path_exists(temp->val, goal, visited);

                    }
                    if (temp_check == true) {
                        //cout << "Path exists " << current << " -> " << temp->val << endl;
                        return true;
                    }
                }
                temp = temp->next;
            }
            //cout << "No path between " << current << " -> " << goal << endl;
            return false;
        }

        bool edge_exist(int start, int end) {
            if (start > current_size-1 || end > current_size-1 or start < 0 or end < 0) {
                cout << "Invalid edge: exceeds bounds of array: \t" << end << endl;
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
                cout << "Invalid edge: exceeds bounds of array: \t" << end << endl;
                return;
            }
            Node * current = arr[start];
            if (current == nullptr) {
                //cout << "Can't remove edge, node is empty" << endl;
                return;
            }
            //If the first element is null, there are no elements to remove
            while (current != nullptr) {
                if (current->val == end) {
                    //Only element in the list
                    if ( (current->next == nullptr) && (current->prev==nullptr) ) {
                        //cout << "First and only element so deleting edge: "<< start <<", " << end << " at end of list" << endl; ;
                        arr[start]=nullptr;
                        delete current;
                    }
                    //Removing from end
                    else if (current->next==nullptr) {
                        //cout << "Removing: " << start <<", " << end << " at end of list" << endl;
                        Node * last = current->prev;
                        last->next = nullptr;
    
                        current->prev = nullptr;
                        current->next=nullptr;
                        delete current;
                    }
                    //Removing from start
                    else if (current->prev == nullptr) {
                        //cout << "Removing: " << start <<", " << end << " at start of list" << endl;
                        current->next->prev=nullptr;
                        arr[start]=current->next;

                        current->next=nullptr;
                        current->prev=nullptr;
                        delete current;
                    }
                    //Removing from middle
                    else {
                        //cout << "Removing " << start <<", " << end << " in middle of list" << endl;
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

            //cout << "Can't remove, edge does not exist between nodes: \t " << start <<", " << end  << endl;

        }

        virtual void add_edge(int start, int end) {
            if (start > current_size-1 || end > current_size-1 or start < 0 or end < 0) {
                cout << "Invalid edge: exceeds bounds of array: \t" << end << endl;
                return;
            }

            Node * current = arr[start];
            Node * to_add = new Node(nullptr, nullptr, end);

            bool middle = false;
            bool end_list = false;

            //If at start of list just swap value of end for first connection
            if (current==nullptr) {
                //cout << "First edge to add: \t" << start << ", " << end << endl;
                arr[start]=to_add;
                return;
            }
            //Also check if an existing start point are you greater
            else if (end < current->val) {
                //cout << "Added new smallest first edge: \t"<< start << ", " << end << endl;
                to_add->next=current;
                current->prev=to_add;
                arr[start]=to_add;
                return;
            }
            //If not adding to front, search through existing adjacency list
            //to find spot to insert
            while(!end_list and !middle) {
                if (current->val > end) {
                    middle = true;
                }
                else if (current->val == end) {
                    cout << "Invalid edge: duplicate: \t" << start << " : " << end << endl;
                    delete to_add;
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
                //cout << "Adding edge in middle: \t " << start << ", " << end << endl;
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
                //cout << "Adding edge to end: \t" << start << ", " << end << endl;
                current->next = to_add;
                to_add->prev=current;
                to_add->next=nullptr;
            }             
        }


        int is_connected() {
            //Check if all paths exist
            if (current_size==0) {
                return 1;
            }
            
            bool visited[current_size] {false};
            vector<int> order;
            dfs(0, visited, order);
            for (int i = 0; i < current_size; i++) {
                if (!visited[i]) {
                    return false;
                }
            }
            return true;
        }

        void dfs(int current, bool* visited, vector<int> &order) {
            visited[current]=true;
            order.push_back(current);
            Node * temp = arr[current];
            while(temp!= nullptr) {
                if (!visited[temp->val]) {
                    dfs(temp->val, visited, order);
                }
                temp = temp->next;
            }
        }


        //The instructions on brightspace indicated a list needed to be returned but didn't
        //specify what strucutre or container, so for the sake of ease I am using a vector.

        //This function is a higher level wrapper for the real DFS so the user doesn't have
        //to allocate a visited array every time they call it.
        vector<int> DFS(int start) {
            vector<int> order;
            if (start < 0 || start > current_size) {
                cout << "Invalid start node, returning empty list";
                return order;
            }
            if (current_size==0) {
                cout << "Graph is empty, returning empty list" << endl;
                return order;
            }
            bool visited[current_size] {false};
            dfs(start, visited, order);
            return order;
        }
        //This function is a higher level wrapper for the real BFS so the user doesn't have
        //to allocate a visited array every time they call it.
        vector <int> BFS(int start) {
            vector<int> order;
            deque<int> queue;
            queue.push_back(start);
            if (start < 0 || start > current_size) {
                cout << "Invalid start node, returning empty list";
                return order;
            }
            if (current_size==0) {
                cout << "Graph is empty, returning empty list" << endl;
                return order;
            }
            bool visited[current_size] {false};
            bfs(visited, order, queue);
            return order;
        }

        void bfs(bool* visited, vector<int> &order, deque<int> queue) {
            while(queue.size()!=0) {
                if (!visited[queue.front()]) {
                    visited[queue.front()]=true;
                    order.push_back(queue.front());
                    Node * temp = arr[queue.front()];
                    while(temp!= nullptr) {
                        queue.push_back(temp->val);
                        temp = temp->next;
                    }
                }
                queue.pop_front();
            }
        }

        friend ostream& operator<<(ostream& os, const Graph& g) {
            os << g.print_graph() << endl;
            return os;
        }

        Graph operator ++(int) {
            Graph temp = *this;
            ++(*this);
            return temp;
        }

        Graph & operator++() {
            Node ** new_arr = new Node*[current_size+1];
            //Clear all pointers to null
            for (int i = 0; i < current_size+1; i++) {
                new_arr[i]=nullptr;
            }
             //Copy over all pointers
            for (int i = 0; i < current_size; i++) {
                new_arr[i] = arr[i];
            }
            //Clear current arr;
            for (int i = 0; i < current_size-1; i++) {
                arr[i] = nullptr;
            }
            delete[] arr;
            current_size++;
            arr = new_arr;
            
            return *this;
        }

        Graph operator --(int) {
            Graph temp = *this;
            --(*this);
            return temp;
        }

        Graph & operator--() {
            if (current_size==0) {
                cout << "Can't decrement further, 0 nodes";
                return *this;
            }
            Node ** new_arr = new Node*[current_size-1];
            //Clear all pointers to null
            for (int i = 0; i < current_size-1; i++) {
                new_arr[i]=nullptr;
            }
            //Clear the node that we will lose 
            clear_node(current_size-1);
            for (int i = 0; i < current_size;i++) {
                remove_edge(i, current_size-1);
            }
             //Copy over all pointers
            for (int i = 0; i < current_size-1; i++) {
                new_arr[i] = arr[i];
            }
            //Clear current arr;
            for (int i = 0; i < current_size; i++) {
                arr[i] = nullptr;
            }
            delete[] arr;
            current_size--;
            arr = new_arr;
            return *this;
        }

};

class Forest : public Graph {
    public:
        //Call starting with one node
        
        Forest() : Graph(1) {
            cout << "I am a forest " << endl;
        }

        void  add_edge(int start, int end) override {
            if (start > current_size-1 || end > current_size-1 or start < 0 or end < 0) {
                cout << "Invalid edge: exceeds bounds of array: \t" << end << endl;
                return;
            }
            bool visisted[current_size]{false};
            if (path_exists(start, end, visisted)) {
                cout << "Can't add edge, " << start << " : " << end << " will create cycle: " << start << " is connected to " << end << endl;
                return;
            }
            //Just add an edge going both directions so no need to modify base directed graph class
            Graph::add_edge(start, end);
            Graph::add_edge(end, start);
        }

        void remove_edge(int start, int end) {
            if (start > current_size-1 || end > current_size-1 or start < 0 or end < 0) {
                cout << "Invalid edge: exceeds bounds of array: \t" << end << endl;
                return;
            }
            //Just remove edge so no need to modify base directed graph class

            if (edge_exist(start, end)) {
                Graph::remove_edge(start, end);
                Graph::remove_edge(end, start);
            }

        }
};

void print_vec(vector<int> input) {
    cout << "[";
    for (int i = 0; i < input.size();i++) {
        cout << input[i] << " ";
    }
    cout << "]";
}

int main() {
    
    Forest f;
    f++;
    f++;
    f.add_edge(0,1);
    cout << f;
    f.add_edge(0,1);
    f.add_edge(1,0);
    f.add_edge(2,0);
    cout << f;
    f.add_edge(2,1);
    f.add_edge(1,2);
    f.remove_edge(2,0);
    cout << f;
    f.remove_edge(2,0);
    f++;
    f++;
    cout << f;
    f.add_edge(3, 0);
    f.add_edge(3, 2);
    f.add_edge(3, 1);
    f.add_edge(2, 4);
    f.add_edge(3, 4);
    f.add_edge(1, 2);
    f.add_edge(4, 3);
    cout << f;
    f--;
    f--;
    cout << f;
    return 0;
}