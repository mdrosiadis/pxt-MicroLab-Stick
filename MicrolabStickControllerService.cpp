#include "MicroBitConfig.h"
#include "MicrolabStickControllerService.h"
#include "MicroBitEvent.h"

#if CONFIG_ENABLED(DEVICE_BLE)
//================================================================
#if MICROBIT_CODAL
//================================================================

const uint8_t  MicrolabStickControllerService::service_base_uuid[ 16] =
{ 0xb2,0x12,0x00,0x00,0x26,0x79,0x30,0xda,0xa2,0x6e,0x02,0x73,0xb6,0x04,0x38,0x49 };


const uint16_t MicrolabStickControllerService::serviceUUID               = 0xb5e6;
const uint16_t MicrolabStickControllerService::charUUID[ mbbs_cIdxCOUNT] = { 0xb5e7 };


MicrolabStickControllerService::MicrolabStickControllerService(BLEDevice &_ble) :
        ble(_ble)
{
    // Initialise our characteristic values.
    memset(&buffer, 0, sizeof(buffer));
    
    // Register the base UUID and create the service.
    RegisterBaseUUID( service_base_uuid);
    CreateService( serviceUUID);

    CreateCharacteristic( mbbs_cIdxDATA, charUUID[ mbbs_cIdxDATA],
                         (uint8_t *)&buffer,
                         sizeof(buffer), sizeof(buffer),
                         microbit_propWRITE);
}

/**
  * A callback function for whenever a Bluetooth device writes to our RX characteristic.
  */
void MicrolabStickControllerService::onDataWritten(const microbit_ble_evt_write_t *params)
{
    if (params->handle == valueHandle( mbbs_cIdxDATA))
    {
        uint16_t bytesWritten = params->len;
        const uint8_t *data = params->data;

        throttle = (int)data[0]-128;
        steer = (int)data[1]-128;

        MicroBitEvent(999, 999);
    }
}

void MicrolabStickControllerService::onDataRead( microbit_onDataRead_t *params){
}

int MicrolabStickControllerService::getThrottle() {
    return throttle;
}

int MicrolabStickControllerService::getSteer() {
    return steer;
}

//================================================================
#else // MICROBIT_CODAL
//================================================================

MicrolabStickControllerService::MicrolabStickControllerService(BLEDevice &_ble) : {
}
#if  0
#include "ble/UUID.h"

MicrolabStickControllerService::MicrolabStickControllerService(BLEDevice &_ble) :
        ble(_ble)
{
    GattCharacteristic  txCharacteristic(BLEHF2TxCharacteristicUUID, (uint8_t *)&txCharacteristicMessage, 0,
    sizeof(txCharacteristicMessage), GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY);

    // Initialise our characteristic values.
    memset(&txCharacteristicMessage, 0, sizeof(txCharacteristicMessage));

    // Set default security requirements
    txCharacteristic.requireSecurity(SecurityManager::MICROBIT_BLE_SECURITY_LEVEL);

    // setup GATT table
    GattCharacteristic *characteristics[] = {&txCharacteristic};
    GattService service(BLEHF2ServiceUUID, characteristics, sizeof(characteristics) / sizeof(GattCharacteristic *));
    ble.addService(service);

    // retreive handles
    txCharacteristicHandle = txCharacteristic.getValueHandle();

    // initialize data
    ble.gattServer().write(txCharacteristicHandle,(uint8_t *)&txCharacteristicMessage, sizeof(txCharacteristicMessage));
}


const uint8_t  MicrolabStrickServiceUUID[] = {
    0xb1,0x12,0xf5,0xe6,0x26,0x79,0x30,0xda,0xa2,0x6e,0x02,0x73,0xb6,0x04,0x38,0x49
};

const uint8_t  MicrolabStrickCharacteristicUUID[] = {
    0xb1,0x12,0xf5,0xe6,0x26,0x79,0x30,0xda,0xa2,0x6e,0x02,0x73,0xb6,0x04,0x38,0x4a
};
#endif

//================================================================
#endif // MICROBIT_CODAL
//================================================================
//
#endif // BLE_ENABLED
