

#include "i2c_accelerometer.h"
#include "libmanyuc.h"

#define CALIBRATION 250

Pin led1(LED2);
I2C i2c(0);
//Serial pc1(0); 

const uint8_t REG_X8   = 0x06;
const uint8_t REG_Y8   = 0x07;
const uint8_t REG_Z8   = 0x08;

const uint8_t REG_X10L = 0x00;
const uint8_t REG_X10H = 0x01;

const uint8_t REG_Y10L = 0x02;
const uint8_t REG_Y10H = 0x03;

const uint8_t REG_Z10L = 0x04;
const uint8_t REG_Z10H = 0x05;

void Accelerometer::calibrate(){
    int8_t Xdata,Ydata,Zdata;
    int32_t Xcal,Xcalp, Ycal, Ycalp, Zcal, Zcalp;
    uint8_t Xcal_L, Xcal_H, Ycal_L,Ycal_H, Zcal_L, Zcal_H;
    uint8_t reg[3];
    reg[0] = 0x10; reg[1] = 0; reg[2] = 0;
    i2c.write(addr, reg, 3);
    //reg[0] = 0x11; reg[1] = 0;
    //i2c.write(addr, reg, 2);
    Xcal = Ycal = Zcal = 0;
    //pc1.printf("Calibrando...");
    //Timer t;
    //t.start();
    for(int i = 0; i < CALIBRATION ; i++){
        //pc1.printf("");
        //Lee X, Y, Z en 8bits
        Xdata = readAccel8(REG_X8);    
        Ydata = readAccel8(REG_Y8);
        Zdata = readAccel8(REG_Z8);
        //Calculata los valores de calibracion
        Xcal+= -2*Xdata;
        Ycal+= -2*Ydata;
        if (Zdata>65){Zcal+=(Zdata-64)*2;}
        else{Zcal+=(64-Zdata)*2;}
        
        Xcalp=Xcal;
        if (Xcalp<0) Xcalp +=2048;
        //Si calp es "positivo" it is assigned to cal variable
        //If Negative value then convert for 2's complement
        Ycalp=Ycal;
        if(Ycalp<0) Ycalp+=2048;
        Zcalp=Zcal;
        if(Zcalp<0) Zcalp+=2048;
        
        Xcal_L= (unsigned uint8_t)(Xcalp&0x00FF); //shift low byte to lower 8 bits
        Xcal_H= (unsigned uint8_t)((Xcalp&0xFF00)>>8); //shift high byte to upper 8 bits
        Ycal_L= (unsigned uint8_t)(Ycalp&0x00FF); //shift low byte to lower 8 bits
        Ycal_H= (unsigned uint8_t)((Ycalp&0xFF00)>>8); //shift high byte to upper 8 bits
        Zcal_L= (unsigned uint8_t)(Zcalp&0x00FF); //shift low byte to lower 8 bits
        Zcal_H= (unsigned uint8_t)((Zcalp&0xFF00)>>8); //shift high byte to upper 8 bits
        
        reg[0] = 0x10; reg[1] = Xcal_L; reg[2] = Xcal_H;
        i2c.write(addr, reg, 3);
        reg[0] = 0x12; reg[1] = Ycal_L; reg[2] = Ycal_H;
        i2c.write(addr, reg, 3);
        reg[0] = 0x14; reg[1] = Zcal_L; reg[2] = Zcal_H;
        i2c.write(addr, reg, 3); 
        wait(0.008);
        led1 = !led1;
    }
    //t.stop();
    //pc1.printf("COMPLETADO EN %f SEGUNDOS", t.read());
}


void Accelerometer::setup() {
    uint8_t cmd[2];
    cmd[0] = 0x16;  // registro 16h, Mode Control
    cmd[1] = 0x05;  // 2g + Measurement Mode
    i2c.write(addr, cmd, 2);
}

uint8_t Accelerometer::check() {
    uint8_t data, reg;
    reg = 0x16;
    i2c.write(addr, &reg, 1);
    wait(0.01);
    i2c.read(addr, &data, 1);
    return data;
}

Accelerometer::Accelerometer() {
    led1 = 1;
    i2c.frequency(100000); //freq de i2c 100KHz
    wait(0.02); // El acelerometro tarda 20ms en arrancar
    setup(); // se inicializa el acelerometro
    int respuesta = check(); // Para ver si se configuro hay que leer el registro 16.
    if (respuesta != 0x05) {
        while (1) {
            led1 = !led1;
            wait(0.5); // Si falla se queda blinkeando el led
        }
    }
    calibrate();
    led1 = 0; // indicador de estado encendido, listo para usar
}

uint8_t Accelerometer::readAccel8(uint8_t registro) {
    uint8_t data, reg;
    reg = registro;
    i2c.write(addr, &reg, 1);
    wait(0.004);
    i2c.read(addr,&data,1);
    return data;
}

int Accelerometer::readAccel10(uint8_t lowReg, uint8_t highReg) {
    uint8_t result[2];
    uint8_t reg = lowReg;
    i2c.write(addr, &reg, 1);
    wait(0.004);
    i2c.read(addr,result,2);
    int salida = (((int)result[1]) << 8) | ((int)result[0]);
    return salida;
}

float Accelerometer::calculate8Bit(uint8_t valor) {
    if (valor & (1 << 7)) {
        return (((255-valor) * 2.0) / (float)-127);
    } else {
        return ((valor * 2.0) / (float)127);
    } 
    
}//Te devuelve el valor en "g", en funcion de los datos del acelerometro, con su signo. 

float Accelerometer::calculate10Bit(int valor) {
    if (valor & (1 << 9)) {
        return (((1023-valor) * 2.0) / (float)-127);
    } else {
        return ((valor * 2.0) / (float)127);
    }
}//Te devuelve el valor en "g", en funcion de los datos del acelerometro, con su signo. 
//En el modo de 10bits siempre lee hasta 8g. Por eso la cuenta es algo diferente.

float Accelerometer::getXAxis8(){ return calculate8Bit(readAccel8(REG_X8)); }
float Accelerometer::getYAxis8(){ return calculate8Bit(readAccel8(REG_Y8)); }
float Accelerometer::getZAxis8(){ return calculate8Bit(readAccel8(REG_Z8)); }
float Accelerometer::getXAxis10(){ return calculate10Bit(readAccel10(REG_X10L, REG_X10H)); }
float Accelerometer::getYAxis10(){ return calculate10Bit(readAccel10(REG_Y10L, REG_Y10H)); }
float Accelerometer::getZAxis10(){ return calculate10Bit(readAccel10(REG_Z10L, REG_Z10H)); }

void Accelerometer::get8BitVector(float vec[]) {
    vec[0] = getXAxis8();
    vec[1] = getYAxis8();
    vec[2] = getZAxis8();
}

void Accelerometer::get10BitVector(float vec[]) {
    vec[0] = getXAxis10();
    vec[1] = getYAxis10();
    vec[2] = getZAxis10();
}


