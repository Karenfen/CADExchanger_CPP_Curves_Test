#include <random>
#include <memory>

class Curv;

namespace MyFunc
{
    template <typename T>
    T GetRandomParam(T min, T max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(min, max);

        return dis(gen);
    }

    void PrintCurvs(std::vector<std::shared_ptr<Curv>> curvs);
}