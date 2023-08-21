#include <fstream>
#include <sstream>
#include <g2o/types/slam3d/edge_se3.h>
#include <g2o/types/slam3d/vertex_se3.h>
#include <g2o/core/block_solver.h>
#include <g2o/solvers/eigen/linear_solver_eigen.h>
#include <g2o/core/optimization_algorithm_levenberg.h>

#include "g2oSE3.h"

using BlockSolverType = g2o::BlockSolver<g2o::BlockSolverTraits<6, 6>>;
using LinearSolverType = g2o::LinearSolverEigen<BlockSolverType::PoseMatrixType>;

void G2OSE3::addVertexAndEdge(const std::string &filePath)
{
    auto *algorithm = new g2o::OptimizationAlgorithmLevenberg(
            std::make_unique<BlockSolverType>(
                    std::make_unique<LinearSolverType>()
            )
    );
    graph.setVerbose(VERBOSE);
    graph.setAlgorithm(algorithm);

    std::ifstream ifs(filePath);
    std::string lineStr;
    while (std::getline(ifs, lineStr)) {
        std::istringstream line(lineStr);
        line >> *this;
    }
}

std::istream &operator>>(std::istream &is, G2OSE3 &g2oSE3)
{
    static int edgeID = 0;
    std::string name;
    is >> name;
    int vertexId= 0;
    // 添加顶点
    if (name == "VERTEX_SE3:QUAT") {
        is >> vertexId;
        auto *vertex = new g2o::VertexSE3;
        vertex->setId(vertexId);
        vertex->read(is);
        if (vertexId == 0)
            vertex->setFixed(true);
        g2oSE3.graph.addVertex(vertex);
    } else if(name == "EDGE_SE3:QUAT"){// 添加边
        int idx1, idx2;
        is >> idx1 >> idx2;
        auto *edge = new g2o::EdgeSE3;
        edge->setId(edgeID++);
        edge->setVertex(0, g2oSE3.graph.vertices()[idx1]);
        edge->setVertex(1, g2oSE3.graph.vertices()[idx2]);
        edge->read(is);
        g2oSE3.graph.addEdge(edge);
    }
    return is;
}

void G2OSE3::optimize(int maxIterations)
{
    graph.initializeOptimization();
    graph.optimize(maxIterations);
}

void G2OSE3::writeToG2o(const std::string &filePath)
{
    std::cout << "saving optimization results ..." << std::endl;
    graph.save(filePath.c_str());
}
