# 8-bit Song Maker for Buzzer

A small Python-to-C++ workflow for creating simple melodies for a passive buzzer.

The project focuses on a deliberately crunchy, lo-fi 8-bit sound using simple square-wave tones, short note timing, and rests. It is not an exact Game Boy sound emulator.

## Features

- Create melodies from simple note-and-duration input.
- Generate Arduino-compatible C++ code.
- Convert MIDI files into monophonic buzzer data.
- Handle MIDI tempo changes correctly.
- Preserve chronological note timing.
- Reduce MIDI polyphony to one playable buzzer note at a time.
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
- `mido` for the MIDI converter:

```bash
python -m pip install mido
```

## Quick Start

### Windows CMD

From the repository root:

```cmd
python src\song_maker.py
```

If `python` is not recognized:

```cmd
py src\song_maker.py
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

The Python program asks for the buzzer GPIO and output filename, then creates a C++ sketch.

## MIDI Conversion

The MIDI converter is intentionally monophonic because a single passive buzzer cannot reproduce a MIDI chord directly.

Install the dependency:

```bash
python -m pip install mido
```

Convert the included MIDI from the repository root:

```bash
python src/chiptune_converter.py music/Virtual_Insanity.mid -o src/song.h
```

The generated `song.h` is a build output, not source code, so it is intentionally **not stored in the repository**.

The converter:

1. Reads MIDI delta times using the file's ticks-per-beat value.
2. Applies MIDI tempo changes when calculating real time.
3. Keeps notes in chronological order.
4. Handles overlapping notes by selecting one active note for each time segment.
5. Writes Arduino-compatible `song.h` data.

## MIDI Example

The MIDI playback sketch is kept with the project source code:

```text
src/
└── code.ino
```

The source MIDI file is:

```text
music/Virtual_Insanity.mid
```

Generate the local header before opening the sketch in Arduino IDE:

```bash
python src/chiptune_converter.py music/Virtual_Insanity.mid -o src/song.h
```

Then open:

```text
src/code.ino
```

The sketch includes the generated `song.h`.

## Example Hardware

Connect a passive buzzer between the selected GPIO and GND.

The basic example uses:

```cpp
const int BUZZER_PIN = 15;
```

The MIDI converter uses GPIO 25 by default.

Change the pin if your board uses another GPIO.

## Examples

### Basic

Open `examples/basic/buzzer_player.cpp` and copy it into an Arduino sketch.

### MIDI

Open `src/code.ino`.

Generate `src/song.h` from the included MIDI first. The generated header is ignored by Git and does not need to be committed.

## Project Structure

```text
8-bit-song-maker-for-buzzer/
├── README.md
├── LICENSE
├── .gitignore
├── src/
│   ├── song_maker.py
│   ├── chiptune_converter.py
│   └── code.ino
├── examples/
│   └── basic/
│       └── buzzer_player.cpp
├── music/
│   └── Virtual_Insanity.mid
├── docs/
│   ├── CMD.txt
│   └── LINUX.txt
└── tools/
    └── code.txt
```

## Board Compatibility

The examples target Arduino-style environments and can be adapted for:

- Arduino boards
- ESP32
- Raspberry Pi Pico with an Arduino-compatible core

The exact `tone()` implementation can vary between board cores.

## License

MIT License.
