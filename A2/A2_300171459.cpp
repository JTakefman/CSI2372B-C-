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
    private:
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

        void add_edge(int start, int end) {
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
                    cout << "Invalid edge: duplicate: \t" << end << endl;
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


        int connectivity_type() {
            //Check if all paths exist
            if (current_size==0) {
                return 0;
            }
            bool connections[current_size][current_size];
            for (int i = 0; i < current_size; i++) {
                for (int j = 0; j < current_size; j++) {
                    bool visisted[current_size] = {false};
                    connections[i][j] = path_exists(i,j,visisted);
                }
            }

            bool strongly_connected = true;
            for (int i = 0; i < current_size; i++) {
                for (int j = 0; j < current_size; j++) {
                    if (connections[i][j]==false) {
                        strongly_connected=false;
                        break;
                    }
                }
            }
            if (strongly_connected) {
                //cout << "All nodes have path between them, hense, strongly connected" << endl;
                return 3;
            }

            bool uni_connected = true;
            for (int i = 0; i < current_size; i++) {
                for (int j = 0; j < current_size; j++) {
                    if (connections[i][j]==false && connections[j][i]==false) {
                        uni_connected=false;
                        break;
                    }
                }
            }
            if (uni_connected) {
                //cout << "At least one path exists between all pairs, hense, unilaterally connected" << endl;
                return  2;
            }

            Graph temp_g = *this;
            //Since we need to test against an undirected graph we 
            //can add an extra edge for every directed edge existing

            for (int i = 0; i < temp_g.current_size; i++) {
                Node * temp = temp_g.arr[i];
                while (temp!=nullptr) {
                    //This works since add_edge checks for duplicatess
                    temp_g.add_edge(temp->val, i);
                    temp=temp->next;
                }
            }
            //Now having constructed our underlying we test if all paths exist like in the above

            bool connections_2[temp_g.current_size][temp_g.current_size];
            for (int i = 0; i < temp_g.current_size; i++) {
                for (int j = 0; j < temp_g.current_size; j++) {
                    bool visisted[current_size] = {false};
                    connections_2[i][j] = temp_g.path_exists(i,j,visisted);
                }
            }

            /*cout << "Connections 2 " << endl;
            for (int i = 0; i < current_size; i++) {
                cout << i << ":\t";
                for (int j = 0; j < current_size; j++) {
                    cout << connections[i][j] << "\t"; 
                }
                cout << endl << endl;
            }*/

            bool weakly_connected=true;
            for (int i = 0; i < temp_g.current_size; i++) {
                for (int j = 0; j < temp_g.current_size; j++) {
                    if (!connections_2[i][j]) {
                        weakly_connected=false;
                        break;
                   }
                }
            }

            if (weakly_connected) {
                //cout << "The graph is weakly connected" << endl;
                return 1;
            }


            //cout << "The Graph is not connected" << endl;
            return 0;
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

void print_vec(vector<int> input) {
    cout << "[";
    for (int i = 0; i < input.size();i++) {
        cout << input[i] << " ";
    }
    cout << "]";
}

int main() {
    Graph g;
    cout << g;
    cout << "Now adding nodes" << endl;
    //Front insertion
    g.add_edge(0,4);
    //Front insertion
    g.add_edge(0,1);
    //Middle insertion
    g.add_edge(0,3);
    g.add_edge(0,5);
    //Duplicate insertion
    g.add_edge(0,5);
    //Boundaries Exceeded
    g.add_edge(0,6);
    g.add_edge(0,-1);
    //Edge to itself
    g.add_edge(0,0);

    cout << g;
    g.add_edge(2,3);
    g.add_edge(2,1);
    g.add_edge(2,0);
    g.add_edge(4,1);
    g.add_edge(1,2);
    g.add_edge(2,5);
    g.add_edge(3,4);
    g.add_edge(3,2);
    g.add_edge(3,0);
    
    cout << g;
    cout << "Now removing nodes" << endl;
    //Middle remove
    g.remove_edge(0,3);
    //Duplicate remove
    g.remove_edge(0,3);
    //Back Remove
    g.remove_edge(0,5);
    //Front Remove
    g.remove_edge(0,0);
    //Only edge
    g.remove_edge(4,1);
    //Test edge case
    g.remove_edge(4,1);
    cout << g;
    //Check existence
    cout << "Checking existance" << endl;
    cout << g.edge_exist(2,3) << endl;
    //Self edge
    cout << g.edge_exist(2,2)<< endl;;
    //Invalid input
    cout << g.edge_exist(2,19)<< endl;;
    cout << g.edge_exist(-2,3)<< endl;;
    cout << g.edge_exist(-2,-3)<< endl;;
    cout << g.edge_exist(19,-3)<< endl;;
    cout << g;

    cout << "Now checking paths" << endl;
    int current_size = g.get_current_size();
    bool visited[current_size]{false};

    cout << "2 -> 3:\t" << g.path_exists(2,3,visited) << endl;
    fill_n(visited, current_size, false);
    cout << "3 -> 1:\t" << g.path_exists(3,1,visited) << endl;
    fill_n(visited, current_size, false);
    cout << "5 -> 0:\t" << g.path_exists(5,0,visited) << endl;
    fill_n(visited, current_size, false);
    cout << "1 -> 4:\t" << g.path_exists(1,4,visited) << endl;
    fill_n(visited, current_size, false);

    cout << endl << "Now checking degrees of nodes" << endl;
    for (int i = 0; i < g.get_current_size(); i++) {
        cout << "For node " << i << " degree is " << g.get_degree(i) << endl;
    }
    //Copy constructor
    Graph g2 = g;
    //Increment five times
    cout << "Adding 5 nodes" << endl;
    for (int i = 0; i < 5; i++) {
        ++g2;
    }
    cout << g2;
    //Decrement to show removing points
    cout << "Removing 8 nodes" << endl;
    for (int i = 0; i < 8; i++) {
        --g2;
    }
    //Create 3rd weakly connected graph
    //
    Graph g3 = g2;
    g3.remove_edge(1,2);
    g3.remove_edge(0,1);
    //Empty graph
    Graph g4;
    for (int i = 0; i < 6; i++) {
        --g4;
    } 
    cout << "G:" << endl;
    cout << g;
    cout << "G2:" << endl;
    cout << g2;
    cout << "G3:" << endl;
    cout << g3;
    cout << "G4:" << endl;
    cout << g4;

    cout << "G Connectivity Type:"  << g.connectivity_type() << endl;
    cout << "G2 Connectivity Type:" << g2.connectivity_type() << endl;
    cout << "G3 Connectivity Type:" << g3.connectivity_type() << endl;
    cout << "G4 Connectivity Type:" << g4.connectivity_type() << endl << endl;

    //BFS
    vector<int> g_bfs = g.BFS(0);
    cout << "G BFS:";
    print_vec(g_bfs);
    cout << endl;

    vector<int> g2_bfs = g2.BFS(0);
    cout << "G2 BFS:";
    print_vec(g2_bfs);
    cout << endl;

    vector<int> g3_bfs = g3.BFS(0);
    cout << "G3 BFS:";
    print_vec(g3_bfs);
    cout << endl;

    vector<int> g4_bfs = g4.BFS(0);
    cout << "G4 BFS:";
    print_vec(g4_bfs);
    cout << endl;

    //DFS
    cout << endl << endl;
    vector<int> g_dfs = g.DFS(0);
    cout << "G DFS:";
    print_vec(g_dfs);
    cout << endl;

    vector<int> g2_dfs = g2.DFS(0);
    cout << "G2 DFS:";
    print_vec(g2_dfs);
    cout << endl;

    vector<int> g3_dfs = g3.DFS(0);
    cout << "G3 DFS:";
    print_vec(g3_dfs);
    cout << endl;

    vector<int> g4_dfs = g4.DFS(0);
    cout << "G4 DFS:";
    print_vec(g4_dfs);
    cout << endl;

    return 0;
}