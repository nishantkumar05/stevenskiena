/*
 * (C) 2016 https://github.com/nulledpointer  
 *
 * You are free to modify and use this program as you deem fit. You can provide credit if you wish
 * by adding https://github.com/nulledpointer on top of this source code
 */

//-two coloring

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <queue>

//Graph:
//     8    -  3    --- 1 
//  /
//2     \       \
// \
//   0  -   6   -  4  ---- 5     9
//   | 
//   7


//Two coloring of graph is possible:
//     r    -  g    --- r 
//  /
//g     \       \
// \
//   r  -   g   -  r  ---- g     r
//   | 
//   g
//
//color array should print: 1, 1, 2, 2, 1, 2, 2, 2, 1, 1,


//Adjacency matrix representation of above graph
constexpr size_t inputVertices = 10;
const int adjmat[inputVertices][inputVertices] = 
{
{0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
{0, 0, 0, 1 ,0, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
{0, 1, 0, 0, 1, 0, 0, 0, 1, 0},
{0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

//Adjacency List representaion of above graph (Should print this)
//    GRAPH START
//    -----------
//    0 - 2 - 6 - 7 -
//    -----------
//    1 - 3 -
//    -----------
//    2 - 0 - 8 -
//    -----------
//    3 - 1 - 4 - 8 -
//    -----------
//    4 - 3 - 5 - 6 -
//    -----------
//    5 - 4 -
//    -----------
//    6 - 0 - 4 - 8 -
//    -----------
//    7 - 0 -
//    -----------
//    8 - 2 - 3 - 6 -
//    -----------
//    9 -

//BFS: starting with 0th node should print this
//    Starting breadth first search
//    0 -> 2 -> 6 -> 7 -> 8 -> 4 -> 3 -> 5 -> 1 -> 
//   : starting with 1 node should print this
//    1 -> 3 -> 4 -> 8 -> 5 -> 6 -> 2 -> 0 -> 7 -> 
//   : starting with 2 node should print this
//    2 -> 0 -> 8 -> 6 -> 7 -> 3 -> 4 -> 1 -> 5 -> 




struct node
{
  enum class state_t {undiscovered, discovered, processed};
  enum class color_t { unknown, red, green };

  //properties of graph that apply to individual nodes and edges of  graph goes here: e.g weight of edge, loop etc
  int id;
  int weight;
  node::state_t state;
  struct node* next;

  node(int id = 0) : id(id), weight(0), next(nullptr), state(node::state_t::undiscovered) {}
};

struct graph
{
  //properties of graph that apply to whole graph goes here: e.g directed, color
  bool directed;
  size_t  vertices;
  static const unsigned int i = 10;
  node *n[i];

  //other usefull data structure created along the way of bfs
  int parent[inputVertices];
  node::color_t colors[inputVertices];


  graph(const int a[][inputVertices], size_t nvertices)
  {
    vertices = nvertices;
    directed = false;
    for(auto&& t : n) {
      t = nullptr;
    }
   for(auto&& t : parent) {
     t = -1;
   }
    
    for(size_t r = 0; r < nvertices; r++) {
      n[r] = new node(r);
      node *current = n[r];
      for(size_t c = 0; c < nvertices; c++) {
        if(r == c) continue;
        if(a[r][c]) {
          node *tmp = new node(c);
          current->next = tmp;
          current = current->next;
        }
      }
    }
  }

  friend std::ostream& operator<<(std::ostream& out, graph& g)
  {
    out << "GRAPH START" << std::endl;
    for(size_t r = 0; r < g.vertices; r++) {
      out << "-----------" << std::endl;
      node *current = g.n[r];
      while(current) {
        out << current->id << " - "; 
        current = current->next;
      }
      out << std::endl;
    }
    return out;
  }

  void findPath(int x, int y)
  {
    bfs(x);

    std::cout << "Finding path: " << y << " -> ";
    for(int i = y; (i != x) && (i >= 0) && (parent[i] != -1); i = parent[i]) {
      int p = parent[i];
      std::cout << p << " -> ";
      if(p == x) {
        std::cout << "Path found!!" << std::endl;
        return;
      }
    }
    std::cout << "Path not found!!" << std::endl;
  }

  /*Tells whether graph can be colored using only two colors or not.
   *Also tells with what color.
   */
  void twoColor()
  {
    for(auto&& t : colors) {
      t = node::color_t::unknown;
    }

    for(auto&& t : n) {
      if( t->state == node::state_t::undiscovered ) {
        bfs(t->id);
        colors[t->id] = node::color_t::red;
      }
    }

    std::cout << "print color=>";
    for(auto&& t : colors) {
      std::cout << static_cast<int>(t) << ", ";
    }
    std::cout << std::endl;
  }

  node::color_t complementColor(node::color_t c)
  {
    if(c == node::color_t::red) return node::color_t::green;
    return node::color_t::red;
  }

  void bfs(const size_t startingNode)
  {
    unsigned int nedges = 0;

    if(startingNode >= vertices) {
      std::cerr << "starting node (" << startingNode << ") out of bounds"  <<std::endl;
      return;
    }
    parent[startingNode] = -1;
    colors[startingNode] = node::color_t::red;

    std::queue<node*> q;
    q.push(n[startingNode]);

    std::cout << "Starting breadth first search with node =" << startingNode <<std::endl;

    n[n[startingNode]->id]->state = node::state_t::discovered;
    std::cout << n[startingNode]->id << " -> ";


    while(q.size()) {
      node *tmp = q.front();
      q.pop();

      for(node *current = n[tmp->id]->next; current; current=current->next) {
        if(n[current->id]->state != node::state_t::processed) {
          nedges++;
          if(colors[current->id] == colors[tmp->id]) {
            std::cout << "Not bipartite!" << std::endl;
          }
        }
        if(n[current->id]->state == node::state_t::undiscovered) {
          n[current->id]->state = node::state_t::discovered;
          parent[current->id] = tmp->id;
          colors[current->id] = complementColor(colors[tmp->id]);
          std::cout << current->id << " -> ";
          q.push(current);
        }
      }
      n[tmp->id]->state = node::state_t::processed;
    }
    std::cout << std::endl << "Finished breadth first search" <<std::endl;
    std::cout << std::endl << "Total number of edges =" << nedges <<std::endl;
    std::cout << std::endl << "Parents =>";
    for(auto&& t : parent) {
      std::cout << t << " ,";
    } 
    std::cout << std::endl;
  }

};

int main(void)
{
  try{
    size_t startingNode = 1;
    graph g(adjmat, inputVertices);
    std::cout << g;
    //g.bfs(startingNode);
    //g.findPath(1,9);
    g.twoColor();
  }catch(std::exception r){
    std::cerr << "exception occured:" << r.what() << std::endl;
  }
  return 0;
}
