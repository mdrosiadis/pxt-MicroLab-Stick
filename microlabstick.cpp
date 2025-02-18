#include "pxt.h"
#include "pxtbase.h"
#include "MicrolabStickControllerService.h"
#include <cstddef>

using namespace pxt;

#define SINGLE(op) return fromDouble(::op(toDouble(x)));

namespace MicrolabStick {
	MicrolabStickControllerService *controllerService = NULL;

#if 0
    /**
    *  Starts the Bluetooth Microlab Stick Controller Service
    */
    //% blockId=start_stick_service block="Start Microlab Stick service"
    //% parts="Microlab Stick" weight=90 blockGap=8
#endif
	//%
    void startMicrolabStickControllerService() {
		if(NULL == controllerService)
			controllerService = new MicrolabStickControllerService(*uBit.ble);        
    }   

    /**
    *
    */
    //% weight=18 blockId=get_throttle block="get throttle"
    //% parts="Microlab Stick" weight=90 blockGap=8
	int getThrottle() {
		return controllerService->getThrottle();
	}

    /**
    *
    */
    //% weight=18 blockId=get_steer block="get steer"
    //% parts="Microlab Stick" weight=90 blockGap=8
	int getSteer() {
		return controllerService->getSteer();
	}

#if 0
    /**
    * Registers an event to be fired when a control packet is received
    */
    //% weight=18 blockId=on_control_packet_received block="on control packet received"
#endif
	//%
    void onControllerPacketReceived(Action body) {
		// TODO: fix magic numbers
    	registerWithDal(999, 999, body);
    }

}
