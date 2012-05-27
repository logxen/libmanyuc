#ifndef __I2C_ACCELL_
#define __I2C_ACCELL_

// Author: Manuel Soldini - 2010
// Modified by: Margarita Manterola - 2012

#include <stdint.h>
#include "libmanyuc.h"

const int addr = 0x3A;

class Accelerometer {

private:
    I2C i2c;

    void calibrate();
    void setup();
    uint8_t check();
    //float _x8,  _y8,  _z8;
    //float _x10, _y10, _z10;
    int readAccel10(uint8_t, uint8_t);
    uint8_t readAccel8(uint8_t);
    float calculate10Bit(int);
    float calculate8Bit(uint8_t);

public:
    Accelerometer(uint8_t port);
    /*Pre: Se debe haber pedido un vector del tipo flotante de al menos 3 elementos*/
    /*Pos: Se almacena el valor de g para x,y,z en el vector recibido*/
    void get8BitVector(float *);
    /*Pre: Se debe haber pedido un vector del tipo flotante de al menos 3 elementos*/
    /*Pos: Se almacena el valor de g para x,y,z en el vector recibido*/
    void get10BitVector(float *);
    float getXAxis8();
    float getYAxis8();
    float getZAxis8();
    float getXAxis10();
    float getYAxis10();
    float getZAxis10();

};

#endif // __I2C_ACCEL_
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
