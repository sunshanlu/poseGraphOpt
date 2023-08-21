#pragma once
#include <string>

#include <g2o/core/sparse_optimizer.h>

const bool VERBOSE = true;

class G2OSE3
{
    friend std::istream &operator>>(std::istream &is, G2OSE3 &g2oSE3);
public:
    using SparseOptimizer = g2o::SparseOptimizer;

    G2OSE3() = default;

    ~G2OSE3() = default;

    /*
    ** 简体中文:读取g2o文件，并向G2OSE3类中添加顶点和边
    ** English: Read the g2o file and add vertices and edges to the G2OSE3 class
    **/
    void addVertexAndEdge(const std::string &filePath);

    void optimize(int maxIterations);

    /*
    ** 简体中文：将优化好的位姿信息写入到g2o类型的文件中
    ** English:Write the optimized pose information to the g2o type file
    **/
    void writeToG2o(const std::string &filePath);

private:

    SparseOptimizer graph;
};

std::istream &operator>>(std::istream &is, G2OSE3 &g2oSE3);