# AACHARYA
Your Pocket Ayurvedic Dincharya Assistant
# Aacharya Keychain

A pocket-sized AI companion built on IIT Bombay's **AyurParam** model.
Ask by voice in Hindi or English. Aacharya suggests diet and lifestyle routines (Dinacharya and Ritucharya) based on your Prakriti, the season and the time of day.

Every answer is designed to pass a safety layer. Red-flag symptoms are referred to a doctor, and replies come with classical-text citations.

> **Status: early prototype.** Only the hardware test firmware exists today. The voice pipeline, safety layer and citations are planned (see Roadmap).

## What it does (target)

- Voice question in Hindi or English
- Routine suggestions by Prakriti, season and time of day
- Safety layer: red-flag symptoms go to a doctor, not to a routine
- Classical-text citation with every answer
- Round display and touch pad on a keychain body

## Hardware

| Part | Role |
| --- | --- |
| ESP32-S3 Super Mini | Main board |
| GC9A01 round display | Screen |
| INMP441 | I2S microphone |
| MAX98357A + 4 ohm 40mm speaker | Audio out |
| TTP223 | Touch pad |
| TP4056 + LiPo 1000mAh | Charging and battery |
| 1N5819 diode, 470uF capacitor | Power protection and smoothing |

## Wiring

| Device pin | ESP32-S3 pin |
| --- | --- |
| Display SCL | GPIO8 |
| Display SDA | GPIO9 |
| Display DC | GPIO10 |
| Display CS | GPIO11 |
| Display RST | GPIO12 |
| Touch OUT | GPIO13 |
| Mic SCK | GPIO4 |
| Mic WS | GPIO2 |
| Mic SD | GPIO1 |
| Amp BCLK | GPIO7 |
| Amp LRC | GPIO6 |
| Amp DIN | GPIO5 |

### Power rails

- **3V3 rail:** ESP32 3V3 pad feeds display VCC, mic VDD and touch VCC.
- **GND rail:** ESP32 GND pad feeds every GND. Mic L/R goes to GND (left channel).
- **BAT+ rail (3.7-4.2 V):** only TP4056 OUT+, amp VIN, the 470uF capacitor and the diode. Nothing else.
- **ESP32 5V pad** gets BAT+ through the 1N5819 diode (silver bar side to the 5V pad).
- **Capacitor:** long leg (+) to VIN, short leg (-) to GND.
- **Battery:** LiPo + red to TP4056 B+, black to B-. TP4056 OUT+ to BAT+, OUT- to GND.
- **Speaker:** amp SPK+ and SPK- to the speaker + and -.

**Check the LiPo plug polarity and the capacitor leg before powering on. Test on USB first, add the battery last.**

## Firmware setup

1. Install Arduino IDE and the ESP32 board package **3.x**.
2. Select board **ESP32S3 Dev Module** and enable **USB CDC On Boot**.
3. Install the library **GFX Library for Arduino** from Library Manager.
4. Put `pins.h` and `Aacharya.ino` in a folder named `Aacharya`.
5. Upload. Touch the pad: the display shows the mic level and the speaker beeps.

## Project files

```
Aacharya/
  pins.h        pin map
  Aacharya.ino  hardware test (display, touch, mic, speaker)
```

## Roadmap

- [x] Wiring and pin map
- [x] Hardware test firmware (untested on all boards)
- [ ] Record voice and send it to the AyurParam backend
- [ ] Speech to text and text to speech in Hindi and English
- [ ] Prakriti, season and time-of-day logic
- [ ] Safety layer with doctor referral for red-flag symptoms
- [ ] Classical-text retrieval and citations

## Safety note

Aacharya gives general diet and lifestyle guidance only. It is not a doctor and does not diagnose, treat or prescribe. For any health problem, see a qualified doctor.

## Credits

- AyurParam by BharatGen (IIT Bombay)
- Built by Ashutosh Shri Mishra

## License

MIT