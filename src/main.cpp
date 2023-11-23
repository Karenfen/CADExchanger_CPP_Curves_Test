#include <iostream>
#include <algorithm>
#include <numeric>
#include <tbb/blocked_range.h>
#include <tbb/parallel_reduce.h>
#include "curvs.h"
#include "my_functions.h"

void PrintCurvs(std::vector<std::shared_ptr<Curv>> curvs);

int main()
{
    std::vector<std::shared_ptr<Curv>> curvs = Curv::GetVectorOfRandomCurvs();

    std::cout << "Curvs:\n"
              << std::endl;

    PrintCurvs(curvs);

    std::vector<std::shared_ptr<Curv>> circles{};

    std::copy_if(curvs.begin(), curvs.end(), std::back_inserter(circles),
                 [](const std::shared_ptr<Curv> &ptr)
                 {
                     return ptr->GetType() == Curv::CIRCLE;
                 });

    std::cout << "Circles:\n"
              << std::endl;

    PrintCurvs(circles);

    std::sort(circles.begin(), circles.end(), [](const std::shared_ptr<Curv> &ptrA, const std::shared_ptr<Curv> &ptrB)
              { return ptrA->GetRadius() < ptrB->GetRadius(); });

    std::cout << "Circles (sorted):\n"
              << std::endl;

    PrintCurvs(circles);

    float sumRadii = std::accumulate(circles.begin(), circles.end(), 0.0f, [](float currentSum, const std::shared_ptr<Curv> &ptr)
                                     { return currentSum + ptr->GetRadius(); });

    float sum = tbb::parallel_reduce(
        tbb::blocked_range<size_t>(0, circles.size()), 0.0f,
        [&](const tbb::blocked_range<size_t> &range, float localSum) -> float
        {
            for (size_t index = range.begin(); index != range.end(); ++index)
            {
                localSum += (circles[index])->GetRadius();
            }
            return localSum;
        },
        [](float first, float second) -> float
        {
            return first + second;
        });

    std::cout << "sum of circle radii: " << sumRadii << std::endl;
    std::cout << "sum of circle radii (paralel): " << sum << std::endl;

    return 0;
}

void PrintCurvs(std::vector<std::shared_ptr<Curv>> curvs)
{
    for (size_t i = 0; i < curvs.size(); i++)
    {
        curvs.at(i)->print();
        std::cout << "Point for PI: " << curvs.at(i)->GetPoint(PI) << std::endl;
        std::cout << "First Derivative for PI: " << curvs.at(i)->GetFirstDerivative(PI) << "\n"
                  << std::endl;
    }
}
