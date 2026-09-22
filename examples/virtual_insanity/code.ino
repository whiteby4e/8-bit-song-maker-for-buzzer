#include "song.h"

void playSong() {
  for (size_t i = 0; i < SONG_LENGTH; ++i) {
    if (song[i].freq > 0) {
      tone(BUZZER_PIN, song[i].freq, song[i].time);
    } else {
      noTone(BUZZER_PIN);
    }

    delay(song[i].time);
    noTone(BUZZER_PIN);
  }
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  playSong();
  noTone(BUZZER_PIN);
}

void loop() {
}
