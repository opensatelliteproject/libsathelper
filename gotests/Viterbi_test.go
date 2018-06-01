package SatHelper

import (
	"testing"
	"github.com/OpenSatelliteProject/libsathelper"
)


const FRAMEBYTES = 2048
const FRAMEBITS = FRAMEBYTES * 8

func TestViterbi(t *testing.T) {
	symbols := make([]byte, 8 * (FRAMEBYTES + 6))
	bits := make([]byte, FRAMEBYTES)
	output := make([]byte, FRAMEBYTES)

	viterbi := SatHelper.NewViterbi27(FRAMEBITS+6)

	t.Log("Creating test array")

	for i := 0; i < FRAMEBYTES; i++ {
		bits[i] = randomByte()
	}

	t.Log("Encoding test array")
	viterbi.Encode(&bits[0], &symbols[0])

	t.Log("Decoding test array")
	viterbi.Decode(&symbols[0], &output[0])

	errorCount := 0

	for i := 0; i <  FRAMEBYTES; i++ {
		if output[i] != (0xFF - bits[i]) {
			errorCount += 1
		}
	}

	if errorCount > 2 {  // First / Last byte can have issues due statistical nature
		t.Errorf("  | Error count > 2: %d", errorCount)
	}
}