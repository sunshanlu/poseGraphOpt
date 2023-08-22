#include "../include/VertexSE3.h"

namespace myself
{
    bool VertexSE3::write(std::ostream &os) const
    {
        // id tx ty tz qx qy qz qw
        Eigen::Quaterniond q = _estimate.unit_quaternion();
        os << id() << " " << _estimate.translation().transpose() << " ";
        os << q.x() << " " << q.y() << " "
           << q.z() << " " << q.w() << " ";

        return true;
    }

    bool VertexSE3::read(std::istream &is)
    {
        // tx ty tz qx qy qz qw
        double data[7];
        for (double &i: data) {
            is >> i;
        }
        Eigen::Quaterniond q(data[6], data[3], data[4], data[5]);
        Eigen::Vector3d t(data[0], data[1], data[2]);
        _estimate = Sophus::SE3d(q, t);
        return true;
    }

}