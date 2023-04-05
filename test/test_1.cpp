
//#include <gtest/gtest_prod.h> si on utilise des fonctions d'affichage personnalisées
#include "../headers/Integrator.hpp"

#include <gtest/gtest.h>

TEST(ADD_1,zero)
{
    int a = 5;
    ASSERT_EQ(a,5);
}