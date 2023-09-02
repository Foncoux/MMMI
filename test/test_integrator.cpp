#include <gtest/gtest.h>
#include <math.h>
#include <array>
#include <gsl/gsl_rng.h>

#include "../config/setup.hpp"
#include "../config/config.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
#include "../headers/fonction_continuous.hpp"





TEST(INTEGRATION,fonction_integrate)
{
    
    parametres p;
    double y[COMPARTIMENT] = { 1.0, 0.0 };

    ODE f;
    integrate(f,p,y);

    ASSERT_NEAR(f.m_result_integration[0][T_FINAL],cos(T_FINAL),0.0001);
    
}

