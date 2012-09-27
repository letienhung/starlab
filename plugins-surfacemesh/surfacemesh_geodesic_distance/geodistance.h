#pragma once
#include "SurfaceMeshPlugins.h"
#include "SurfaceMeshHelper.h"
#include "RichParameterSet.h"

#include "GeoHeatHelper.h"

// This plugin efficently computes shortest geodesic distance to points on the mesh
// It is based on the paper "Geodesics in Heat" by Kennan Crane et al. 2012

class geodistance : public SurfaceMeshFilterPlugin{
    Q_OBJECT
    Q_INTERFACES(FilterPlugin)

public:
    geodistance() { h = NULL; }
    ~geodistance(){ delete h; }
    QString name() { return "Geodesic distance"; }
    QString description() { return "Compute geo-distance."; }

    void initParameters(RichParameterSet* pars);
    void applyFilter(RichParameterSet* pars);

    void precompute();
    void setSource(const QSet<Vertex> &fromVerts);

    ScalarVertexProperty uniformDistance(const QSet<Vertex> &source);

private:
    GeoHeatHelper*          h;
    SparseMatrix<Scalar>    A;
    Scalar                  t;
    SparseMatrix<Scalar>    Lc;
    VectorXd                u0;

    CholmodSolver heat_flow, poisson_solver;
};