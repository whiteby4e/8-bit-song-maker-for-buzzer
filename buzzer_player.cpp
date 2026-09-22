/*
  8-bit Song Maker for Buzzer
  Arduino-compatible passive buzzer example.

  Change BUZZER_PIN if your buzzer uses another GPIO.
*/

const int BUZZER_PIN = 15;

struct Note {
  int frequency;
  int duration;
};

// Original demo melody. Frequency 0 means rest.
const Note song[] = {
  {262, 160}, // C4
  {294, 160}, // D4
  {330, 160}, // E4
  {392, 260}, // G4
  {0,   100}, // Rest
  {392, 160}, // G4
  {440, 160}, // A4
  {494, 260}, // B4
  {0,   100}, // Rest
  {523, 300}, // C5
  {494, 160}, // B4
  {440, 160}, // A4
  {392, 300}, // G4
};

const size_t SONG_LENGTH = sizeof(song) / sizeof(song[0]);

void playSong() {
  for (size_t i = 0; i < SONG_LENGTH; ++i) {
    if (song[i].frequency > 0) {
      tone(BUZZER_PIN, song[i].frequency, song[i].duration);
    } else {
      noTone(BUZZER_PIN);
    }

    delay(song[i].duration);
    noTone(BUZZER_PIN);
    delay(20);
  }
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  playSong();
  delay(700);
}
