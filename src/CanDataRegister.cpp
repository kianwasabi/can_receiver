#include "CanDataRegister.hpp"

#include <iostream>
#include <thread>

using namespace v0_1::commonapi;

/*Constructor.*/
CanDataRegister::CanDataRegister() {
    // Get the commonAPI runtime instance & create the vSOME/IP service
    runtime = CommonAPI::Runtime::get();
    SpeedRpmService = std::make_shared<SpeedSensorStubImpl>();
    // Register the vSOME/IP service
    SpeedSensor_Init();
}

/*Destructor*/
CanDataRegister::~CanDataRegister() {}

/* Registers the vSOME/IP service*/
void CanDataRegister::SpeedSensor_Init(){
    while(!runtime->registerService("local", "commonapi.SpeedSensor", SpeedRpmService, "SpeedRpmService")){
        std::cout << "Register SpeedRpm Service failed, trying again in 100 milliseconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Successfully Registered SpeedRpm Service!" << std::endl;
}

/* sets the attributes of vSOME/IP service*/
void CanDataRegister::sendDataToVSomeIP(uint32_t rpm, uint32_t speed) {
    // Set RPM and Speed values via the Speed_SensorStubImpl
    SpeedRpmService->setRpmAttribute(rpm);
    SpeedRpmService->setSpeedAttribute(speed);
}

