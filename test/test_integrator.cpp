

#include "../headers/integrator.hpp"
#include "../headers/ODE.hpp"

#include <gtest/gtest.h>
#include <math.h>


TEST(INTEGRATION,fonction_integrate)
{
    
    parametres p = {10};
    double y[COMPARTIMENT] = { 1.0, 0.0 };

    ODE f(1,y);
    integrate(f,p,y);

    ASSERT_NEAR(f.m_result_integration[0][T_FINAL],cos(T_FINAL),0.0001);
}

