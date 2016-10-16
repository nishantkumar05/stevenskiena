/*
 * (C) 2016 https://github.com/nulledpointer  
 *
 * You are free to modify and use this program as you deem fit. You can provide credit if you wish
 * by adding https://github.com/nulledpointer on top of this source code
 */


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
//   0  -   6   -  4  ---- 5
//   | 
//   7

//Adjacency matrix representation of above graph
constexpr size_t inputVertices = 9;
const int adjmat[inputVertices][inputVertices] = 
{
{0, 0, 1, 0, 0, 0, 1, 1, 0},
{0, 0, 0, 1 ,0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 1},
{0, 1, 0, 0, 1, 0, 0, 0, 1},
{0, 0, 0, 1, 0, 1, 1, 0, 0},
{0, 0, 0, 0, 1, 0, 0, 0, 0},
{1, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 0, 0, 1, 0, 0},
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

//BFS: starting with 0th node should print this
//    Starting breadth first search
//    0 -> 2 -> 6 -> 7 -> 8 -> 4 -> 3 -> 5 -> 1 -> 
//   : starting with 1 node should print this
//    1 -> 3 -> 4 -> 8 -> 5 -> 6 -> 2 -> 0 -> 7 -> 




struct node
{
  enum class state_t {undiscovered, discovered, processed};

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


  graph(const int a[][inputVertices], size_t nvertices)
  {
    vertices = nvertices;
    directed = false;
    for(auto&& t : n)
    {
      t = nullptr;
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

  void bfs(const graph& g, const size_t starting_node)
  {
    if(starting_node >= g.vertices) {
      std::cerr << "starting node (" << starting_node << ") out of bounds"  <<std::endl;
      return;
    }

    std::queue<node*> q;
    q.push(g.n[starting_node]);

    std::cout << "Starting breadth first search" <<std::endl;

    while(q.size()) {
      node *tmp = q.front();
      q.pop();
      //std::cout << "starting with:" << tmp->id <<std::endl;

      for(node *current = g.n[tmp->id]; current; current=current->next) {
        if(g.n[current->id]->state == node::state_t::processed) {
          //std::cout << "already processed node:" << current->id << ",  " <<std::endl;
        } else if(g.n[current->id]->state == node::state_t::discovered) {
          //std::cout << "already discovered node:" << current->id << ",  " <<std::endl;
        } else {
          g.n[current->id]->state = node::state_t::discovered;
          std::cout << current->id << " -> ";
          q.push(current);
        }
      }
      g.n[tmp->id]->state = node::state_t::processed;
    }
    std::cout << std::endl << "Finished breadth first search" <<std::endl;
  }

};

int main(void)
{
  try{
    graph g(adjmat, inputVertices);
    std::cout << g;
    g.bfs(g, 1);
  }catch(std::exception r){
    std::cerr << "exception occured:" << r.what() << std::endl;
  }
  return 0;
}
