# Optional BLE pairing PIN

On ESP32 / ESP32-S3 builds using NimBLE, configure a six-digit PIN in the web settings or the USB serial configuration tool. Leading zeroes are preserved. An empty PIN keeps the existing open connection behavior. Existing configurations migrate with protection disabled.

Serial setup example (replace the example PIN with your own):

```text
setup
bt pin 123456
save
reboot
```

To disable protection, use `bt pin off`, then save and reboot.

Changes apply on restart. Changing or disabling the PIN revokes stored device bonds. Forget the previous pairing on the phone and pair again. Bonded clients may reconnect without entering the PIN again while the PIN remains unchanged.

When enabled, KISS traffic is gated on an encrypted, authenticated BLE connection. Malformed nonempty PIN settings or failure to update bond policy disable BLE instead of silently allowing an open connection.

This setting applies only to NimBLE; nRF52 Bluefruit and Bluetooth Classic are unchanged. It protects BLE access, not configuration access: the PIN remains part of the saved/exported configuration, which must be treated as sensitive.
