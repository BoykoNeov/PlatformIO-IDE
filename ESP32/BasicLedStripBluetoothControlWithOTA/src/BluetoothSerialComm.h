#include <BluetoothSerial.h>

extern BluetoothSerial SerialBT;

#if !defined(bluetoothcommands)
#define bluetoothcommands

char* ReadBluetooth();
void WriteBluetooth(char* message);

#endif // bluetoothcommands


