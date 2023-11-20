#include <curvs.h>
#include <iomanip>
#include <my_functions.h>

const float PI = std::acos(-1.0f);

std::ostream &operator<<(std::ostream &os, const Point3D &point)
{
    os << std::fixed << std::setprecision(3) << "X: " << point.x << ", Y: " << point.y << ", Z: " << point.z;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Vector3D &vector)
{
    os << std::fixed << std::setprecision(3) << "X: " << vector.x << ", Y: " << vector.y << ", Z: " << vector.z;
    return os;
}

Circle::Circle(float radius) : radius_((radius < 0.0f) ? std::abs(radius) : radius) // радиус не может быть отрицательным
{
}

Ellipses::Ellipses(float radiusX, float radiusY) : Circle(radiusX), radiusY_((radiusY < 0.0f) ? std::abs(radiusY) : radiusY) // радиус не может быть отрицательным
{
}

Helixes3D::Helixes3D(float radius, float step) : Circle(radius), step_(step)
{
}

Point3D Circle::GetPoint(float t) const
{
    float x = radius_ * std::cos(t);
    float y = radius_ * std::sin(t);

    return Point3D(x, y, 0.0f);
}

Vector3D Circle::GetFirstDerivative(float t) const
{
    float dx_dt = -radius_ * std::sin(t); // Derivative of 'x' with respect to 't'
    float dy_dt = radius_ * std::cos(t);  // Derivative of 'y' with respect to 't'

    return Vector3D(dx_dt, dy_dt, 0.0f);
}

Point3D Ellipses::GetPoint(float t) const
{
    float x = radius_ * std::cos(t);
    float y = radiusY_ * std::sin(t);

    return Point3D(x, y, 0.0f);
}

Vector3D Ellipses::GetFirstDerivative(float t) const
{
    float dx_dt = -radius_ * std::sin(t); // Производная x по t
    float dy_dt = radiusY_ * std::cos(t); // Производная y по t

    return Vector3D(dx_dt, dy_dt, 0.0f);
}

Point3D Helixes3D::GetPoint(float t) const
{
    float module_t = std::abs(t); // for a Helixes3D 't' must be positive
    Point3D point = Circle::GetPoint(module_t);
    point.z = step_ * (module_t / (2.0f * PI));

    return point;
}

Vector3D Helixes3D::GetFirstDerivative(float t) const
{
    float module_t = std::abs(t); // для спирали t должен пыть положительным, так-как спираль не циклична
    Vector3D first_derivative = Circle::GetFirstDerivative(module_t);
    first_derivative.z = step_ * (module_t / (2.0f * PI)); // Производная z по t

    return first_derivative;
}

std::shared_ptr<Curv> Curv::GetRandomCurv(float minParam, float maxParam)
{
    float radius = MyFunc::GetRandomParam(minParam, maxParam);
    float secondParam = MyFunc::GetRandomParam(minParam, maxParam);
    int curvType = MyFunc::GetRandomParam(0, 3);
    switch (curvType)
    {
    case Curv::CIRCLE:
        return std::make_shared<Circle>(radius);
        break;
    case Curv::ELLIPSE:
        return std::make_shared<Ellipses>(radius, secondParam);
        break;
    case Curv::HELIX:
        return std::make_shared<Helixes3D>(radius, secondParam);
        break;
    }
    return nullptr;
}

std::vector<std::shared_ptr<Curv>> Curv::GetVectorOfRandomCurvs(size_t size, float minParam, float maxParam)
{
    std::vector<std::shared_ptr<Curv>> curvs{};

    for (size_t i = 0; i < size; i++)
    {
        curvs.push_back(Curv::GetRandomCurv(minParam, maxParam));
    }

    return curvs;
}
