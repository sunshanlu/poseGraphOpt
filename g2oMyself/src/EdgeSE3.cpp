#include "EdgeSE3.h"

namespace myself
{
    void EdgeSE3::computeError()
    {
        auto *vertex0 = dynamic_cast<const VertexSE3 *>(_vertices[0]);
        auto *vertex1 = dynamic_cast<const VertexSE3 *>(_vertices[1]);
        Sophus::SE3d estimate0 = vertex0->estimate();
        Sophus::SE3d estimate1 = vertex1->estimate();
        _error = (_measurement.inverse() * estimate0.inverse() * estimate1).log();
    }

    bool EdgeSE3::read(std::istream &is)
    {
        double data[7];
        for (double &i: data) {
            is >> i;
        }
        Eigen::Vector3d t(data[0], data[1], data[2]);
        Eigen::Quaterniond q(data[6], data[3], data[4], data[5]);
        _measurement = Sophus::SE3d(q, t);

        for (int i = 0; i < _information.rows(); ++i)
            for (int j = i; j < _information.cols(); ++j) {
                is >> _information(i, j);
                if (i != j) {
                    _information(j, i) = _information(i, j);
                }
            }

        return true;
    }

    bool EdgeSE3::write(std::ostream &os) const
    {
        Eigen::Quaterniond q = _measurement.unit_quaternion();
        Eigen::Vector3d t = _measurement.translation();
        os << _vertices[0]->id() << " " << _vertices[1]->id() << " ";
        os << t.transpose() << " ";
        os << q.x() << " " << q.y() << " " << q.z() << " " << q.w();

        for (int i = 0; i != _information.rows(); ++i)
            for (int j = i; j != _information.cols(); ++j) {
                os << _information(i, j) << " ";
            }
        return true;
    }
}
