#include <iostream>
#include <sstream>
#include <fstream>
#include "../entity/property.h"

using namespace std;

Property *readFile(int rowSize)
{
    Property *propertyList = new Property[rowSize];
    Property property;
    string data[13];

    const string filepath = "file/mudah-apartment-kl-selangor.csv";
    ifstream file;
    string line = "";
    int i;
    int j = 0;
    string temp;
    string item;
    string nextitem;

    file.open(filepath);
    getline(file, line);

    while (getline(file, line))
    {
        i = 0;
        stringstream ss(line);

        while (getline(ss, item, ','))
        {
            if (item.front() == '"')
            {
                // handle quoted dield spanning multiple lines
                while (getline(ss, nextitem, ','))
                {
                    item += "," + nextitem;
                    if (nextitem.back() == '"')
                    {
                        break;
                    };
                };
            };
            data[i++] = item;
        };

        property.setAdsId(data[0]);
        property.setPropName(data[1]);
        property.setCompletionYear((data[2].empty()) ? -1 : stoi(data[2]));

        if (data[3].empty())
        {
            property.setMonthlyRent(-1);
        }
        else
        {
            temp = data[3].substr(3, data[3].length() - 13);
            if (temp.length() > 4)
            {
                temp = temp.at(0) + temp.substr(2, 3);
            }
            property.setMonthlyRent(stof(temp));
        }

        property.setLocation((data[4].empty()) ? "-" : data[4]);
        property.setPropertyType((data[5].empty()) ? "-" : data[5]);
        try
        {
            property.setRooms((data[6].empty()) ? -1 : stoi(data[6]));
        }
        catch (exception)
        {
            property.setRooms(10);
        }

        property.setParking((data[7].empty()) ? -1 : stoi(data[7]));
        property.setBathroom((data[8].empty()) ? -1 : stoi(data[8]));

        if (data[9].empty())
        {
            property.setSize(-1);
        }
        else
        {
            temp = data[9].substr(0, data[9].length() - 7);
            property.setSize(stoi(temp));
        }

        property.setFurnished((data[10].empty()) ? "-" : data[10]);
        property.setFacilities((data[11].empty()) ? "-" : data[11]);
        property.setAdditionalFacilities((data[12].empty()) ? "-" : data[12]);
        property.setRentStatus("Available");

        propertyList[j++] = property;
    }
    file.close();
    cout << "Successfully fetch the Data" << endl;
    return propertyList;
}