# BLE PIN and OLED brightness — development change

Target: LilyGo T-Beam 433 MHz 1W, ESP32-S3, SH1106.
Base: KJ7NYE/LoRa_FieldOps_APRS_Tracker c2fdfa9174e9bd2d03e0d72c5c92245f642a9e78.

## Settings

The web configuration and the bundled serial_config.html add:
- SH1106 OLED brightness 1–100%. This controls contrast, not a calibrated luminance percentage. Other display controller paths are unchanged.
- Six-digit BLE PIN, including leading zeros. Empty disables PIN protection. Applies to NimBLE ESP32/ESP32-S3; nRF52 and Classic Bluetooth are not extended.
- The existing LED indicator switch already disables the GPIO18 status LED. Power/charge/GNSS LEDs are outside this change.

Old configurations retain full brightness and open BLE until a PIN is configured.
Save and restart to apply PIN or brightness. A PIN change revokes previous bonds;
forget the old pairing in Android, then pair again. Bond keys allow subsequent
reconnections without entering the PIN again. PIN is stored in the local device
configuration and security preferences; configuration exports contain it.

Serial console example (replace the illustrative PIN with your own):

```
setup
bt pin 638205
display brightness 20
display led off
save
reboot
```

`bt pin off` disables PIN protection after saving and restarting.

## Security behavior

MITM-authenticated encrypted BLE pairing with bonding is requested. GATT reads
and writes require authentication when enabled. Notifications and queued KISS
transmission are blocked until authentication. Only one active client is used.
Bad nonempty PIN configuration disables BLE instead of silently opening access.
Changing a PIN deletes previous bond keys before advertising starts. An inability
to open security storage or revoke old keys disables BLE.

## Validation

- Native C++ tests for invalid PINs, leading zeros and brightness limits passed.
- JavaScript syntax checks for both configuration interfaces passed.
- A full target build and hardware testing are required before release.

On-device acceptance tests still required: correct and incorrect PIN; reconnect
after phone and tracker restart; change PIN and reject an old bond; both KISS
directions in Graywolf and APRSConnect; brightness 1/20/100 and persistence;
LED off; original config migration; malformed imported PIN; PIN disabled.

Build: `python -m platformio run -e tbeam_433_1w_aprs`.
