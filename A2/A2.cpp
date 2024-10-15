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
        //Added optional size paramter to make ++ overload easier
        Graph(Graph& g, int in_size=6) {
            current_size=in_size;
            arr = new Node*[in_size];
            for (int i = 0; i < current_size; i++) {
                arr[i] = nullptr;
            }
            //Only bound to g.current size in case new nodes are to be added
            cout << "Starting copies for copy constructor" << endl;
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
            cout << "Graph destructor called" << endl;
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

        void clear_node(int nd) {
            cout << "Clearing node " << nd << endl;
            Node * current = arr[nd];
            //Skip assuming nothing to clear
            if (current == nullptr) {
                cout << "Empty list nothing to clear for " << nd << endl;
                return;
            }
            while (current != nullptr) {
                Node *after = current->next;
                current->next = nullptr;
                current->prev=nullptr;
                delete current;
                current = after;
            }
        }

        int get_degree(int nd) {
            if (nd < 0 || nd > current_size) {

            }
            Node * current = arr[nd];
            int deg = 0;
            if (current->val==-1) {
                return deg;
            }
            while (current != nullptr) {
                deg++;
                current = current->next;
            }
            return deg;
        }


        string print_graph() const{
            string ret = "\n";
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
                cout << "Start and goal are the same " << current << " -> " << goal << endl;
                return true;
            }

            if (arr[current] == nullptr) {
                cout << "Node " << current << " is empty" << endl;
                return false;
            }            

            Node * temp = arr[current];
            while (temp != nullptr) {
                if (temp->val == goal) {
                    cout << "Found goal " << current << " -> " << goal << endl;
                    return true;
                }
                if (temp->val != current) {
                    bool temp_check;
                    if (!visited[temp->val]) {
                        cout << "Moving from " << current << " -> " << temp->val << endl;
                        temp_check = path_exists(temp->val, goal, visited);

                    }
                    if (temp_check == true) {
                        cout << "Path exists " << current << " -> " << temp->val << endl;
                        return true;
                    }
                }
                temp = temp->next;
            }
            cout << "No path between " << current << " -> " << goal << endl;
            return false;
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
            if (current == nullptr) {

            }
            while (current != nullptr) {
                if (current->val == end) {
                    //Last element in list
                    if ( (current->next == nullptr) && (current->prev==nullptr) ) {
                        cout << "First and only element so deleting edge: "<< start <<", " << end << " at end of list" << endl; ;
                        arr[start]=nullptr;
                        delete current;
                    }
                    //Removing from end
                    else if (current->next==nullptr) {
                        cout << "Removing: " << start <<", " << end << " at end of list" << endl;
                        Node * last = current->prev;
                        last->next = nullptr;
    
                        current->prev = nullptr;
                        current->next=nullptr;
                        delete current;
                    }
                    //Removing from start
                    else if (current->prev == nullptr) {
                        cout << "Removing: " << start <<", " << end << " at start of list" << endl;
                        current->next->prev=nullptr;
                        arr[start]=current->next;

                        current->next=nullptr;
                        current->prev=nullptr;
                        delete current;
                    }
                    //Removing from middle
                    else {
                        cout << "Removing " << start <<", " << end << " in middle of list" << endl;
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
            //cout << "In add edge: \t" << start << ", " << end << endl;
            Node * current = arr[start];
            Node * to_add = new Node(nullptr, nullptr, end);
            //cout << "Passed first add initilzation" << endl;
            bool middle = false;
            bool end_list = false;

            //If at start of list just swap value of end for first connection
            //cout << "About to start ifs " << endl;
            //cout << "Checking current nullptr   " << (current==nullptr) << endl;
            //cout << current << endl;
            if (current==nullptr) {
                cout << "First edge to add: \t" << start << ", " << end << endl;
                arr[start]=to_add;
                return;
            }
            //Also check if an existing start point are you greater
            else if (end < current->val) {
                cout << "Added new smallest first edge: \t"<< start << ", " << end << endl;
                to_add->next=current;
                current->prev=to_add;
                arr[start]=to_add;
                return;
            }


            //cout << "About to enter loop" << endl;
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
                cout << "Adding edge in middle: \t " << start << ", " << end << endl;
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
                cout << "Adding edge to end: \t" << start << ", " << end << endl;
                current->next = to_add;
                to_add->prev=current;
                to_add->next=nullptr;
            }             
        }


        int connectivity_type() {
            //Check if all paths exist
            bool connections[current_size][current_size];
            for (int i = 0; i < current_size; i++) {
                for (int j = 0; j < current_size; j++) {
                    bool visisted[current_size] = {false};
                    connections[i][j] = path_exists(i,j,visisted);
                }
            }
            cout << "\t";
            for (int i = 0; i < current_size; i++) {
                cout << i << "\t";
            }
            cout << endl;

            for (int i = 0; i < current_size; i++) {
                cout << i << ":\t";
                for (int j = 0; j < current_size; j++) {
                    cout << connections[i][j] << "\t"; 
                }
                cout << endl << endl;
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
                cout << "All nodes have path between them, hense, strongly connected" << endl;
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
                cout << "At least one path exists between all pairs, hense, unilaterally connected" << endl;
                return  2;
            }

            cout << "Neither strongly nor unilaterally connected, test for weakly" << endl;
            return 0;
        }

        void bfs(int current, bool* visited, vector<int> &order) {
            visited[current]=true;
            order.push_back(current);
            Node * temp = arr[current];
            while(temp!= nullptr) {
                if (!visited[temp->val]) {
                    bfs(temp->val, visited, order);
                }
                temp = temp->next;
            }
        }


        //The instructionson brightspace indicated a list needed to be returned but didn't
        //specify what strucutre or container, so for the sake of ease I am using a vector.
        vector<int> BFS(int start) {
            vector<int> order;
            if (start < 0 || start > current_size) {
                cout << "Invalid start node, returning empty list";
                return order;
            }
            bool visited[current_size] {false};
            bfs(start, visited, order);
            return order;
        }

        vector <int> DFS(int start) {
            vector<int> order;
            deque<int> queue;
            queue.push_back(start);
            if (start < 0 || start > current_size) {
                cout << "Invalid start node, returning empty list";
                return order;
            }
            bool visited[current_size] {false};
            dfs(visited, order, queue);
            return order;
        }

        void dfs(bool* visited, vector<int> &order, deque<int> queue) {
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

};

ostream& operator<<(ostream& os, const Graph& g) {
    os << g.print_graph() << endl;
    return os;
}
int main() {
    cout << "Started" << endl;
    Graph g;
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(0, 3);
    g.add_edge(0, 4);
    g.add_edge(0, 5);
    g.add_edge(2,5);
    g.add_edge(3,4);
    g.add_edge(1, 4);
    g.add_edge(1, 3);
    g.add_edge(4, 3);
    g.add_edge(4, 2);
    g.add_edge(4, 4);
    g.add_edge(4,0);
    g.add_edge(4, 1);
    //g.add_edge(5,2);
    cout << g;
    g.remove_edge(0,3);
    g.remove_edge(0,1);
    g.add_edge(0,0);
    g.remove_edge(4,3);
    cout << g;
    g.remove_edge(0,2);
    cout << g;
    int x = g.connectivity_type();
    cout << endl << "Connection is " << x << endl;
    cout << g;
    bool visisted[g.get_current_size()] = {false};
    g.path_exists(3,0,visisted);
    cout << endl << endl;
    vector<int> ret = g.BFS(0);
    cout << "DFS complete: ";
    for (int i = 0; i < ret.size();i++) {
        cout << ret[i] << ", ";
    }
    cout << endl << endl;
    vector<int> ret2 = g.DFS(0);
    cout << "BFS complete: ";
    for (int i = 0; i < ret2.size();i++) {
        cout << ret2[i] << ", ";
    }
    cout << endl << endl;
    cout <<"testing graph print: " << g;
    Graph g2(g, 8);
    cout << "G2 test with extra nodes " << g2;
    return 0;
}