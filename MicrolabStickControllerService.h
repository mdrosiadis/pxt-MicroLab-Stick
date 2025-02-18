#ifndef MICROLAB_STICK_SERVICE_H
#define MICROLAB_STICK_SERVICE_H

#include "MicroBitConfig.h"



//#if CONFIG_ENABLED(DEVICE_BLE)
#if 1

#include "EventModel.h"
#include "pxt.h"

// UUIDs for our service and characteristics
extern const uint8_t  MicrolabStrickServiceUUID[];
extern const uint8_t  MicroLabStickDataCharacteristicUUID[];


//================================================================
#if MICROBIT_CODAL
//================================================================

#include "MicroBit.h"
#include "MicroBitBLEManager.h"
#include "MicroBitBLEService.h"

class MicrolabStickControllerService : public MicroBitBLEService
{
    public:

    /**
      * Constructor.
      * Create a representation of the TemperatureService
      * @param _ble The instance of a BLE device that we're running on.
      */
    MicrolabStickControllerService(BLEDevice &_ble);
    int getThrottle();
    int getSteer();
    
    /**
      * Callback. Invoked when any of our attributes are written via BLE.
      */
    void onDataWritten( const microbit_ble_evt_write_t *params);

    /**
      * Callback. Invoked when any of our attributes are read via BLE.
      * Set  params->data and params->length to update the value
      */
    void onDataRead( microbit_onDataRead_t *params);

    /**
    * Sends text
    void sendSerial(const char *data, int len, bool isError);
    */

    private:

    // Bluetooth stack we're running on.
    BLEDevice &ble;
    int throttle, steer;
        
    uint8_t buffer[2];
    
    // Index for each charactersitic in arrays of handles and UUIDs
    typedef enum mbbs_cIdx
    {
        mbbs_cIdxDATA,
        mbbs_cIdxCOUNT
    } mbbs_cIdx;
    
    // UUIDs for our service and characteristics
    static const uint8_t  service_base_uuid[ 16];
    static const uint8_t  char_base_uuid[ 16];
    static const uint16_t serviceUUID;
    static const uint16_t charUUID[ mbbs_cIdxCOUNT];
    
    // Data for each characteristic when they are held by Soft Device.
    MicroBitBLEChar      chars[ mbbs_cIdxCOUNT];

    public:
    
    int              characteristicCount()          { return mbbs_cIdxCOUNT; };
    MicroBitBLEChar *characteristicPtr( int idx)    { return &chars[ idx]; };
};

//================================================================
#else // MICROBIT_CODAL
//================================================================
#include "ble/BLE.h"

class MicrolabStickControllerService : public MicroBitBLEService
    public:

    /**
      * Constructor.
      * Create a representation of the TemperatureService
      * @param _ble The instance of a BLE device that we're running on.
      */
    MicrolabStickControllerService(BLEDevice &_ble);
}

#if 0
class BLEHF2Service
{
    public:

    /**
      * Constructor.
      * Create a representation of the TemperatureService
      * @param _ble The instance of a BLE device that we're running on.
      */
    BLEHF2Service(BLEDevice &_ble);

    /**
    * Sends text
    */
    void sendSerial(const char *data, int len, bool isError); 

    private:

    // Bluetooth stack we're running on.
    BLEDevice &ble;

    // memory for buffers.
    BLEHF2Packet txCharacteristicMessage;

    // Handles to access each characteristic when they are held by Soft Device.
    GattAttribute::Handle_t txCharacteristicHandle;
};
#endif

//================================================================
#endif // MICROBIT_CODAL
//================================================================

#endif // BLE_ENABLED
#endif
