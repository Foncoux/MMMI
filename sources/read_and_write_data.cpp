/**
 * @file read_and_write_data.cpp
 * @author Esteban Foncoux 
 * @brief Lit et écrit dans des fichiers
 * @version 0.1
 * @date 2023-06-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <iomanip> 
#include <array>
#include <gsl/gsl_rng.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../config/setup.hpp"
#include "../config/config.hpp"
#include "../headers/Parametres.hpp"
#include "../headers/ODE.hpp"
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


void read_data_day(std::string filename,std::array<std::array<double, NB_DAY>, NB_DATA_DEATH_AGE_DAY>& data_day_matrix)
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


void set_social_contact_matrix(std::array<std::array<double, NB_CLASSE_SOCIAL_CONTACT_MATRIX>, NB_CLASSE_SOCIAL_CONTACT_MATRIX>& matrix,std::string filename)
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
        while(std::getline(iss, value, ',')){
            matrix[i][j] = std::stod(value);
            //std::cout << matrix[i][j] << "\n\n";
            j++;
        }
        i++;
    }

    file.close();    

}







/*
void write_data(std::array<std::array<double, T_FINAL>, COMPARTIMENT> output_data){
    

  std::ofstream myfile ("../data/integration.txt");
  if (myfile.is_open())
  {

        for (int j = 0; j < COMPARTIMENT; j++)
        {
            for (int i = 0; i < T_FINAL; i++)
            {
                myfile << output_data[j][i]*POP_TOT << " ";
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
*/

void write_data(const std::array<ODE, NB_CLASSE_AGE>& f,const std::string& filename1) {
    boost::property_tree::ptree main_tree;

    for (int k = 0; k < NB_CLASSE_AGE; k++) {
        boost::property_tree::ptree ode_tree;

        for (int j = 0; j < COMPARTIMENT; j++) {
            boost::property_tree::ptree child_tree;
            
            for (int i = 0; i < T_FINAL; i++) {
                boost::property_tree::ptree value;
                value.put_value(f[k].m_result_integration[j][i] * POP_TOT);
                child_tree.push_back(std::make_pair("", value));
            }
            ode_tree.add_child(NAMES_COMPARTIMENT[j], child_tree);
        }

        // Si vous voulez nommer chaque "ODE" dans le JSON (par exemple "ODE1", "ODE2", ...)
        std::string ode_name = "Classe" + std::to_string(k+1);
        main_tree.add_child(ode_name, ode_tree);
    }

    std::string filename = filename1 + ".json";
    std::ofstream myfile(filename);
    if (myfile.is_open()) {
        boost::property_tree::write_json(myfile, main_tree, true);
        myfile.close();
    } else {
        std::cout << "Unable to open file";
    }
}


void print_parameter(std::array<parametres,NB_CLASSE_AGE> p)
{
    std::cout << std::endl;
    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
    {   
        std::cout << "*** Classe d'age " << classe+1 << " ***" << std::endl;
        for (size_t i = 0; i < NB_CONFINEMENT+1; i++)
        {
            std::cout << "beta" << i << " : " << p[classe].beta[i] << std::endl;
        }
        
        std::cout << "delta"<< " : " << p[classe].delta << std::endl;
        std::cout << "eps" << " : " << p[classe].eps << std::endl;
        std::cout << "gamma"<< " : " << p[classe].gamma << std::endl;
        std::cout << "r" << " : " << p[classe].r << std::endl;
        
        for (size_t i = 0; i < COMPARTIMENT; i++)
        {
            std::cout << "x0[" << i << "] : " << p[classe].x0[classe][i] << std::endl;
        }
        std::cout << "\n" << std::endl;
    }  
    
}


/*
void write_save_parameters(std::array<parametres,NB_CLASSE_AGE> p, std::string save_nbr)
{
    std::string filename = "../data/save_dir/save" + save_nbr + ".txt"; 
    std::ofstream myfile (filename);
    if (myfile.is_open())
    {
        for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++)
        {
            for (size_t i = 0; i < NB_CONFINEMENT+1; i++)
            {
                myfile << p[classe].beta[i] << " ";
            }
            
            myfile << p[classe].delta << " " << p[classe].eps << " " << p[classe].gamma << " " << p[classe].r;
            
            for (size_t i = 0; i < COMPARTIMENT; i++)
            {
                myfile << " " << p[classe].x0[classe][i];
            }
            myfile << "\n";
        }  

        myfile.close();
    }
    else std::cout << "Unable to open file";

}
*/



void write_save_parameters(const std::array<parametres, NB_CLASSE_AGE>& p, const std::string& save_nbr) {
    boost::property_tree::ptree main_tree;

    for (size_t classe = 0; classe < NB_CLASSE_AGE; classe++) {
        boost::property_tree::ptree classe_tree;

        boost::property_tree::ptree beta_tree;
        for (size_t i = 0; i < NB_CONFINEMENT+1; i++) {
            beta_tree.put_value(p[classe].beta[i]);
            classe_tree.add_child("beta" + std::to_string(i), beta_tree);
            beta_tree.clear();
        }

        classe_tree.put("delta", p[classe].delta);
        classe_tree.put("eps", p[classe].eps);
        classe_tree.put("gamma", p[classe].gamma);
        classe_tree.put("r", p[classe].r);

        if(COMPARTIMENT == 6)
        {
            classe_tree.put("sigma", p[classe].sigma);
        }
        boost::property_tree::ptree x0_tree;
        for (size_t i = 0; i < COMPARTIMENT; i++) {
            boost::property_tree::ptree x0_item;
            x0_item.put_value(p[classe].x0[classe][i]);
            x0_tree.push_back(std::make_pair("", x0_item));
        }
        classe_tree.add_child("x0", x0_tree);

        main_tree.add_child("classe_" + std::to_string(classe), classe_tree);
    }

    std::string filename = save_nbr + ".json";
    std::ofstream myfile(filename);
    if (myfile.is_open()) {
        boost::property_tree::write_json(myfile, main_tree, true);
        myfile.close();
    } else {
        std::cout << "Unable to open file";
    }
}

/*
std::array<parametres,NB_CLASSE_AGE> read_save_parameters(std::string save_nbr)
{
    std::array<parametres,NB_CLASSE_AGE> p;

    std::string filename = "../data/save_dir/save" + save_nbr + ".txt"; 
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

    std::string line;
    int classe=0;

    while(std::getline(file, line)){
        
        std::istringstream iss(line);
        std::string value;
            
        for (size_t i = 0; i < NB_CONFINEMENT+1; i++)
        {
            std::getline(iss, value, ' ');
            p[classe].beta[i] = std::stod(value);
        }

        std::getline(iss, value, ' ');
        p[classe].delta = std::stod(value); 
        std::getline(iss, value, ' ');
        p[classe].eps = std::stod(value);
        std::getline(iss, value, ' ');
        p[classe].gamma = std::stod(value);
        std::getline(iss, value, ' ');
        p[classe].r = std::stod(value);


        std::getline(iss, value, ' ');
        p[classe].x0[classe][S_COMP] = std::stod(value);
        std::getline(iss, value, ' ');
        p[classe].x0[classe][I_COMP] = std::stod(value);
        std::getline(iss, value, ' ');
        p[classe].x0[classe][R_COMP] = std::stod(value);
        std::getline(iss, value, ' ');
        p[classe].x0[classe][Q_COMP] = std::stod(value);
        std::getline(iss, value, ' ');
        p[classe].x0[classe][D_COMP] = std::stod(value);
            
        
        classe++;
    }

    file.close();  
    return p; 
}
*/



std::array<parametres, NB_CLASSE_AGE> read_save_parameters(const std::string& save_nbr) {
    std::array<parametres, NB_CLASSE_AGE> p;

    std::string filename = save_nbr + ".json";
    boost::property_tree::ptree main_tree;
    boost::property_tree::read_json(filename, main_tree);

    int classe = 0;

    for (const auto& item : main_tree) {
        const auto& classe_tree = item.second;

        for (size_t i = 0; i < NB_CONFINEMENT+1; i++) {
            p[classe].beta[i] = classe_tree.get<double>("beta" + std::to_string(i));
        }

        p[classe].delta = classe_tree.get<double>("delta");
        p[classe].eps = classe_tree.get<double>("eps");
        p[classe].gamma = classe_tree.get<double>("gamma");
        p[classe].r = classe_tree.get<double>("r");
        if(COMPARTIMENT == 6)
        {
            p[classe].sigma = classe_tree.get<double>("sigma");
        }

        const auto& x0_tree = classe_tree.get_child("x0");
        int x0_index = 0;
        for (const auto& x0_item : x0_tree) {
            p[classe].x0[classe][x0_index] = x0_item.second.get_value<double>();
            x0_index++;
        }

        classe++;
    }

    return p;
}
