#include <iostream>
#include <vector>
#include <string>
#include <exception>

//Graph:
//     2    -  3 
//  /
//0     \       \
// \
//   1     5   -  4 


//Adjacency List:
//Should print this
//   GRAPH START
//   -----------
//   0 - 1 - 2 - 
//   -----------
//   1 - 0 - 
//   -----------
//   2 - 0 - 3 - 5 - 
//   -----------
//   3 - 2 - 4 - 
//   -----------
//   4 - 3 - 5 - 
//   -----------
//   5 - 2 - 4 - 


const int adjmat[6][6] = 
{
{0, 1, 1, 0, 0, 0},
{1, 0, 0, 0 ,0, 0},
{1, 0, 0, 1, 0, 1},
{0, 0, 1, 0, 1, 0},
{0, 0, 0, 1, 0, 1},
{0, 0, 1, 0, 1, 0},
};

struct node
{
  int y;
  int weight;
  struct node* next;

  node(int id = 0)
  {
     y = id;
     weight = 0;
     next = nullptr;
  }
};

struct graph
{
  //properties of graph here: e.g directed, color, weight of edge etc
  bool directed;
  int  weight;
  size_t  vertices;
  static const unsigned int i = 10;
  node *n[i];


  graph(const int a[][6], size_t nvertices)
  {
    vertices = nvertices;
    directed = false;
    weight = 0;
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
        out << current->y << " - "; 
        current = current->next;
      }
      out << std::endl;
    }
    return out;
  }
};

//std::ostream& operator<<(std::ostream& out, graph& g)
//{
//  out << "GRAPH START" << std::endl;
//  for(size_t r = 0; r < g.vertices; r++) {
//    out << "-----------" << std::endl;
//    node *current = g.n[r];
//    while(current) {
//      out << current->y << " - "; 
//      current = current->next;
//    }
//    out << std::endl;
//  }
//  return out;
//}


int main(void)
{
  try{
    graph g(adjmat, 6);
    std::cout << g;
  }catch(std::exception r){
    std::cerr << "exception occured:" << r.what() << std::endl;
  }
  return 0;
}
