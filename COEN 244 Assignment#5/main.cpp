#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include "../json-develop/single_include/nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;//for convinience

struct batters
{
    int id;
    std::string type;
};

struct toppings
{
    int id;
    std::string type;
};

struct items
{
    int id;
    float ppu;
    std::string name;
    std::string type;
    std::vector<batters>batter;
    std::vector<toppings>topping;

};

void display(std::vector<items> item)
{
    int ispace(10);
    cout<<left<<setw(ispace-2)<<"id"<<setw(ispace)<<"name"<<setw(ispace)<<"ppu"<<setw(ispace)
        <<"type"<<setw(ispace+3)<<"batter#"<<setw(ispace+3)<<"batter"<<setw(ispace+3)<<"topping#"<<setw(ispace)<<"topping"<< endl<<endl;
    for(unsigned int inum = 0 ; inum < item.size(); inum++)
    {
        for(unsigned int ivalue = 0; ivalue < item[inum].batter.size(); ivalue++)
        {
            for(unsigned int icheck = 0; icheck < item[inum].topping.size(); icheck++)
            {
                cout<<left<<setw(ispace-2)<<item[inum].id
                    <<setw(ispace)<<item[inum].name
                    <<setw(ispace)<<item[inum].ppu
                    <<setw(ispace)<<item[inum].type
                    <<setw(ispace+3)<<item[inum].batter[ivalue].id
                    <<setw(ispace+4)<<item[inum].batter[ivalue].type
                    <<setw(ispace+2)<<item[inum].topping[icheck].id
                    <<setw(ispace)<<item[inum].topping[icheck].type<<endl;
            }
        }
    }
}

void from_json(vector<items> &item, json &j)
{
    for(unsigned int inum = 0; inum < j.at("items").at("item").size(); inum++ )
    {
        batters tbatter;
        toppings ttopping;
        items titem;

        titem.id = j["items"]["item"][inum].at("id").get<int>();
        titem.ppu = j["items"]["item"][inum].at("ppu").get<float>();
        titem.name = j["items"]["item"][inum].at("name").get<std::string>();
        titem.type = j["items"]["item"][inum].at("type").get<std::string>();

        for(unsigned int icheck = 0 ; icheck < j["items"]["item"][inum].at("batters").at("batter").size() ; icheck++ )
        {
            tbatter.id = stoi(j["items"]["item"][inum]["batters"]["batter"][icheck].at("id").get<std::string>());
            tbatter.type = j["items"]["item"][inum]["batters"]["batter"][icheck].at("type").get<std::string>();

            titem.batter.push_back(tbatter);
        }

        for(unsigned int icheck = 0 ; icheck < j["items"]["item"][inum].at("toppings").at("topping").size() ; icheck++ )
        {
           ttopping.id = stoi(j["items"]["item"][inum]["toppings"]["topping"][icheck].at("id").get<std::string>());
           ttopping.type = j["items"]["item"][inum]["toppings"]["topping"][icheck].at("type").get<std::string>();

            titem.topping.push_back(ttopping);
        }

        item.push_back(titem);
    }

}

void sortID(vector<items> &i)
{
    items titem;
    int ismall(0);
    for(unsigned int iloop = 0 ; iloop < i.size()-1; iloop++)
    {
        for(unsigned int inum = iloop + 1; inum < i.size(); inum++)
        {
            if(i[ismall].id > i[inum].id)
            {
                ismall = inum;
            }
        }
        titem = i[ismall];
        i.erase(i.begin()+ismall);
        i.insert(i.begin()+iloop, titem);
    }
}

void sortPpu(vector<items> &i)
{
    items titem;
    int ismall(0);
    for(unsigned int iloop = 0 ; iloop < i.size()-1; iloop++)
    {
        for(unsigned int inum = iloop + 1; inum < i.size(); inum++)
        {
            if(i[ismall].ppu > i[inum].ppu)
            {
                ismall = inum;
            }
        }
        titem = i[ismall];
        i.erase(i.begin()+ismall);
        i.insert(i.begin()+iloop, titem);
    }
}

void sortType(vector<items> &i)
{
    items titem;
    int ismall(0);
    for(unsigned int iloop = 0 ; iloop < i.size()-1; iloop++)
    {
        for(unsigned int inum = iloop + 1; inum < i.size(); inum++)
        {
            if(i[ismall].type > i[inum].type)
            {
                ismall = inum;
            }
        }
        titem = i[ismall];
        i.erase(i.begin()+ismall);
        i.insert(i.begin()+iloop, titem);
    }
}

void sortName(vector<items> &i)
{
    items titem;
    int ismall(0);
    for(unsigned int iloop = 0 ; iloop < i.size()-1; iloop++)
    {
        for(unsigned int inum = iloop + 1; inum < i.size(); inum++)
        {
            if(i[ismall].name > i[inum].name)
            {
                ismall = inum;
            }
        }
        titem = i[ismall];
        i.erase(i.begin()+ismall);
        i.insert(i.begin()+iloop, titem);
    }
}

void sortIBatter(vector<items> &i)
{
    batters titem;
    for(unsigned int iloop = 0 ; iloop < i.size(); iloop++)
    {
        int ismall(0);
        for(unsigned int inum = 0 ; inum < i[iloop].batter.size()-1; inum++)
        {
            for(unsigned int icheck = inum+1 ; icheck < i[iloop].batter.size(); icheck++)
            {
                if( i[iloop].batter[ismall].id > i[iloop].batter[icheck].id)
                {
                    ismall = icheck;
                }
            }
            titem = i[iloop].batter[ismall];
            i[iloop].batter.erase(i[iloop].batter.begin()+ismall);
            i[iloop].batter.insert(i[iloop].batter.begin()+inum, titem);
        }
    }
}

void sortNBatter(vector<items> &i)
{
    batters titem;
    for(unsigned int iloop = 0 ; iloop < i.size(); iloop++)
    {
        int ismall(0);
        for(unsigned int inum = 0 ; inum < i[iloop].batter.size()-1; inum++)
        {
            for(unsigned int icheck = inum+1 ; icheck < i[iloop].batter.size(); icheck++)
            {
                if( i[iloop].batter[ismall].type > i[iloop].batter[icheck].type)
                {
                    ismall = icheck;
                }
            }
            titem = i[iloop].batter[ismall];
            i[iloop].batter.erase(i[iloop].batter.begin()+ismall);
            i[iloop].batter.insert(i[iloop].batter.begin()+inum, titem);
        }
    }
}

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

    from_json(item,j);

    sortID(item);
    display(item);
    sortName(item);
    cout<<endl;
    display(item);
    sortType(item);
    cout<<endl;
    display(item);


    std::ofstream outfile;//output to the file
    {
        outfile.open("Table.txt");
        if(outfile.fail())
        {
            std::cout<<"sorry file not found"<<std::endl;
        }
        else
        {
            int ispace(10);
            outfile<<left<<setw(ispace-2)<<"id"<<setw(ispace)<<"name"<<setw(ispace)<<"ppu"<<setw(ispace)
                    <<"type"<<setw(ispace+3)<<"batter#"<<setw(ispace+3)<<"batter"<<setw(ispace+3)<<"topping#"<<setw(ispace)<<"topping"<< endl<<endl;
            for(unsigned int inum = 0 ; inum < item.size(); inum++)
            {
                for(unsigned int ivalue = 0; ivalue < item[inum].batter.size(); ivalue++)
                {
                    for(unsigned int icheck = 0; icheck < item[inum].topping.size(); icheck++)
                    {
                        outfile<<left<<setw(ispace-2)<<item[inum].id
                            <<setw(ispace)<<item[inum].name
                            <<setw(ispace)<<item[inum].ppu
                            <<setw(ispace)<<item[inum].type
                            <<setw(ispace+3)<<item[inum].batter[ivalue].id
                            <<setw(ispace+4)<<item[inum].batter[ivalue].type
                            <<setw(ispace+2)<<item[inum].topping[icheck].id
                            <<setw(ispace)<<item[inum].topping[icheck].type<<endl;
                    }
                }
            }
        }
        outfile.close();
    }


    return 0;
}

