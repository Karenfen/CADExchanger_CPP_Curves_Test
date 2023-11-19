#include <iostream>
#include <curvs.h>

int main()
{
    std::vector<std::unique_ptr<Curv>> curvs = Curv::GetVectorOfRandomCurvs();

    for (size_t i = 0; i < curvs.size(); i++)
    {
        curvs.at(i)->print();
    }

    return 0;
}
