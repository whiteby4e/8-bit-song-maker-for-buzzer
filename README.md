<div align="center">

# 8-bit Song Maker for Buzzer

**Compose a melody. Generate code. Make a buzzer sing.**

A small Python toolkit for creating monophonic, retro-style melodies and converting MIDI files into Arduino-compatible C++ data for passive buzzers.

![Python](https://img.shields.io/badge/Python-3.x-3776AB?logo=python&logoColor=white)
![Arduino](https://img.shields.io/badge/Output-Arduino%20C%2B%2B-00979D?logo=arduino&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green)

</div>

---

## 🎵 What it does

The project provides two workflows:

- Write a melody using note names and durations.
- Convert a MIDI file into a single-note-at-a-time buzzer sequence.

The goal is a deliberately crunchy, lo-fi 8-bit sound using simple square-wave tones and rests. It is not an exact Game Boy sound emulator.

## ✨ Features

- Create melodies from simple note-and-duration input.
- Generate Arduino-compatible C++ code.
- Convert MIDI files into monophonic buzzer data.
- Account for MIDI tempo changes.
- Preserve chronological note timing.
- Reduce overlapping MIDI notes to one playable note at a time.
- Include Windows CMD and Linux instructions.

## ⚡ Quick start

### Requirements

- Python 3
- A passive buzzer
- An Arduino-compatible board, ESP32, or Raspberry Pi Pico with a compatible Arduino core
- `mido` for MIDI conversion

Install the MIDI dependency:

```bash
python -m pip install mido
```

### Create a melody

From the repository root:

```bash
# Windows
python src\song_maker.py

# Linux / macOS
python3 src/song_maker.py
```

Enter notes in this format:

```text
NOTE:DURATION
```

For example:

```text
C4:180 D4:180 E4:180 G4:300 R:120 E4:180 C4:400
```

- `C4`, `F#4`, `A5` — musical notes.
- The number is the duration in milliseconds.
- `R` — rest / silence.
- Separate notes with spaces.

The program asks for the buzzer GPIO and output filename, then generates a C++ sketch.

## 🎹 Convert a MIDI file

```bash
python src/chiptune_converter.py music/Virtual_Insanity.mid -o src/song.h
```

Then open `src/code.ino` in Arduino IDE.

The converter reads MIDI timing using ticks-per-beat and tempo changes, keeps events in chronological order, and produces a monophonic sequence. A single passive buzzer cannot play a chord, so overlapping notes must be reduced to one active pitch at a time.

The generated `song.h` is a local build output and is intentionally not committed.

## 🔌 Hardware example

The basic example uses GPIO 15:

```cpp
const int BUZZER_PIN = 15;
```

Connect the passive buzzer between the selected GPIO and GND, using a suitable driver if the buzzer requires more current than the GPIO can safely provide. Change the pin to match your board.

## 📁 Project layout

```text
8-bit-song-maker-for-buzzer/
├── src/
│   ├── song_maker.py
│   ├── chiptune_converter.py
│   └── code.ino
├── examples/basic/
│   └── buzzer_player.cpp
├── music/
├── docs/
└── tools/
```

## 🧪 Board compatibility

The examples target Arduino-style environments and can be adapted to Arduino boards, ESP32, and Raspberry Pi Pico with an Arduino-compatible core. The exact `tone()` implementation varies by board core.

## 📄 License

MIT — see [LICENSE](LICENSE).
