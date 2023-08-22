#pragma once

#include <g2o/core/base_vertex.h>
#include <sophus/se3.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include <string>

namespace myself
{
    class VertexSE3 : public g2o::BaseVertex<6, Sophus::SE3d>
    {
    public:
        using Vertex6d = Eigen::Matrix<double, 6, 1>;

        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        VertexSE3() = default;

        /*
         * 简体中文：
         *      在定义read()时，只需要7个double值，分别是tx ty tz qx qy qz qw
         *      在定义write()时，只需要8个值，分别是id tx ty tz qx qy qz qw
         * English:
         *      When defining read(), only 7 double values are required, which are tx ty tz qx qy qz qw
         *      When defining write(), only 8 values are required, namely id tx ty tz qx qy qz qw
         * */
        bool write(std::ostream &os) const override;

        bool read(std::istream &is) override;


        void setToOriginImpl() override
        {
            _estimate = Sophus::SE3d();
        }

        void oplusImpl(const number_t *v) override
        {
            // 通过Vertex6d和exp函数即可以实现左乘扰动模型的定义
            Vertex6d update;
            update << v[0], v[1], v[2], v[3], v[4], v[5];
            _estimate = Sophus::SE3d::exp(update) * _estimate;
        }

    };

}

