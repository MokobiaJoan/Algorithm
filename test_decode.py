import base64
import random
import subprocess
import string

def run_ascii85_decoder(input_str):
    proc = subprocess.run(
        ["./ascii85", "-d"],
        input=input_str.encode(),
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    return proc.returncode, proc.stdout, proc.stderr

def test_valid_random():
    print("[VALID DATA TESTS]")
    for i in range(5):
        data = bytes(random.getrandbits(8) for _ in range(random.randint(1, 30)))
        encoded = base64.a85encode(data, adobe=True).decode()
        retcode, stdout, stderr = run_ascii85_decoder(encoded)

        if stdout != data or retcode != 0:
            print(f"\n[FAIL] Test {i+1}")
            print(f"Original (hex): {data.hex()}")
            print(f"Encoded: {encoded}")
            print(f"Decoded (hex): {stdout.hex()}")
            print(f"Return code: {retcode}")
            print(f"stderr: {stderr.decode()}")
        else:
            print(f"Passed test {i + 1}")

def test_invalid_random():
    print("\n[INVALID DATA TESTS]")
    for i in range(5):
        corrupted = ''.join(random.choices(string.printable, k=random.randint(10, 30)))
        retcode, stdout, stderr = run_ascii85_decoder(corrupted)

        if retcode != 0:
            print(f"Passed test {i + 1} (correctly failed with code {retcode})")
        else:
            print(f"FAILED: test {i + 1} unexpectedly succeeded (code {retcode})")

if __name__ == "__main__":
    test_valid_random()
    test_invalid_random()