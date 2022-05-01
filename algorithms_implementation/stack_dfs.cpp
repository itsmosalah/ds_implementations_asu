#include <iostream>
#include <vector>

using namespace std;

void stackDfs(int start, vector<vector<int>>&g){
    //g corresponds to graph of size n
    int n = int(g.size());

    //to indicate visited node
    vector<bool>visited(n, false);

    //to keep track of the index of the current child of a node (replaces for-loop in recursive dfs)
    vector<int>childIndex(n, 0);

    //stack of nodes (replaces call-stack in recursive dfs)
    stack<int>st;

    st.push(start); visited[start] = true;
    
    while(!st.empty()){
        int node = st.top();

        //while there are still children
        while(childIndex[node] < g[node].size()){
            //take the current child and move the index +1
            int child = g[node][childIndex[node]++];

            //if this child has not been visited before (in case of cycles and loops)
            if (!visited[child]){
                //marked as visited
                visited[child] = true;

                //pushed to the stack of nodes to be processed later
                st.push(child);

                //it is now the current node whose children will be checked in the next iteration
                node = child;
            }
            
        }
        //this node has no more children now, it is used and popped from stack
        cout << node << endl;
        st.pop();
    }
}

int main() {

    int n, m; cin >> n >> m;
    vector<vector<int>>g(n+1);
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    stackDfs(1, g);
  return 0;
}
