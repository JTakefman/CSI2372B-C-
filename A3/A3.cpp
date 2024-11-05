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
    protected:
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
        int current_size;
        Node **arr;
    public:
        Graph() {
            current_size=6;
            arr = new Node*[current_size];
            for (int i = 0; i < current_size; i++) {
                arr[i] = nullptr;
            }
        }
        Graph(int size) {
            cout << "Constructing Graph" << endl;
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


        virtual string print_adj() const{
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
                        //out << "Moving from " << current << " -> " << temp->val << endl;
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
            os << g.print_adj() << endl;
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
            cout << "Constructing Forest " << endl;
        }

        void add_edge(int start, int end) override {
            if (start > current_size-1 || end > current_size-1 or start < 0 or end < 0) {
                cout << "Invalid edge: exceeds bounds of array: \t" << end << endl;
                return;
            }
            bool visited[current_size]{false};
            if (path_exists(start, end, visited)) {
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

        using Graph::operator++;
        using Graph::operator--;
};

class Tree : public Forest {

    private:
        /*For a tree, we obviously don't want the user adding extra edges as this will by defintion
          create a cycle since the graph is already connected Hence we make add_edge() private
          in order to ensure the user can only add by adding a new vertex, connected to a given node
          or by incrementing.

          The same principle applies for remove_edge as if the user can remove a random edge, this will
          prevent the graph from being connected.
        */
        int root_node = 0;
        using Forest::add_edge;
        using Forest::remove_edge;

    public:
        Tree(): Forest() {
            cout << "Constructing Tree" << endl;
        }

        void add_vertex(int start) {
            if (start > current_size-1 || start < 0) {
                cout << "Invalid vertex: " << start << " exceeds bounds of array with max vertex: \t" << current_size-1 << endl;;
                return;
            }

            //By default we only add nodes as leaves, so you only need to specify the start point
            //thus, you simply need to increase the size of the graph then call add_edge
            Graph::operator++();
            Forest::add_edge(start, current_size-1);
        }

        void set_root(int root) {
            if (root < 0 || root > current_size) {
                cout << "Invalid root node" << endl;
                return;
            }
            root_node=root;
        }

        

        //add_vertex needs to increment the size of the 
        Tree operator ++(int) {
            Tree temp = *this;
            add_vertex(current_size-1);
            return temp;
        }

        Tree operator --(int) {
            cout << "Entered decrement root node is " << root_node << endl;
            cout << "Current size is " << current_size << endl;
            //I did this because an empty graph is technically vacuously connected and not considered a tree.
            //So be convention I chose to keep the tree at size 1 at a minimum.
            if (current_size==1) {
                cout << "Error: Cannot decrement tree further than one" << endl;
                return *this;
            }
            //Edge case for removing the node set as root but not changing it.
            //Default to 0
            if (root_node >= current_size-1) {
                cout << "Error: tried to decrement set root node, defaulting to 0" << endl;
                root_node=0;
                return *this;
            }
            Tree temp = *this;
            //Since a leaft 
            Graph::operator--();
            return temp;
        }

        friend ostream& operator<<(ostream& os, const Tree& t) {
            os << t.print_wrapper() << endl;
            return os;
        }

        
    private:
        string print_wrapper() const {
            //cout << " about to print, root node is " << root_node << endl;
            //Should never happen due to decrement convention preventing further than one.
            if (current_size==0) {
                cout << "Error, tree is empty" << endl;
                return "";
            }
            bool visited[current_size]{false};
            return print_graph(root_node, visited, 0);
        }

        string print_graph(int current, bool* visited, int level) const{
            
            visited[current] = true;
            Node * temp = arr[current];
            string ret = "";
            if (current == root_node) {
                ret+= to_string(current) + "\n";
            }
            //If no children print yourself
            while(temp!= nullptr) {
                if (!visited[temp->val]) {
                    string front_space(3*level, ' ');
                    ret += front_space + "---" + to_string(temp->val) + "\n"; 
                    ret += print_graph(temp->val, visited, level+1);
                }
                temp = temp->next;
            }
            //All nodes under this were paths back to an existing explored node so we need to add

            return ret;
        }


};

void print_vec(vector<int> input) {
    cout << "[";
    for (int i = 0; i < input.size();i++) {
        cout << input[i] << " ";
    }
    cout << "]";
}


void run_forest() {
    cout << "\n\n********************\nSTART OF FOREST TEST\n********************\n\n\n";
    Forest f;
    f++;
    f++;
    //Add a new edge between the vertices
    f.add_edge(0,1);
    cout << f;
    //Edges will create a cycle, so blocked from adding
    f.add_edge(0,1);
    f.add_edge(1,0);
    //Valid edge so it will add
    f.add_edge(2,0);
    cout << f;
    //Again invalid
    f.add_edge(2,1);
    f.add_edge(1,2);
    //Now removing edges
    f.remove_edge(2,0);
    cout << f;
    //Invalid remove edge
    f.remove_edge(2,0);
    //Now increment again
    f++;
    f++;
    cout << "after incrementing twice " << f;
    //Add new edges
    f.add_edge(3, 0);
    f.add_edge(3, 2);
    cout << "Added edges 3-0 and 3-2" << f;
    //No valid edges because of cycle except for 4,2
    f.add_edge(3, 1);
    //Only valid edge, rest won't work
    f.add_edge(2, 4);
    f.add_edge(3, 4);
    f.add_edge(1, 2);
    f.add_edge(4, 3);
    cout << "\n\nAfter adding 4-2 and attempted invalid edges" << endl;
    cout << f;
    //
    f.edge_exist(4,3);
    f.edge_exist(1,0);
    //All invalid
    f.edge_exist(1,-1);
    f.edge_exist(-1,4);
    f.edge_exist(-1,90);
    //Decrement twice
    f--;
    f--;
    //Now is no longer connected. Expected and allowed since the forest only specifies no cycles not connectivity
    cout << endl << "After decrementing twice" << f;

}

void run_tree() {
    cout << "\n\n******************\nSTART OF TREE TEST\n******************\n\n\n";
    Tree t;
    cout << "First adding new node with edge to 0" << endl;
    t.add_vertex(0);
    cout << "First print " << endl << t << endl;
    cout << "Adding another node with edge to 0" << endl;
    t.add_vertex(0);
    cout << t;
    cout << "Adding 3 nodes" << endl;
    //Error check to show invalid addition
    t.add_vertex(3); 
    //Valid additions
    t.add_vertex(1);
    t.add_vertex(2);
    //Now how adjacency list
    cout << "adjacency list form:" << endl;
    cout << t.print_adj();
    cout << "Now showing dfs and bfs as well as print from each node as root" << endl;

    t.set_root(0);
    cout << t;
    cout << "DFS:" << endl;
    print_vec(t.DFS(0));
    cout << endl << "BFS:" << endl;
    print_vec(t.BFS(0));
    cout << endl << endl;

    t.set_root(1);
    cout << t;
    cout << "DFS:" << endl;
    print_vec(t.DFS(1));
    cout << endl << "BFS:" << endl;
    print_vec(t.BFS(1));
    cout << endl<< endl;

    t.set_root(2);
    cout << t;
    cout << "DFS:" << endl;
    print_vec(t.DFS(2));
    cout << endl << "BFS:" << endl;
    print_vec(t.BFS(2));
    cout << endl << endl;
    
    t.set_root(3);
    cout << t;
    cout << "DFS:" << endl;
    print_vec(t.DFS(3));
    cout << endl << "BFS:" << endl;
    print_vec(t.BFS(3));
    cout << endl << endl;
    
    t.set_root(4);
    cout << t;
    cout << "DFS:" << endl;
    print_vec(t.DFS(4));
    cout << endl << "BFS:" << endl;
    print_vec(t.BFS(4));
    cout << endl << endl;
    
    cout << "Now incrementing hte graph twice" << endl;
    t++;
    t++;
    cout << endl << t << endl;
    cout << "No add a 2 more nodes, connected to 0";
    cout << endl;

    t.add_vertex(0);
    t.add_vertex(0);
    t.set_root(0);
    cout << t;
    cout << "prior to decrement loop" << endl;
    cout << t;

    //Erase all nodes
    int s = t.get_current_size();
    t.set_root(0);
    cout << "Now starting decrement loop with initial state" << endl;
    cout << t << endl;
    cout << "adjacency list: " << endl << t.print_adj();
    
    //Done to demonstrate behaviour if removing a node that is set as root
    cout << "Now resetting root to 5 for decrement loop" << endl;
    t.set_root(5);
    for (int i = 0; i < s; i++) {
        cout << "i is " << i << " size is " << t.get_current_size() << endl;
        cout << t;
        t--;
    }
    cout << t;
    //Trying to decremnt past one node
    cout << "Now trying to decrement past -1" << endl;
    t--;
}

int main() {
    run_forest();
    run_tree();
    return 0;
}