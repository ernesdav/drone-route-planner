#ifndef WAYPOINT_H
#define WAYPOINT_H

#include<string>

struct Waypoint
{
    int id;
    double latitude;
    double longitude;
    std::string name;

    Waypoint(int _waypointId, double _latitude, double _longitude, std::string _waypointName) : 
        id(_waypointId),
        latitude(_latitude),
        longitude(_longitude),
        name(_waypointName)    
    {}

};


#endif