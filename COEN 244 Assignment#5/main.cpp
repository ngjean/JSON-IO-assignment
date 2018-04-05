#include <iostream>
#include <vector>
#include <fstream>
#include "../json-develop/single_include/nlohmann/json.hpp"

using json = nlohmann::json;//for convinience

struct batters
{
    std::string id;
    std::string type;
};

struct toppings
{
    std::string id;
    std::string type;
};

struct items
{
    int id;
    int ppu;
    std::string name;
    std::string type;
    std::vector<batters> batter;
    std::vector<toppings> topping;

};


int main()
{
    json j;
    std::vector<items> item;

    std::ifstream infile;//input from the file
    {
        infile.open("Sample.json");
        if(infile.fail())
        {
            std::cout<<"file not found"<<std::endl;
        }
        else
        {
            infile>>j;
        }
        infile.close();
    }

   for(unsigned int inum = 0; inum < j.at("items").at("item").size(); inum++ )
    {
        batters tbatter;
        toppings ttopping;
        items titem;

        titem.id = j["items"]["item"][inum].at("id").get<int>();
        titem.ppu = j["items"]["item"][inum].at("ppu").get<int>();
        titem.name = j["items"]["item"][inum].at("name").get<std::string>();
        titem.type = j["items"]["item"][inum].at("type").get<std::string>();

        for(unsigned int icheck = 0 ; icheck < j["items"]["item"][inum].at("batters").at("batter").size() ; icheck++ )
        {
            tbatter.id = j["items"]["item"][inum]["batters"]["batter"][icheck].at("id").get<std::string>();
            tbatter.type = j["items"]["item"][inum]["batters"]["batter"][icheck].at("type").get<std::string>();

            titem.batter.push_back(tbatter);
        }

        for(unsigned int icheck = 0 ; icheck < j["items"]["item"][inum].at("toppings").at("topping").size() ; icheck++ )
        {
           ttopping.id = j["items"]["item"][inum]["toppings"]["topping"][icheck].at("id").get<std::string>();
           ttopping.type = j["items"]["item"][inum]["toppings"]["topping"][icheck].at("type").get<std::string>();

            titem.topping.push_back(ttopping);
        }

        item.push_back(titem);
    }


    for(unsigned int inum = 0 ; inum < item.size(); inum++)
    {
        std::cout<<item[inum].id<<std::endl;
        std::cout<<item[inum].name<<std::endl;
        std::cout<<item[inum].ppu<<std::endl;
        std::cout<<item[inum].type<<std::endl;
        std::cout<<"batters: "<< std::endl<< std::endl;
        for(unsigned int icheck = 0; icheck < item[inum].batter.size(); icheck++)
        {
            std::cout<<item[inum].batter[icheck].id<<std::endl;
            std::cout<<item[inum].batter[icheck].type<<std::endl;
        }
         std::cout<<"toppings: "<< std::endl<< std::endl;
        for(unsigned int icheck = 0; icheck < item[inum].topping.size(); icheck++)
        {
            std::cout<<item[inum].topping[icheck].id<<std::endl;
            std::cout<<item[inum].topping[icheck].type<<std::endl;
        }
    }
  //  std::cout<<j["items"]["item"].size([0].at("id").get<int>()<<std::endl;

    std::ofstream outfile;//output to the file
    {
        outfile.open("Sample.json");
        if(outfile.fail())
        {
            std::cout<<"sorry file not found"<<std::endl;
        }
        else
        {
           outfile<<std::setw(4)<<j<<std::endl;
        }
        outfile.close();
    }


    return 0;
}
