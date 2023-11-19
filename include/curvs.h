#pragma once

#include <ostream>
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>

extern const float PI;
struct Point3D;
struct Vector3D;

class Curv
{
public:
    virtual Point3D GetPoint(float t) const = 0;
    virtual Vector3D GetFirstDerivative(float t) const = 0;
    static std::unique_ptr<Curv> GetRandomCurv(float minParam = 0, float maxParam = 10.0f);
    static std::vector<std::unique_ptr<Curv>> GetVectorOfRandomCurvs(size_t size = 10, float minParam = 0.0f, float maxParam = 10.0f);
    virtual void print() = 0;
};

class Circle : public Curv
{
public:
    Circle(float radius);
    virtual ~Circle(){};
    virtual void print() override { std::cout << "Circle: radius = " << radius_ << std::endl; }

    virtual Point3D GetPoint(float t) const override;
    virtual Vector3D GetFirstDerivative(float t) const override;
    virtual float GetRadius() const { return radius_; }

protected:
    float radius_;
};

class Ellipses : public Circle
{
public:
    Ellipses(float radiusX, float radiusY);
    virtual ~Ellipses() override{};
    virtual void print() override { std::cout << "Ellipses: radius X = " << radius_ << " radius Y = " << radiusY_ << std::endl; }

    virtual Point3D GetPoint(float t) const override;
    virtual Vector3D GetFirstDerivative(float t) const override;
    virtual float GetRadiusX() const { return radius_; }
    virtual float GetRadiusY() const { return radiusY_; }

protected:
    float radiusY_;

private:
    virtual float GetRadius() const override { return radius_; }
};

class Helixes3D : public Circle
{
public:
    Helixes3D(float radius, float step);
    virtual ~Helixes3D() override{};
    virtual void print() override { std::cout << "Helixes3D: radius = " << radius_ << " step = " << step_ << std::endl; }

    virtual Point3D GetPoint(float t) const override;
    virtual Vector3D GetFirstDerivative(float t) const override;
    float GetStep() const { return step_; }

protected:
    float step_;
};

struct Point3D
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

struct Vector3D
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