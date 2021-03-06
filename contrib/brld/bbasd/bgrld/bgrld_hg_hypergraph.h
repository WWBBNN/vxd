// This is lemsvxlsrc/brcv/shp/dbhg/bgrld_hg_hypergraph.h
//:
// \file
// author: Ming-Ching Chang
// date:   Apr 04, 2005

#ifndef dbhg_hypergraph_h_
#define dbhg_hypergraph_h_

#include <vcl_map.h>
#include <vcl_utility.h>

#include <bgrld/bgrld_hg_graph.h>
#include <bgrld/bgrld_hg_hyperedge.h>

class bgrld_hg_hypergraph : public bgrld_hg_graph
{
protected:
  vcl_map<int, bgrld_hg_hyperedge*> hyperedges_;

public:
  //: ====== Hypergraph query functions ======
  vcl_map<int, bgrld_hg_hyperedge*>& hyperedges() {
    return hyperedges_;
  }
  bgrld_hg_hyperedge* hyperedges (const int i) {
    vcl_map<int, bgrld_hg_hyperedge*>::iterator H_it = hyperedges_.find (i);
    if (H_it == hyperedges_.end())
      return NULL;
    
    bgrld_hg_hyperedge* hyperedge = (*H_it).second;
    return hyperedge;
  }

  //: ===== Internal Low-level Graph operation (without handling connectivity) =====
  virtual bool _internal_del_vertex (bgrld_hg_vertex* vertex);
  virtual bool _internal_del_edge (bgrld_hg_edge* edge);

  void _internal_add_hyperedge (bgrld_hg_hyperedge* hyperedge);
  bool _internal_del_hyperedge (bgrld_hg_hyperedge* hyperedge);

  //: ===== Internal Mid-level Graph operation (handling connectivity) =====
  void _internal_connect_hyperedge_edge (bgrld_hg_hyperedge* hyperedge, bgrld_hg_edge* edge) {
    //: unordered edge list
    hyperedge->connect_edge (edge);
    edge->connect_hyperedge (hyperedge);
  }
  void _internal_disconnect_hyperedge_edge (bgrld_hg_hyperedge* hyperedge, bgrld_hg_edge* edge) {
    //: unordered edge list
    hyperedge->disconnect_edge (edge);
    edge->disconnect_hyperedge (hyperedge);
  }

  void _internal_connect_hyperedge_vertex (bgrld_hg_hyperedge* hyperedge, bgrld_hg_vertex* vertex) {
    hyperedge->connect_vertex (vertex);
    vertex->connect_hyperedge (hyperedge);
  }
  void _internal_disconnect_hyperedge_vertex (bgrld_hg_hyperedge* hyperedge, bgrld_hg_vertex* vertex) {
    hyperedge->disconnect_vertex (vertex);
    vertex->disconnect_hyperedge (hyperedge);
  }

  //: ===== High-level Graph operation for insert/remove/replace element =====
  virtual bool remove_vertex (bgrld_hg_vertex* vertex);
  ///virtual bool remove_vertex (int id);
  virtual bool remove_edge (bgrld_hg_edge* edge);
  // virtual bool remove_edge (int id);
  virtual bool remove_hyperedge (bgrld_hg_hyperedge* hyperedge);
  ///virtual bool remove_hyperedge (int id);

  //: ===== High-level Graph operation that user should use =====
  //  These operations are always topologically consistent,
  //  i.e. the resulting graph is always a geometric graph.
  //  (You will not have an edge that has no end nodes.)  
  virtual bool topo_remove_vertex (bgrld_hg_vertex* vertex);
  ///virtual bool topo_remove_vertex (int id);
  virtual bool topo_remove_edge (bgrld_hg_edge* edge);
  ///virtual bool topo_remove_edge (int id);
  virtual bool topo_remove_hyperedge (bgrld_hg_hyperedge* hyperedge);
  ///virtual bool topo_remove_hyperedge (int id);

  bgrld_hg_hypergraph () :
    bgrld_hg_graph ()
  {
  }
  virtual ~bgrld_hg_hypergraph ()
  {
  }
};

#endif
