/*************************************************************************
 * Graphs Exploration
 *
 * Check for Cliques and Anti-Cliques.
 *
 * Stub code provided for the pressed-for-time student...
 *
 * Modify to suit -- except for main!
 *
 * NOTE: this code is highly UNcommented -- this is deliberate.
 *
 *************************************************************************/
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;

typedef unsigned int uint;

/*************************************************************************
*
*************************************************************************/
class Node
{
   public:
      Node(uint inNumber)
      {
         mNumber = inNumber;
      }
      uint getNumber() const { return mNumber; }

   private:
      uint mNumber;
};

ostream& operator << (ostream& out, const Node& n)
{
   out << "Node[" << n.getNumber() << "]";
   return out;
}

/*************************************************************************
*
*************************************************************************/
class Edge
{
   public:
      Edge(unsigned int first, unsigned int second)
      {
         mFirst = first;
         mSecond = second;
      }
      unsigned int first() const { return mFirst; }
      unsigned int second() const { return mSecond; }

   private:
      unsigned int mFirst;
      unsigned int mSecond;
};

ostream& operator<<(ostream& os, const Edge& e);

/*************************************************************************
*
*************************************************************************/
class Graph
{
   public:
      const set<uint>& vertices() const;
      const vector<Node>& nodes() const;
      const vector<Edge>& edges() const;
      Graph(const char* filename);
      virtual ~Graph();
      void readFrom(const char* filename);
      void addEdge(unsigned int v1, unsigned int v2);
      void addEdge(const Edge& e);
      void addVertices(const Edge& e);
      void addNodes();
      void addNodes(set<uint> vertices);
      void addVertices(Graph& g);
      void addVertices(set<uint> vertices);
      bool contains(unsigned int v) const;
      bool containsEdge(unsigned int v1, unsigned int v2);
      void checkCliqueOrAntiClique(bool anti, vector<int>& vertices);
   
   private:
      set<uint> mVertices;
      vector<Node> mNodes;
      vector<Edge> mEdges;
      map<uint, vector<Edge> > mAdjacencies;
};


/*************************************************************************
* DO NOT MODIFY IN ANY WAY!!
*************************************************************************/
int main(int argc, char* argv[])
{
   if (argc < 2)
   {
      cerr << "Usage: " << argv[0] << " <input_file> [space-separated vertex list]";
      return -1;
   }
   else
   {
      const char* filename = argv[1];
      vector<int> vertices;
   
      bool anti = false;
      bool gotWhich = false;

      for (int i = 2; i < argc; i++)
      {
         if (strcmp(argv[i], "anti-clique") == 0)
         {
            anti = true;
            gotWhich = true;
         }
         else if (strcmp(argv[i], "clique") == 0)
         {
            anti = false;
            gotWhich = true;
         }
         else if (gotWhich)
         {
            int n = atoi(argv[i]);
            vertices.push_back(n);
         }
      }

      Graph g(filename);

      cout << "The graph specified in " << filename << endl;

      g.checkCliqueOrAntiClique(anti, vertices);

      return 0;
   }
}



Edge::Edge(uint first, uint second)
{
   mFirst = first;
   mSecond = second;
}

uint Edge::first()  const { return mFirst; }
uint Edge::second() const { return mSecond; }


ostream& operator<<(ostream& os, const Edge& e)
{
   os << "Edge[" << e.first() << ", " << e.second() << "]";
   return os;
}

const set<uint>& Graph::vertices() const { return mVertices; }
const vector<Node>& Graph::nodes() const { return mNodes; }
const vector<Edge>& Graph::edges() const { return mEdges; }

Graph::Graph(const char* filename)
{
   readFrom(filename);
}

Graph::~Graph()
{
}

void Graph::readFrom(const char* filename)
{
   unsigned int v1;
   unsigned int v2;
   ifstream file(filename, ios_base::in);
   if (file)
   {
      // cout << "reading from " << filename << ":\n";
      while (true)
      {
         file >> v1 >> v2;
         if (file.eof() || file.fail())
         {
            break;
         }
         addEdge(v1, v2);
      }
      file.close();
      addNodes();
   }
}

void Graph::addEdge(unsigned int v1, unsigned int v2)
{
   Edge e(v1, v2);
   addEdge(e);
   addVertices(e);

   if (mAdjacencies.find(v1) != mAdjacencies.end())
   {
       vector<Edge> * adj = &mAdjacencies.find(v1)->second;
       adj->push_back(e);
   }
   else
   {
       vector<Edge> adj; adj.push_back(e);
       mAdjacencies.insert(pair<uint, vector<Edge> >(v1, adj));
   }
   if (mAdjacencies.find(v2) != mAdjacencies.end())
   {
       vector<Edge> * adj = &mAdjacencies.find(v2)->second;
       adj->push_back(e);
   }
   else
   {
       vector<Edge> adj; adj.push_back(e);
       mAdjacencies.insert(pair<uint, vector<Edge> >(v2, adj));
   }
}

void Graph::addEdge(const Edge& e)
{
   mEdges.push_back(e);
}

void Graph::addVertices(const Edge& e)
{
   mVertices.insert(e.first());
   mVertices.insert(e.second());
}

void Graph::addNodes()
{
   addNodes(mVertices);
}

void Graph::addNodes(set<uint> vertices)
{
   for (set<uint>::const_iterator it = vertices.begin();
        it != vertices.end(); it++)
   {
      unsigned int v = *it;
      mNodes.push_back(Node(v));
   }
}

void Graph::addVertices(Graph& g)
{
   addVertices(g.vertices());
}

void Graph::addVertices(set<uint> vertices)
{
   for (set<uint>::const_iterator it = vertices.begin();
        it != vertices.end(); it++)
   {
      mVertices.insert(*it);
   }
}

bool Graph::contains(unsigned int v) const
{
   // see if v is in the set of vertices
   return (mVertices.find(v) != mVertices.end());
}
   
bool Graph::containsEdge(unsigned int v1, unsigned int v2)
{
    for (vector<Edge>::const_iterator it = mEdges.begin();
         it != mEdges.end(); it++)
    {
        Edge e = *it;
        if ((e.first() == v1 && e.second() == v2) ||
            (e.first() == v2 && e.second() == v1))
        {
            return true;
        }
    }
    return false;
 }

void Graph::checkCliqueOrAntiClique(bool anti, vector<int>& vertices)
{
   // TODO: flesh out this function. Use good modularity, that is,
   // write some appropriate helper function(s) that this one can call.
}

ostream& operator << (ostream& out, const Graph& g)
{
   out << "Graph[\n";

   vector<Edge> edges = g.edges();

   out << edges.size() << " edges:";
   for (vector<Edge>::const_iterator it = edges.begin();
        it != edges.end(); it++)
   {
      out << "\n\t" << *it;
   }

   vector<Node> nodes = g.nodes();
   int numNodes = nodes.size();

   out << "\n" << numNodes << " nodes:";

   for (vector<Node>::const_iterator it = nodes.begin();
        it != nodes.end(); it++)
   {
      out << "\n\t" << *it;
   }

   out << "\n]";

   return out;
}
