
#include "nomad/Nomad/nomad.hpp"
#include "Nomad_file.hpp"


void initAllParams(std::shared_ptr<NOMAD::AllParameters> allParams)
{
    // Parameters creation
    // Number of variables
    size_t n = 10;
    allParams->setAttributeValue( "DIMENSION", n);
    // The algorithm terminates after
    // this number of black-box evaluations
    allParams->setAttributeValue( "MAX_BB_EVAL", 1000);
    // Starting point
    allParams->setAttributeValue( "X0", NOMAD::Point(n, 7.0) );

    allParams->getPbParams()->setAttributeValue("GRANULARITY", NOMAD::ArrayOfDouble(n, 0.0000001));

    // Constraints and objective
    NOMAD::BBOutputTypeList bbOutputTypes;
    bbOutputTypes.push_back(NOMAD::BBOutputType::PB);     // g1
    bbOutputTypes.push_back(NOMAD::BBOutputType::PB);     // g2
    bbOutputTypes.push_back(NOMAD::BBOutputType::OBJ);    // f
    bbOutputTypes.push_back(NOMAD::BBOutputType::EB);     // c2000
    allParams->setAttributeValue("BB_OUTPUT_TYPE", bbOutputTypes );
    allParams->setAttributeValue("DIRECTION_TYPE", NOMAD::DirectionType::ORTHO_2N);
    allParams->setAttributeValue("DISPLAY_DEGREE", 2);

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
    NOMAD::Double f = 1e+20, g1 = 1e+20, g2 = 1e+20;
    NOMAD::Double sum1 = 0.0, sum2 = 0.0, sum3 = 0.0, prod1 = 1.0, prod2 = 1.0;
    size_t n = x.size();

    try
    {
        for (size_t i = 0; i < n ; i++)
        {
            sum1  += pow(cos(x[i].todouble()), 4);
            sum2  += x[i];
            sum3  += (i+1)*x[i]*x[i];
            prod1 *= pow(cos(x[i].todouble()), 2);
            if (prod2 != 0.0)
            {
                if (x[i] == 0.0)
                {
                    prod2 = 0.0;
                }
                else
                {
                    prod2 *= x[i];
                }
            }
        }

        g1 = -prod2 + 0.75;
        g2 = sum2 -7.5 * n;

        f = 10*g1 + 10*g2;
        if (0.0 != sum3)
        {
            f -= ((sum1 -2*prod1) / sum3.sqrt()).abs();
        }
        // Scale
        if (f.isDefined())
        {
            f *= 1e-5;
        }

        NOMAD::Double c2000 = -f-2000;
        std::string bbo = g1.tostring();
        bbo += " " + g2.tostring();
        bbo += " " + f.tostring();
        bbo += " " + c2000.tostring();

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