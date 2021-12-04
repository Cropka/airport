#ifndef GATEWAY_H
#define GATEWAY_H

#include "resource.h"

class gateway : public resource
{
public:    
    gateway(int _id, int _positionX, int _positionY): resource(nullptr) {
        type="gateway";
        positionX=_positionX;
        positionY=_positionY;
        id=_id;
    }
};

#endif // GATEWAY_H
