import soundfile as sf
import scipy.signal as signal

input_file = f"../assets/audio/{input('Input audio (wav): ')}"
output_file = f"../assets/ir/{input('Output inpulse response: ')}"

new_sample_rate = 44100

data, original_sample_rate = sf.read(input_file, dtype="float32")

if original_sample_rate != new_sample_rate:
    data = signal.resample_poly(
        data,
        new_sample_rate,
        original_sample_rate,
        axis=0
    )

if data.ndim > 1:
    data = data.mean(axis=1)

with open(output_file, "w") as f:
    for sample in data:
        f.write(f"{sample:.8f}\n")

print(f"Original sample rate: {original_sample_rate} Hz")
print(f"New sample rate:      {new_sample_rate} Hz")
print(f"Number of samples:    {len(data)}")
