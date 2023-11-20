#include <iostream>
#include <algorithm>
#include <numeric>
#include <curvs.h>
#include <my_functions.h>

int main()
{
    std::vector<std::shared_ptr<Curv>> curvs = Curv::GetVectorOfRandomCurvs();

    std::cout << "Curvs:\n"
              << std::endl;

    MyFunc::PrintCurvs(curvs);

    std::vector<std::shared_ptr<Curv>> circles{};

    std::copy_if(curvs.begin(), curvs.end(), std::back_inserter(circles),
                 [](const std::shared_ptr<Curv> &ptr)
                 {
                     return ptr->GetType() == Curv::CIRCLE;
                 });

    std::cout << "Circles:\n"
              << std::endl;

    MyFunc::PrintCurvs(circles);

    std::sort(circles.begin(), circles.end(), [](const std::shared_ptr<Curv> &ptrA, const std::shared_ptr<Curv> &ptrB)
              { return ptrA->GetRadius() < ptrB->GetRadius(); });

    std::cout << "Circles (sorted):\n"
              << std::endl;

    MyFunc::PrintCurvs(circles);

    float sumRadii = std::accumulate(circles.begin(), circles.end(), 0.0f, [](float currentSum, const std::shared_ptr<Curv> &ptr)
                                     { return currentSum + ptr->GetRadius(); });

    std::cout << "sum of circle radii: " << sumRadii << std::endl;

    return 0;
}