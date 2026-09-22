import mido
import sys


INPUT = sys.argv[1]
OUTPUT = "song.h"


BUZZER_PIN = 25


def midi_to_freq(note):
    return round(440 * (2 ** ((note - 69) / 12)))


def quantize(note):
    # گی بوی مدلی کنیم
    scale = [
        0,2,4,5,7,9,11
    ]

    octave = note // 12
    n = note % 12

    closest = min(
        scale,
        key=lambda x: abs(x-n)
    )

    return octave*12 + closest



mid = mido.MidiFile(INPUT)


events = []

time = 0


#تریاک ها رو میخوریم
for track in mid.tracks:

    current = 0

    active = {}

    for msg in track:

        current += msg.time


        if msg.type == "note_on" and msg.velocity:

            active[msg.note] = current


        elif msg.type == "note_off" or (
            msg.type=="note_on" and msg.velocity==0
        ):

            if msg.note in active:

                length = current-active[msg.note]

                events.append(
                    (
                        msg.note,
                        length
                    )
                )

                del active[msg.note]


# همون چیه تمیز کاری
events.sort(key=lambda x:x[1])


notes=[]


for note,length in events:

    note=quantize(note)

    freq=midi_to_freq(note)

    duration=int(length*1000)


    # حذف نت‌های خیلی کوتاه
    if duration>50:

        notes.append(
            (
                freq,
                duration
            )
        )



with open(OUTPUT,"w") as f:

    f.write("#define BUZZER_PIN 25\n\n")

    f.write("struct Note {int freq; int time;};\n\n")

    f.write("Note song[]={\n")


    for freq,time in notes:

        f.write(
            f"{{{freq},{time}}},\n"
        )


    f.write("{0,0}\n};")


print("finished!")
print("Notes:",len(notes))
print("Created:",OUTPUT)