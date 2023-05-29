

#include "../headers/read_and_write_data.hpp"



void read_data_day(std::string filename,std::array<std::array<double, NB_DAY>, NB_DATA_DAY>& data_day_matrix)
{
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

    std::string line;
    int i=0;
    while(std::getline(file, line)){
        int j=0;
        std::istringstream iss(line);
        std::string value;
        int skip_first_value = 1;

        while(std::getline(iss, value, ',')){
            if(skip_first_value == 0)
            {
                if(std::stod(value) != -1)
                {
                    data_day_matrix[i][j] = std::stod(value)/POP_TOT;
                    j++;
                }else{
                    data_day_matrix[i][j] = -1;
                    j++;
                }
                
                
            }else{skip_first_value = 0;}
            
            
        }
        i++;
    }

    file.close();   
    
}


void read_data_week_age(std::string filename,std::array<std::array<double, NB_WEEK>, NB_CLASSE_WEEK>& data_week_matrix)
{
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

    std::string line;
    int i=0;
    while(std::getline(file, line)){
        int j=0;
        std::istringstream iss(line);
        std::string value;
        int skip_first_value = 1;

        while(std::getline(iss, value, ',')){
            if (skip_first_value == 0)
            {
                if (std::stod(value) != -1)
                {
                    data_week_matrix[i][j] = std::stod(value)/POP_TOT;
                    j++;
                }else{
                    data_week_matrix[i][j] = -1;
                    j++;
                }
                
                
            }else{skip_first_value = 0;}
            
            
        }
        i++;
    }

    file.close();   
    
}

void read_data_month_age(std::string filename,std::array<std::array<double, NB_MONTH>, NB_CLASSE_MONTH>& data_month_matrix)
{
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

    std::string line;
    int i=0;
    while(std::getline(file, line)){
        int j=0;
        std::istringstream iss(line);
        std::string value;
        int skip_first_value = 1;

        while(std::getline(iss, value, ',')){
            if (skip_first_value == 0)
            {
                if (std::stod(value) != -1)
                {
                    data_month_matrix[i][j] = std::stod(value)/POP_TOT;
                    j++;
                }else{
                    data_month_matrix[i][j] = -1;
                    j++;
                }
                
                
            }else{skip_first_value = 0;}
            
            
        }
        i++;
    }

    file.close();   
    
}




void read_dataH(std::array<double,NB_DAY> &hosp)
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
        
    }   
    else 
    {
        std::cout << "Couldn't open file\n";
    }

    

}


void set_social_contact_matrix(std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX>& matrix)
{   
    std::ifstream file("../data/social_contact_matrix.csv");
    if(!file.is_open()){
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }
    
    std::string line;
    int i=0;
    while(std::getline(file, line)){
        int j=0;
        std::istringstream iss(line);
        std::string value;
        while(std::getline(iss, value, ',')){
            matrix[i][j] = std::stod(value);
            j++;
        }
        i++;
    }

    file.close();    

}





void write_data(std::array<std::array<double, T_FINAL>, COMPARTIMENT> output_data){
    

  std::ofstream myfile ("../data/integration.txt");
  if (myfile.is_open())
  {

        for (int j = 0; j < COMPARTIMENT; j++)
        {
            for (int i = 0; i < T_FINAL; i++)
            {
                myfile /*<< std::setprecision(16)*/ << output_data[j][i]*POP_TOT << " ";
                //std::cout << i << "   ";
                //fprintf(fpdata,"%.15lf ",);
            }
            //fprintf(fpdata,"\n");
            myfile << "\n";
        }
    myfile.close();
  }
  else std::cout << "Unable to open file";

 
}

