#include "song.h"

void setup()
{
  for(int i=0; song[i].freq; i++)
  {
    tone(
      BUZZER_PIN,
      song[i].freq,
      song[i].time
    );

    delay(song[i].time);
  }
}

void loop(){}
