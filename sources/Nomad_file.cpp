#include <vector>


#include "nomad/Nomad/nomad.hpp"
#include "Nomad_file.hpp"

#include "../config/config.hpp"

#include "ODE.hpp"
#include "fonction_discret.hpp"
#include "Data.hpp"
#include "fonction_obj.hpp"
#include "../headers/Data.hpp"


void initAllParams(std::shared_ptr<NOMAD::AllParameters> allParams)
{
    // Parameters creation
    // Number of variables
    size_t n = NB_CLASSE_AGE*NB_PARAM_TOT;
    allParams->setAttributeValue( "DIMENSION", n);
    // The algorithm terminates after
    // this number of black-box evaluations
    allParams->setAttributeValue( "MAX_BB_EVAL", 5000);
    // Starting point
    NOMAD::Point X0(n, 0.1);
    X0[PARAM_ID_X0_infect] = 2500/POP_TOT; // starting point (0.0 0.0 0.0 0.0 0.0 -4.0)
    allParams->setAttributeValue( "X0", X0 );

    allParams->getPbParams()->setAttributeValue("GRANULARITY", NOMAD::ArrayOfDouble(n, 0));

    // Constraints and objective
    NOMAD::BBOutputTypeList bbOutputTypes;

    bbOutputTypes.push_back(NOMAD::BBOutputType::OBJ);

    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {
        bbOutputTypes.push_back(NOMAD::BBOutputType::EB);
        bbOutputTypes.push_back(NOMAD::BBOutputType::EB);
    }

    allParams->setAttributeValue("BB_OUTPUT_TYPE", bbOutputTypes );
    allParams->setAttributeValue("DIRECTION_TYPE", NOMAD::DirectionType::ORTHO_2N);
    allParams->setAttributeValue("DISPLAY_DEGREE", 2);
    std::string best_feasible_sol_filename = "../best_feasible_point.txt";
    allParams->setAttributeValue("SOLUTION_FILE", best_feasible_sol_filename);

    allParams->setAttributeValue("LOWER_BOUND", NOMAD::ArrayOfDouble(n, 0.0000000000001)); // all var. >= 0 
    NOMAD::ArrayOfDouble ub(n,1);     // x_i < 1
    ub[PARAM_ID_X0_infect] = 5000/POP_TOT;     // x_x_0 <= 5000/POP_TOT 

    allParams->setAttributeValue("UPPER_BOUND", ub);






    // Parameters validation
    allParams->checkAndComply();

}


/*----------------------------------------*/
/*               The problem              */
/*----------------------------------------*/

My_Evaluator::My_Evaluator(const std::shared_ptr<NOMAD::EvalParameters>& evalParams)
: NOMAD::Evaluator(evalParams, NOMAD::EvalType::BB) // Evaluator for true blackbox evaluations only
{}

My_Evaluator::~My_Evaluator() {}

bool My_Evaluator::eval_x(NOMAD::EvalPoint &x, const NOMAD::Double &hMax, bool &countEval) const
{
    bool eval_ok = false;
    // Based on G2.
    NOMAD::Double f = 1e+20;
    std::vector<double> nbr;

    try
    {
        Data data;
        ODE fct;
        
        if (model(fct,x) !=-1)
        {
            f = -fonction_obj(data,fct,1);
        }else{
            
        }
        
        
        for (size_t i = 0; i < NB_PARAM_TOT; i++)
        {
            nbr.push_back(x[i].todouble());
        }
    

        NOMAD::Double EB;
        std::string bbo = f.tostring();

        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            EB = x[NB_PARAM_TOT*classe + PARAM_ID_EPS].todouble() + x[NB_PARAM_TOT*classe + PARAM_ID_R].todouble() -1;
            bbo += " " + EB.tostring();
            EB = x[NB_PARAM_TOT*classe + PARAM_ID_DELTA].todouble() + x[NB_PARAM_TOT*classe + PARAM_ID_GAMMA].todouble() -1;
            bbo += " " + EB.tostring();
        }


        x.setBBO(bbo);

        eval_ok = true;
    }
    catch (std::exception &e)
    {
        std::string err("Exception: ");
        err += e.what();
        throw std::logic_error(err);
    }

    countEval = true;
    return eval_ok;
}


void main2()
{
    NOMAD::MainStep TheMainStep;

    auto params = std::make_shared<NOMAD::AllParameters>();
    initAllParams(params);
    TheMainStep.setAllParameters(params);

    auto ev = std::make_unique<My_Evaluator>(params->getEvalParams());
    TheMainStep.setEvaluator(std::move(ev));

    try
    {
        TheMainStep.start();
        TheMainStep.run();
        TheMainStep.end();



    }
    catch(std::exception &e)
    {
        std::cerr << "\nNOMAD has been interrupted (" << e.what() << ")\n\n";
    }
}