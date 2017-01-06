// This is lemsvxlsrc/brcv/shp/dbhg/dbgrl_hg_hypergraph.cxx
//:
// \file
// author: Ming-Ching Chang
// date:   Apr 04, 2005

#include <dbgrl/dbgrl_hg_hypergraph.h>


////////////////////////////////////////////////////////////////////
//: ===== Internal Low-level Graph operation (without handling connectivity) =====
bool dbgrl_hg_hypergraph::_internal_del_vertex (dbgrl_hg_vertex* vertex)
{
  assert (vertex->connecting_hyperedges().size() == 0);
  return dbgrl_hg_graph::_internal_del_vertex (vertex);
}

bool dbgrl_hg_hypergraph::_internal_del_edge (dbgrl_hg_edge* edge)
{
  assert (edge->connecting_hyperedges().size() == 0);
  return dbgrl_hg_graph::_internal_del_edge (edge);
}

void dbgrl_hg_hypergraph::_internal_add_hyperedge (dbgrl_hg_hyperedge* hyperedge) 
{
  ///assert (hyperedge->id() > 0);
  ///hyperedges_.insert (vcl_pair<int, dbgrl_hg_hyperedge*> (hyperedge->id(), hyperedge));
}

bool dbgrl_hg_hypergraph::_internal_del_hyperedge (dbgrl_hg_hyperedge* hyperedge) 
{
  assert (hyperedge->connecting_edges().size() == 0);
  assert (hyperedge->connecting_vertices().size() == 0);

  ///int n_removed = hyperedges_.erase (hyperedge->id());
  ///return (n_removed == 1);
  return true;
}

////////////////////////////////////////////////////////////////////
//: ===== High-level Graph operation (handling connectivity) =====
bool dbgrl_hg_hypergraph::remove_vertex (dbgrl_hg_vertex* vertex)
{
  vcl_vector<dbgrl_hg_edge*>::iterator E_it = vertex->connecting_edges().begin();
  while (E_it != vertex->connecting_edges().end()) {
    dbgrl_hg_edge* edge = (*E_it);
    _internal_disconnect_edge_vertex (edge, vertex);
  }

  vcl_vector<dbgrl_hg_hyperedge*>::iterator H_it = vertex->connecting_hyperedges().begin();
  while (H_it != vertex->connecting_hyperedges().end()) {
    dbgrl_hg_hyperedge* hyperedge = (*H_it);
    _internal_disconnect_hyperedge_vertex (hyperedge, vertex);
  }

  return _internal_del_vertex (vertex);
}

/*bool dbgrl_hg_hypergraph::remove_vertex (int id)
{
  dbgrl_hg_vertex* vertex = vertices (id);
  if (vertex)
    return remove_vertex (vertex);
  else
    return false;
}*/

bool dbgrl_hg_hypergraph::remove_edge (dbgrl_hg_edge* edge)
{
  dbgrl_hg_vertex* sv = edge->connecting_s_vertex();
  dbgrl_hg_vertex* ev = edge->connecting_e_vertex();

  if (sv)
    _internal_disconnect_edge_vertex (edge, sv);
  if (ev)
    _internal_disconnect_edge_vertex (edge, ev);

  for (unsigned int i=0; i<edge->connecting_hyperedges().size(); i++) {
    dbgrl_hg_hyperedge* hyperedge = edge->connecting_hyperedges(i);
    _internal_disconnect_hyperedge_edge (hyperedge, edge);
  }

  return _internal_del_edge (edge);
}

/*bool dbgrl_hg_hypergraph::remove_edge (int id)
{
  dbgrl_hg_edge* edge = edges (id);
  if (edge)
    return remove_edge (edge);
  else
    return false;
}*/

bool dbgrl_hg_hypergraph::remove_hyperedge (dbgrl_hg_hyperedge* hyperedge)
{
  vcl_vector<dbgrl_hg_edge*>::iterator E_it = hyperedge->connecting_edges().begin();
  while (E_it != hyperedge->connecting_edges().end()) {
    dbgrl_hg_edge* edge = (*E_it);
    _internal_disconnect_hyperedge_edge (hyperedge, edge);
  }

  vcl_vector<dbgrl_hg_vertex*>::iterator V_it = hyperedge->connecting_vertices().begin();
  while (V_it != hyperedge->connecting_vertices().end()) {
    dbgrl_hg_vertex* vertex = (*V_it);
    _internal_disconnect_hyperedge_vertex (hyperedge, vertex);
  }

  return _internal_del_hyperedge (hyperedge);
}

/*bool dbgrl_hg_hypergraph::remove_hyperedge (int id)
{
  dbgrl_hg_hyperedge* hyperedge = hyperedges (id);
  if (hyperedge)
    return remove_hyperedge (hyperedge);
  else
    return false;
}*/


////////////////////////////////////////////////////////////////////
//: ===== High-level Graph operation that the user should use =====
bool dbgrl_hg_hypergraph::topo_remove_vertex (dbgrl_hg_vertex* vertex)
{
  // ! Should check both edges and hyperedges!!
  if (vertex->connecting_edges().size() == 0) {
    assert (vertex->connecting_hyperedges().size() == 0);
    return remove_vertex (vertex);
  }
  else
    return false;
}

/*bool dbgrl_hg_hypergraph::topo_remove_vertex (int id)
{
  dbgrl_hg_vertex* vertex = vertices (id);
  if (vertex)
    return topo_remove_vertex (vertex);
  else
    return false;
}*/

bool dbgrl_hg_hypergraph::topo_remove_edge (dbgrl_hg_edge* edge)
{
  if (edge->connecting_hyperedges().size() == 0)
    return remove_edge (edge);
  else
    return false;
}

/*bool dbgrl_hg_hypergraph::topo_remove_edge (int id)
{
  dbgrl_hg_edge* edge = edges (id);
  if (edge)
    return topo_remove_edge (edge);
  else
    return false;
}*/

bool dbgrl_hg_hypergraph::topo_remove_hyperedge (dbgrl_hg_hyperedge* hyperedge)
{
  //: for dbgrl_hg_hypergraph, can remove the hyperedge directly.
  return remove_hyperedge (hyperedge);
}

/*bool dbgrl_hg_hypergraph::topo_remove_hyperedge (int id)
{
  //: for dbgrl_hg_hypergraph, can remove the hyperedge directly.
  return remove_hyperedge (id);
}*/
