#include <array>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip> 

#include "config.hpp"

std::vector<int> TAB_DATE_CONFINEMENT;
std::vector<double> PROP_PAR_CLASSE;
std::vector<std::string> NAMES_COMPARTIMENT;
std::vector<std::vector<double>> SOCIAL_CONTACT_MATRIX;
std::vector<std::string> SELECT_CLASSE_AGE;

void config_table_extern(){

    switch (NB_CONFINEMENT)
    {
    case 4:
        //std::array<int, NB_CONFINEMENT> TAB_DATE_CONFINEMENT = {19,76,233,269};
        TAB_DATE_CONFINEMENT = {20,77,98,233};
        break;
        
    case 6:
        TAB_DATE_CONFINEMENT = {20,77,98,133,188,233};
        break;

    default:
        break;
    }
    



    
    //std::array<double, NB_CLASSE_AGE> PROP_PAR_CLASSE = {0.2434811,0.2719328,0.2918983,0.1926878};
    //std::array<double, NB_CLASSE_AGE> PROP_PAR_CLASSE = {0.23,0.265,0.332,0.173};
    switch (NB_CLASSE_AGE)
    {
    case 1:
        PROP_PAR_CLASSE = {1};
        break;

    case 2:
        PROP_PAR_CLASSE = {0.7012859, 0.2987141};
        break;
    default:
        break;
    }




    
    switch (COMPARTIMENT_TOT)
    {
    case 6:
        NAMES_COMPARTIMENT = {"S","I","R","Q","D","Q_entry"};
        break;
    
    case 7:
        NAMES_COMPARTIMENT = {"S","I","R","Q","D","E"};
        break;
    
    default:
        break;
    }

    std::string filename = SOCIAL_CONTACT_MATRIX_filename;
    set_social_contact_matrix(SOCIAL_CONTACT_MATRIX,filename);
    

}


void set_social_contact_matrix(std::vector<std::vector<double>>& matrix, std::string filename) {   
    
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
        return;
    }
    
    std::string line;
    
    while(std::getline(file, line)){
        std::vector<double> row;
        std::istringstream iss(line);
        std::string value;
        while(std::getline(iss, value, ',')){
            row.push_back(std::stod(value));
        }
        matrix.push_back(row);
    }

    file.close();    
}


//https://dub.uu.nl/en/depth/timeline-looking-back-whole-year-pandemic
//https://grenzinfo.eu/nl/strengere-maatregelen-in-nederland-vanaf-14-oktober-2020/
//https://www.rijksoverheid.nl/onderwerpen/coronavirus-tijdlijn/november-2020-verzwaring-en-verlenging-van-de-gedeeltelijke-lockdown
//https://www.rijksoverheid.nl/onderwerpen/coronavirus-tijdlijn/maart-2020-maatregelen-tegen-verspreiding-coronavirus
//https://www.containmentnu.nl/articles/timeline?lang=en
//https://www.researchgate.net/figure/Timeline-of-the-COVID-19-pandemic-in-the-Netherlands-and-Lifelines-data-collection-A_fig1_350142568
//file:///home/foncoux/T%C3%A9l%C3%A9chargements/jech-2020-215678.full1.pdf
