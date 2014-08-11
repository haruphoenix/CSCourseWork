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

class Node
{
private:
   unsigned int mNumber;

public:
   Node(unsigned int inNumber)
   {
      mNumber = inNumber;
   }

   unsigned int getNumber() const { return mNumber; }
};

ostream& operator<<(ostream& os, const Node& n)
{
   os << "Node[" << n.getNumber() << "]";
   return os;
}

class Edge
{
private:
   unsigned int mFirst;
   unsigned int mSecond;

public:
   Edge(unsigned int first, unsigned int second)
   {
      mFirst = first;
      mSecond = second;
   }

   unsigned int first() const { return mFirst; }
   unsigned int second() const { return mSecond; }
};

ostream& operator<<(ostream& os, const Edge& e)
{
   os << "Edge[" << e.first() << ", " << e.second() << "]";
   return os;
}

class Graph
{
private:
   set<uint> mVertices;
   vector<Node> mNodes;
   vector<Edge> mEdges;
   map<uint, vector<Edge> > mAdjacencies;

public:
   const set<uint>& vertices() const { return mVertices; }

   const vector<Node>& nodes() const { return mNodes; }

   const vector<Edge>& edges() const { return mEdges; }

   Graph(const char* filename)
   {
      readFrom(filename);
   }

   virtual ~Graph()
   {
   }

   void readFrom(const char* filename)
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

   void addEdge(unsigned int v1, unsigned int v2)
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

   void addEdge(const Edge& e)
   {
      mEdges.push_back(e);
   }

   void addVertices(const Edge& e)
   {
      mVertices.insert(e.first());
      mVertices.insert(e.second());
   }

   void addNodes()
   {
      addNodes(mVertices);
   }

   void addNodes(set<uint> vertices)
   {
      for (set<uint>::const_iterator it = vertices.begin();
           it != vertices.end(); it++)
      {
         unsigned int v = *it;
         mNodes.push_back(Node(v));
      }
   }

   void addVertices(Graph& g)
   {
      addVertices(g.vertices());
   }

   void addVertices(set<uint> vertices)
   {
      for (set<uint>::const_iterator it = vertices.begin();
           it != vertices.end(); it++)
      {
         mVertices.insert(*it);
      }
   }

   bool contains(unsigned int v) const
   {
      // see if v is in the set of vertices
      return (mVertices.find(v) != mVertices.end());
   }
   
   bool containsEdge(unsigned int v1, unsigned int v2)
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

   void checkCliqueOrAntiClique(bool anti, vector<int>& vertices)
   {
      // TODO: flesh out this function. Use good modularity, that is,
      // write some appropriate helper function(s) that this one can call.
   }
};

ostream& operator<<(ostream& os, const Graph& g)
{
   os << "Graph[\n";

   vector<Edge> edges = g.edges();

   os << edges.size() << " edges:";
   for (vector<Edge>::const_iterator it = edges.begin();
        it != edges.end(); it++)
   {
      os << "\n\t" << *it;
   }

   vector<Node> nodes = g.nodes();
   int numNodes = nodes.size();

   os << "\n" << numNodes << " nodes:";

   for (vector<Node>::const_iterator it = nodes.begin();
        it != nodes.end(); it++)
   {
      os << "\n\t" << *it;
   }

   os << "\n]";

   return os;
}

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
