// This is lemsvxlsrc/basic/dbgrl/dbgrl_hg_graph.h
//:
// \file
// author: Ming-Ching Chang
// date:   Apr 04, 2005

#ifndef dbgrl_hg_graph_h_
#define dbgrl_hg_graph_h_

#include <vcl_map.h>
#include <vcl_utility.h>

#include <dbgrl/dbgrl_hg_vertex.h>
#include <dbgrl/dbgrl_hg_edge.h>

class dbgrl_hg_graph 
{
protected:
  vcl_map<int, dbgrl_hg_vertex*>    vertices_;
  vcl_map<int, dbgrl_hg_edge*>      edges_;

public:
  //: ====== Graph query functions ======
  vcl_map<int, dbgrl_hg_vertex*>& vertices() {
    return vertices_;
  }
  dbgrl_hg_vertex* vertices (const int i) {
    //: !! this query will insert a NULL object to the map if key not found !!
    //  return scaffold_vertices_[i];
    //  instead, use find to avoid inserting NULL objects
    vcl_map<int, dbgrl_hg_vertex*>::iterator V_it = vertices_.find (i);
    if (V_it == vertices_.end())
      return NULL;
    
    dbgrl_hg_vertex* vertex = (*V_it).second;
    return vertex;
  }

  vcl_map<int, dbgrl_hg_edge*>& edges() {
    return edges_;
  }
  dbgrl_hg_edge* edges (const int i) {
    vcl_map<int, dbgrl_hg_edge*>::iterator E_it = edges_.find (i);
    if (E_it == edges_.end())
      return NULL;
    
    dbgrl_hg_edge* edge = (*E_it).second;
    return edge;
  }

  //: ===== Internal Low-level Graph operation (without handling connectivity) =====
  virtual void _internal_add_vertex (dbgrl_hg_vertex* vertex);
  virtual bool _internal_del_vertex (dbgrl_hg_vertex* vertex);
  virtual void _internal_add_edge (dbgrl_hg_edge* edge);
  virtual bool _internal_del_edge (dbgrl_hg_edge* edge);

  //: ===== Internal Mid-level Graph operation (handling connectivity) =====
  //: vidx==0: starting vertex, vidx==1: ending vertex, 
  void _internal_connect_edge_vertex (dbgrl_hg_edge* edge, int vidx, dbgrl_hg_vertex* vertex) {
    assert (vidx==0 || vidx==1);
    edge->connect_vertex (vidx, vertex);
    vertex->connect_edge (edge);
  }
  bool _internal_disconnect_edge_vertex (dbgrl_hg_edge* edge, dbgrl_hg_vertex* vertex) {
    if (edge->connecting_s_vertex() == vertex) {
      edge->disconnect_vertex (0);
      vertex->disconnect_edge (edge);
      return true;
    }
    else if (edge->connecting_e_vertex() == vertex) {
      edge->disconnect_vertex (1);
      vertex->disconnect_edge (edge);
      return true;
    }
    assert (0);
    return false;
  }

  //: ===== High-level Graph operation for insert/remove/replace element =====
  virtual bool remove_vertex (dbgrl_hg_vertex* vertex);
  virtual bool remove_vertex (int id);
  virtual bool remove_edge (dbgrl_hg_edge* edge);
  virtual bool remove_edge (int id);

  //: ===== High-level Graph operation that user should use =====
  //  These operations are always topologically consistent,
  //  i.e. the resulting graph is always a geometric graph.
  //  (You will not have an edge that has no end nodes.)
  virtual bool topo_remove_vertex (dbgrl_hg_vertex* vertex);
  virtual bool topo_remove_vertex (int id);
  virtual bool topo_remove_edge (dbgrl_hg_edge* edge);
  virtual bool topo_remove_edge (int id);

  dbgrl_hg_graph () 
  {
  }

  virtual ~dbgrl_hg_graph() 
  {
    vcl_map<int, dbgrl_hg_edge*>::iterator E_it = edges_.begin();
    for (; E_it != edges_.end(); E_it++) {
      dbgrl_hg_edge* edge = (*E_it).second;
      delete edge;
    }
    edges_.clear ();

    vcl_map<int, dbgrl_hg_vertex*>::iterator V_it = vertices_.begin();
    for (; V_it != vertices_.end(); V_it++) {
      dbgrl_hg_vertex* vertex = (*V_it).second;
      delete vertex;
    }
    vertices_.clear ();
  }
};

#endif
