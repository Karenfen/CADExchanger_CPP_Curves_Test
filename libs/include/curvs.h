#pragma once

#include "curvs_global.h"

#include <ostream>
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>

extern const float PI;
struct Point3D;
struct Vector3D;

class __declspec(dllexport) Curv
{
public:
    enum Type
    {
        CIRCLE,
        ELLIPSE,
        HELIX
    };

    virtual Point3D GetPoint(float t) const = 0;
    virtual Vector3D GetFirstDerivative(float t) const = 0;
    static std::shared_ptr<Curv> GetRandomCurv(float minParam = 0, float maxParam = 10.0f);
    static std::vector<std::shared_ptr<Curv>> GetVectorOfRandomCurvs(size_t size = 10, float minParam = 0.0f, float maxParam = 10.0f);
    virtual void print() const = 0;
    virtual Type GetType() const = 0;
    virtual float GetRadius() const = 0;
};

class __declspec(dllexport) Circle : public Curv
{
public:
    Circle(float radius);
    virtual ~Circle(){};
    virtual void print() const override { std::cout << "Circle: radius = " << radius_ << std::endl; }
    bool operator==(const Circle &other) const
    {
        return radius_ == other.radius_;
    }

    virtual Point3D GetPoint(float t) const override;
    virtual Vector3D GetFirstDerivative(float t) const override;
    virtual float GetRadius() const override { return radius_; }
    virtual Type GetType() const override { return Type::CIRCLE; }

protected:
    float radius_;
};

class __declspec(dllexport) Ellipses : public Circle
{
public:
    Ellipses(float radiusX, float radiusY);
    virtual ~Ellipses() override{};
    virtual void print() const override { std::cout << "Ellipses: radius X = " << radius_ << " radius Y = " << radiusY_ << std::endl; }
    bool operator==(const Ellipses &other) const
    {
        return ((radius_ == other.radius_) && (radiusY_ == other.radiusY_));
    }

    virtual Point3D GetPoint(float t) const override;
    virtual Vector3D GetFirstDerivative(float t) const override;
    virtual float GetRadiusX() const { return radius_; }
    virtual float GetRadiusY() const { return radiusY_; }
    virtual Type GetType() const override { return Type::ELLIPSE; }

protected:
    float radiusY_;

private:
    virtual float GetRadius() const override { return radius_; }
};

class __declspec(dllexport) Helixes3D : public Circle
{
public:
    Helixes3D(float radius, float step);
    virtual ~Helixes3D() override{};
    virtual void print() const override { std::cout << "Helixes3D: radius = " << radius_ << " step = " << step_ << std::endl; }
    bool operator==(const Helixes3D &other) const
    {
        return ((radius_ == other.radius_) && (step_ == other.step_));
    }

    virtual Point3D GetPoint(float t) const override;
    virtual Vector3D GetFirstDerivative(float t) const override;
    float GetStep() const { return step_; }
    virtual Type GetType() const override { return Type::HELIX; }

protected:
    float step_;
};

struct __declspec(dllexport) Point3D
{
    float x, y, z;

    Point3D() : x(0.0f), y(0.0f), z(0.0f) {}
    Point3D(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

    // Перегрузка оператора присваивания
    Point3D &operator=(const Point3D &other)
    {
        if (this != &other) // Проверка на самоприсваивание
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    Point3D operator+(const Point3D &other) const
    {
        return Point3D(x + other.x, y + other.y, z + other.z);
    }

    bool operator==(const Point3D &other) const
    {
        return (x == other.x) && (y == other.y) && (z == other.z);
    }
};

struct __declspec(dllexport) Vector3D
{
    float x, y, z;

    Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3D(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

    // Метод для нормализации вектора
    void normalize()
    {
        float length = std::sqrt(x * x + y * y + z * z);
        if (length != 0.0f) // Проверка на нулевую длину
        {
            x /= length;
            y /= length;
            z /= length;
        }
    }

    // Перегрузка оператора присваивания
    Vector3D &operator=(const Vector3D &other)
    {
        if (this != &other) // Проверка на самоприсваивание
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }
};

std::ostream &operator<<(std::ostream &os, const Point3D &point);
std::ostream &operator<<(std::ostream &os, const Vector3D &vector);
