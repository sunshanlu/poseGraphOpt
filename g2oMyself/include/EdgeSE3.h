#pragma once

#include <g2o/core/base_binary_edge.h>
#include <sophus/se3.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "VertexSE3.h"

namespace myself
{
    class EdgeSE3 : public g2o::BaseBinaryEdge<6, Sophus::SE3d, VertexSE3, VertexSE3>
    {
        /*
         * 简体中文：
         *      1. 在read()函数中，设置了观测值和信息矩阵（上对角阵）
         *      2. 在write()函数中，设置了两个顶点的id，观测值和信息矩阵（上对角阵）
         *      3. Sophus::SE3d类型为李群，可以通过log()静态成员函数变为李代数（向量形式）
         *      4. Eigen::Matrix<double, 6, 2>类型为李代数类型，可以通过exp()函数变为李群Sophus::SE3d类型
         *      5. 信息矩阵为高斯分布协方差矩阵的逆，由于协方差矩阵是对称阵，信息矩阵同样也是对称阵
         * English:
         *      1. In the read() function, the observation value and information matrix (upper diagonal matrix) are set.
         *      2. In the write() function, the ids of the two vertices, observation values and information matrix
         *         (upper diagonal matrix) are set.
         *      3. The type of Sophus::SE3d is a Lie group, which can be transformed into a Lie
         *         algebra (vector form) through the log() static member function.
         *      4. The Eigen::Matrix<double, 6, 2> type is a Lie algebra type,
         *         which can be changed to a Lie group Sophus::SE3d type through the exp() function.
         * */
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        EdgeSE3() = default;

        bool read(std::istream &is) override;

        bool write(std::ostream &os) const override;

        void computeError() override;
    };
}


