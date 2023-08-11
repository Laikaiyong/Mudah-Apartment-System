#pragma once
#include <iostream>

using namespace std;

class Property
{
    string adsId;
    string propName;
    int completionYear;
    float monthlyRent;
    string location;
    string propertyType;
    int rooms;
    int parking;
    int bathroom;
    int size;
    string furnished;
    string facilities;
    string additionalFacilities;
    string region;
    string rentStatus;

public:
    Property(){};

    Property(string adsId, string propName, int completionYear, float monthlyRent, string location, string propertyType, int rooms, int parking, int bathroom, int size, string furnished, string facilities, string additionalFacilities, string region, string rentStatus)
    {
        this->adsId = adsId;
        this->propName = propName;
        this->completionYear = completionYear;
        this->monthlyRent = monthlyRent;
        this->location = location;
        this->propertyType = propertyType;
        this->rooms = rooms;
        this->parking = parking;
        this->bathroom = bathroom;
        this->size = size;
        this->furnished = furnished;
        this->facilities = facilities;
        this->additionalFacilities = additionalFacilities;
        this->region = region;
        this->rentStatus = rentStatus;
    }

    friend std::ostream &operator<<(std::ostream &os, const Property &property)
    {
        // Code to output the object's data to the ostream
        os << "Property Details:" << endl;
        os << "Ads ID: " << property.adsId << endl;
        os << "Property Name: " << property.propName << endl;
        os << "Completion Year: " << property.completionYear << endl;
        os << "Monthly Rent: " << property.monthlyRent << endl;
        os << "Location: " << property.location << endl;
        os << "Property Type: " << property.propertyType << endl;
        os << "Rooms: " << property.rooms << endl;
        os << "Parking: " << property.parking << endl;
        os << "Bathroom: " << property.bathroom << endl;
        os << "Size: " << property.size << endl;
        os << "Furnished: " << property.furnished << endl;
        os << "Facilities: " << property.facilities << endl;
        os << "Additional Facilities: " << property.additionalFacilities << endl;
        os << "Region: " << property.region << endl;
        os << "Rent Status: " << property.rentStatus << endl;
        return os;
    }

    string getAdsId()
    {
        return adsId;
    }

    void setAdsId(string adsId)
    {
        this->adsId = adsId;
    }

    string getPropName()
    {
        return propName;
    }

    void setPropName(string propName)
    {
        this->propName = propName;
    }

    int getCompletionYear()
    {
        return completionYear;
    }

    void setCompletionYear(int completionYear)
    {
        this->completionYear = completionYear;
    }

    float getMonthlyRent()
    {
        return monthlyRent;
    }

    void setMonthlyRent(float monthlyRent)
    {
        this->monthlyRent = monthlyRent;
    }

    string getLocation()
    {
        return location;
    }

    void setLocation(string location)
    {
        this->location = location;
    }

    string getPropertyType()
    {
        return propertyType;
    }

    void setPropertyType(string propertyType)
    {
        this->propertyType = propertyType;
    }

    int getRooms()
    {
        return rooms;
    }

    void setRooms(int rooms)
    {
        this->rooms = rooms;
    }

    int getParking()
    {
        return parking;
    }

    void setParking(int parking)
    {
        this->parking = parking;
    }

    int getBathroom()
    {
        return bathroom;
    }

    void setBathroom(int bathroom)
    {
        this->bathroom = bathroom;
    }

    int getSize()
    {
        return size;
    }

    void setSize(int size)
    {
        this->size = size;
    }

    string getFurnished()
    {
        return furnished;
    }

    void setFurnished(string furnished)
    {
        this->furnished = furnished;
    }

    string getFacilities()
    {
        return facilities;
    }

    void setFacilities(string facilities)
    {
        this->facilities = facilities;
    }

    string getAdditionalFacilities()
    {
        return additionalFacilities;
    }

    void setAdditionalFacilities(string additionalFacilities)
    {
        this->additionalFacilities = additionalFacilities;
    }

    string getRegion()
    {
        return region;
    }

    void setRegion(string region)
    {
        this->region = region;
    }

    string getRentStatus()
    {
        return rentStatus;
    }

    void setRentStatus(string rentStatus)
    {
        this->rentStatus = rentStatus;
    }
};