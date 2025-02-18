//% weight=0 color=#db9909  icon="\uf124" block="MicroLab Stick"
namespace MicrolabStick {


    //% blockId=start_stick_service block="Start Microlab Stick service"
    //% parts="Microlab Stick" weight=110 blockGap=8
    //% shim=MicrolabStick::startMicrolabStickControllerService
    export function startMicrolabStickControllerService(): void {
        return;
    }

    //% parts="Microlab Stick" blockGap=8
    //% weight=90 blockId=on_control_packet_received block="on control packet received"
    //% shim=MicrolabStick::onControllerPacketReceived
    export function onControllerPacketReceived(body: () => void): void {
        return;
    }
    
    //% parts="Microlab Stick" blockGap=8
    //% weight=10 blockId=get_left_motor block="get left motor percentage"
    export function getLeftMotorPercentage(): number {
        return getSteer() < 0 
        ? getThrottle() - Math.map(Math.abs(getSteer()), 0, 100, 0, getThrottle())
        : getThrottle();
    }

    //% parts="Microlab Stick" blockGap=8
    //% weight=10 blockId=get_right block="get right motor percentage"
    export function getRightMotorPercentage(): number {
        return getSteer() > 0 
        ? getThrottle() - Math.map(Math.abs(getSteer()), 0, 100, 0, getThrottle())
        : getThrottle();
    }
}

