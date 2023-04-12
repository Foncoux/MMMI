

#include "../headers/read_data.hpp"



void read_dataD(std::array<double,DEATH_NB_DAY> &death)
{
    std::ifstream myfile; 
    myfile.open("../data/Death_1mars_to_14dec.csv");

    std::string myline;
    

    if ( myfile.is_open() ) 
    {   
        std::getline (myfile, myline);
        int i=0;
        while ( myfile ) // equivalent to myfile.good()
        {
            std::getline (myfile, myline);

            if(! myline.empty())
            {   
                //std::cout << std::stoi(myline)<< " ";
                death[i] = std::stoi(myline)/POP_TOT;
                

            }

            
            i++;
        }

        myfile.close();
    }   
    else 
    {
        std::cout << "Couldn't open file\n";
    }
    
    
}

void read_dataH(std::array<double,HOSP_NB_DAY> &hosp)
{
    std::ifstream myfile; 
    myfile.open("../data/hosp_tot_17_10.csv");

    std::string myline;
    

    if ( myfile.is_open() ) 
    {   
        std::getline (myfile, myline);
        int i=0;
        while ( myfile ) // equivalent to myfile.good()
        {
            std::getline (myfile, myline);

            if(! myline.empty())
            {
                hosp[i] = std::stoi(myline)/POP_TOT;
            }

            
            i++;
            
        }
        myfile.close();
        std::cout << i << std::endl;
    }   
    else 
    {
        std::cout << "Couldn't open file\n";
    }

    

}


void write_data(std::array<std::array<double, T_FINAL+1>, COMPARTIMENT> output_data){
    

  std::ofstream myfile ("../data/integration.txt");
  if (myfile.is_open())
  {

        for (int j = 0; j < COMPARTIMENT; j++)
        {
            for (int i = 0; i < T_FINAL; i++)
            {
                myfile << std::setprecision(16) << output_data[j][i]*POP_TOT << " ";
                //fprintf(fpdata,"%.15lf ",);
            }
            //fprintf(fpdata,"\n");
            myfile << "\n";
        }
    myfile.close();
  }
  else std::cout << "Unable to open file";

 
}

