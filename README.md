# 8-bit Song Maker for Buzzer

A small Python-to-C++ workflow for creating simple melodies for a passive buzzer.

The goal is a deliberately crunchy, lo-fi 8-bit sound — like a tiny Game Boy-style speaker being pushed into an alarm-like tone. It is not an exact Game Boy sound emulator; the character comes from simple square-wave tones, short note timing, and rests.

## Features

- Create melodies from simple note-and-duration input.
- Generate Arduino-compatible C++ code.
- Convert MIDI files into buzzer-friendly note data.
- Designed for passive buzzers.
- Beginner-friendly for Arduino, ESP32, and Raspberry Pi Pico projects.
- Windows CMD and Linux terminal instructions included.

## Workflow

```text
Python song maker / MIDI converter
              |
              v
       Generated C++ data
              |
              v
       Arduino / ESP32 / Pico
              |
              v
         Passive buzzer
```

## Requirements

- Python 3
- Arduino IDE or another compatible Arduino/C++ environment
- A passive buzzer
- An Arduino-compatible board, ESP32, or Raspberry Pi Pico
- `mido` is required only for the MIDI converter:
  `python -m pip install mido`

## Quick Start

### Windows CMD

From the repository root:

```cmd
python src/song_maker.py
```

If `python` is not recognized:

```cmd
py src/song_maker.py
```

See [Windows CMD instructions](docs/CMD.txt).

### Linux

From the repository root:

```bash
python3 src/song_maker.py
```

See [Linux instructions](docs/LINUX.txt).

## Song Format

Enter notes as:

```text
NOTE:DURATION
```

Example:

```text
C4:180 D4:180 E4:180 G4:300 R:120 E4:180 C4:400
```

- `C4`, `F#4`, `A5`, etc. are notes.
- Duration is in milliseconds.
- `R` means rest/silence.
- Separate notes with spaces.

The Python program asks for the buzzer GPIO and output filename, then creates a ready-to-edit C++ sketch.

## MIDI Conversion

The project also includes a MIDI-to-buzzer converter.

Install the dependency:

```bash
python -m pip install mido
```

Then convert the included example:

```bash
cd examples/virtual_insanity
python ../../src/chiptune_converter.py ../../music/Virtual_Insanity.mid
```

The converter generates `song.h` in the current directory.

## Example Hardware

Connect a passive buzzer between the selected GPIO and GND. The basic example uses:

```cpp
const int BUZZER_PIN = 15;
```

Change this pin if your board uses another GPIO.

## Project Structure

```text
8-bit-song-maker-for-buzzer/
├── README.md
├── LICENSE
├── .gitignore
├── src/
│   ├── song_maker.py
│   └── chiptune_converter.py
├── examples/
│   ├── basic/
│   │   └── buzzer_player.cpp
│   └── virtual_insanity/
│       ├── code.ino
│       └── song.h
├── music/
│   └── Virtual_Insanity.mid
├── docs/
│   ├── CMD.txt
│   └── LINUX.txt
└── tools/
    └── code.txt
```

### Directories

- `src/` — Python tools.
- `examples/basic/` — simple passive-buzzer example.
- `examples/virtual_insanity/` — generated Arduino example for the included MIDI file.
- `music/` — MIDI source files.
- `docs/` — platform-specific instructions.
- `tools/` — useful command snippets.

## Sound Style

This project intentionally keeps the audio simple. A passive buzzer driven by square-wave tones naturally produces a rough electronic sound.

The intended character is:

> tiny speaker + square waves + short notes + crunchy 8-bit character + alarm-like energy

It is intentionally lo-fi rather than hi-fi.

## Board Compatibility

The generated code targets Arduino-style environments and can be adapted for:

- Arduino boards
- ESP32
- Raspberry Pi Pico with an Arduino-compatible core

The exact `tone()` implementation can vary between board cores, so small changes may occasionally be needed.

## Future Plans

- BPM and tempo support
- More note/octave support
- Song save/load files
- Transpose
- More buzzer sound effects
- Simple GUI
- Direct Arduino sketch export

## License

MIT License.
