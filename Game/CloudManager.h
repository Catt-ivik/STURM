// +++ CloudManager class for the program STURM +++
//
// Takes control of the clouds creation, destroying and
// attributes setting.
//


#ifndef STURM_CLOUDMANAGER
#define STURM_CLOUDMANAGER

#include "Cloud.h"

#include <vector>

class CloudManager
{
public:

    CloudManager();
    ~CloudManager();

    void Update();
    void Render();

    void Reset();
    
    float cloudSpeed;

private:

    void CreateCloud();

    int minAltitude;
    int maxAltitude;

    std::vector <std::shared_ptr<Cloud>> clouds;
    int cloudNumber;

    float xSeparation;
};

#endif // STURM_CLOUDMANAGER