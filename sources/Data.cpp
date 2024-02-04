#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <iomanip> 
#include <array>
#include <gsl/gsl_rng.h>

#include "../config/config.hpp"


#include "../config/setup.hpp"
#include "../config/config.hpp"

#include "../headers/Parametres.hpp"
#include "../headers/fonction_discret.hpp"
#include "../headers/Data.hpp"

Data::Data()
{
    
    //read_data<NB_DATA_DAY, NB_DAY>(DAY_DATA_filename, day_all);
    //read_data<NB_DATA_DEATH_AGE_DAY, NB_DAY>(DAY_DEATH_AGE_DATA_filename, day_death_age);
    //read_data<NB_CLASSE_MONTH, NB_MONTH>(DEATH_MONTH_AGE_DATA_filename, month_death_ages);

    //read_data<NB_CLASSE_WEEK, NB_WEEK>(HOSP_WEEK_AGE_DATA_filename, week_hosp_ages);

    read_data_csv<NB_DATA_DAY_DEATH, NB_DAY_CALIBRATION>(DAY_DEATH_DATA_filename, day_death);
    read_data_csv<NB_DATA_DAY_HOSP, NB_DAY_CALIBRATION>(DAY_HOSP_DATA_filename, day_hosp);

    
}

Data DATA;

template <std::size_t X, std::size_t Y>
void Data::read_data_csv(std::string filename, std::array<std::array<double, Y>, X>& data_matrix)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
        return;
    }

    std::string line;
    std::getline(file,line);

    int row = 0;
    while (std::getline(file, line) && row < Y) {
        std::istringstream iss(line);
        std::string value;
        int col = 0;

        while (std::getline(iss, value, ',') && col < X ) {
            if (std::stod(value) != -1) {
                data_matrix[col][row] = std::stod(value);
            } else {
                data_matrix[col][row] = -1;
            }
            col++;
        }
        row++;
    }

    file.close();
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


void write_data_csv(const ODE& f,const std::string& filename1) {
    std::ofstream file(filename1 + ".csv");
    if (file.is_open()) {

        //put headers in the top of the csv file
        for (int i=0;i<COMPARTIMENT_TOT*NB_CLASSE_AGE; i++) {
            file << NAMES_COMPARTIMENT_CSV[i];
            if(i != COMPARTIMENT_TOT*NB_CLASSE_AGE-1)
            {
                file << ',';
            }
        }
        file << "\n";

        for (size_t day = 0; day < NB_DAY; day++)
        {
            for (int classe=0; classe < NB_CLASSE_AGE; classe++) 
            {
                for (int comp=0;comp<COMPARTIMENT_TOT; comp++) 
                {
                    file << f.m_result_simulation[classe][comp][day];

                    if(comp != COMPARTIMENT_TOT-1)
                    {
                        file << ',';
                    }
                    if(classe != NB_CLASSE_AGE-1 && comp == COMPARTIMENT_TOT-1)
                    {
                        file << ',';
                    }
                }
            }
            file << '\n';
        }
        file.close();
        
    }else{
        std::cerr << "Impossible d'ouvrir le fichier " << filename1 << std::endl;
    }
}


void write_save_parameters_MCMC(const std::vector<std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE>> p_storage) {
    
    std::ofstream file(std::string(SAVE_MCMC_WRITE) + ".csv");
    file << std::fixed << std::setprecision(15);
    
    if (file.is_open()){
        //put headers in the top of the csv file
        for (int i=0;i<NB_PARAM_TOT*NB_CLASSE_AGE; i++) {
            file << NAMES_PARAM[i];
            if(i != NB_PARAM_TOT*NB_CLASSE_AGE-1)
            {
                file << ',';
            }
        }
        file << "\n";

        //data storage
        for (size_t vec = 0; vec < p_storage.size(); vec++)
        {
            for (int i=0;i<NB_PARAM_TOT*NB_CLASSE_AGE; i++){
                file << p_storage[vec][i];
                if(i != NB_PARAM_TOT*NB_CLASSE_AGE-1)
                {
                    file << ',';
                }
            }
            file << "\n";
        }
        
        file.close();
        
    } else {
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
    }
}



void write_save_parameters(const std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE>& p, const std::string& save_nbr) {
    std::ofstream file(save_nbr + ".csv");
    file << std::fixed << std::setprecision(15);
    if (file.is_open()) {
        for (int i=0;i<NB_PARAM_TOT*NB_CLASSE_AGE; i++) {
            file << NAMES_PARAM[i];
            if(i != NB_PARAM_TOT*NB_CLASSE_AGE-1)
            {
                file << ',';
            }
        }
        file << "\n";

        for (int i=0;i<NB_PARAM_TOT*NB_CLASSE_AGE; i++){
            file << p[i];
            if(i != NB_PARAM_TOT*NB_CLASSE_AGE-1)
            {
                file << ',';
            }
        }
        
        file.close();
        
    } else {
        std::cerr << "Impossible d'ouvrir le fichier " << save_nbr << std::endl;
    }
}


std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> read_save_parameters(const std::string& save_nbr)
{
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p;
    std::ifstream file(save_nbr + ".csv");
    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier. (read_save_parameters)" << std::endl;
        exit(0);
    }

    std::string line;
    std::getline(file,line);

    std::getline(file, line);
    std::istringstream iss(line);
    std::string value;
    int i = 0;

    while (std::getline(iss, value, ',') && i < NB_PARAM_TOT*NB_CLASSE_AGE ) {
        p[i] = std::stod(value);
        
        i++;
    }
        
    
    
    file.close();
    return p;
}


std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> read_nomad_best_feasible_solution()
{
    std::array<double,NB_PARAM_TOT*NB_CLASSE_AGE> p;
    std::ifstream file("../best_feasible_point.txt");
    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier. (read_nomad_best_feasible)" << std::endl;
        exit(0);
    }


    double value;
    int i=0;
    while (file >> value && i < NB_PARAM_TOT*NB_CLASSE_AGE) {
        p[i] = value;
        i++;
    }

    // Fermer le fichier
    file.close();
    
    return p;
}
