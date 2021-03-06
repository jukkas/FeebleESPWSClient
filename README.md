# Feeble ESP WebSocket Client (fwsc)

Arduino library that implements parts of the WebSocket client protocol
(https://tools.ietf.org/html/rfc6455) for ESP8266 and ESP32 microcontrollers.

Designed to be light weight and work with parse-esp to implement ParseLiveQuery.
Surprisingly has also worked against some other servers too.
Might be usable elsewhere, but...

Definitely not compliant with the RFC6455. Most definitely insecure.
Some limitations vs proper WS client:
- Can only connect to TLS servers
- Does not verify server TLS certificate -> insecure!
- Cheats in WS handshake: Always uses the same `Sec-WebSocket-Key`, does not check server response -> insecure!
- Cheats with "Masking keys": Sets key as zero -> insecure!
- No Subprotocols
- Supports only text frames (no binary)
- No continuation frames

So this probably only works with the one kind of server I have tested against, i.e. Nginx+Node ws,
and with very limited set of applications.

TODO: Even basic documentation... Or more comments in code...