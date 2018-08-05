import wave, struct

print("Script started...")

# Read all of the values from the numbers file
# and store in a list of type float.
# The value is multlied by ≈ ±32767 as using 16-bit integers.
frame = []
with open("inputOut.txt", "r") as f:
    for sample in f:
        frame.append(float(sample) * 0.9)
        #if float(sample) > 1.0:
        #    frame.append( 1 )
        #else:
        #    frame.append( int (float(sample) * 32767.0) )

# Initialise information for writing to a wav file.
sampleRate = 96000.0 # hertz
wavef = wave.open('inputOut.wav','w')
wavef.setnchannels(1) # mono
wavef.setsampwidth(2) # ' 16 bits - 2 bytes - DO NOT CHANGE!!!
wavef.setframerate(sampleRate)

# Cycle through each sample in the frame and
# write into the wav file.
for sample in frame:
    print( int(sample) )
    data = struct.pack('<h', int (sample) )
    wavef.writeframesraw(data);

wavef.close()

print("...script complete!")
