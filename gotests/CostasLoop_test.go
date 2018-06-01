package SatHelper

import (
	"testing"
	"github.com/OpenSatelliteProject/libsathelper"
	"math"
	"math/rand"
)

var CostasLoopTestSize = 4096
var PHASEOFFSET float32 = 0.707
var NOISELEVEL float32 = 0.02
var NUMTAPS = 45
var SPS float64 = 4
var ROLLOFF = 0.35
var LOOPBW float32 = 2 * 3.141592653589793 / 100.0

var TEST_AVERAGE = 0.00004

func TestCostasLoop(t *testing.T) {
	testData := make([]complex64, CostasLoopTestSize)
	testData2 := make([]complex64, CostasLoopTestSize)
	frequencyDeviation := make([]float32, CostasLoopTestSize)
	costasloop := SatHelper.NewCostasLoop(LOOPBW, 2)

	phaseShift := exp(mul(complex(0, 1), PHASEOFFSET))

	for i := 0; i < CostasLoopTestSize; i++ {
		// Create Signal
		testData[i] = mul(phaseShift, (rand.Float32() * 2) - 1)
		// Add Noise
		testData[i] = add(testData[i], complex(rand.Float32() * NOISELEVEL, rand.Float32() * NOISELEVEL))
	}

	rrcTaps := SatHelper.FiltersRRC(1, SPS, SPS, ROLLOFF, NUMTAPS)
	rrcFilter := SatHelper.NewFirFilter(1, rrcTaps)

	t.Log("  | Filtering Test Data ")

	rrcFilter.Work(&testData[0], &testData2[0], CostasLoopTestSize)

	t.Log("  | Running Costas Loop ")

	costasloop.Work(&testData2[0], &testData[0], &frequencyDeviation[0], CostasLoopTestSize)

	highestValue := -100.0
	minimumValue := 100.0
	averageValue := 0.0

	for i := 0; i < CostasLoopTestSize; i++ {
		freqHz := frequencyDeviation[i] / ( 2 * math.Pi)
		averageValue += float64(freqHz)
		highestValue = math.Max(highestValue, float64(freqHz))
		minimumValue = math.Min(minimumValue, float64(freqHz))
	}

	averageValue /= float64(CostasLoopTestSize)

	t.Logf("    | Highest Deviation: %f", highestValue)
	t.Logf("    | Minimum Deviation: %f", minimumValue)
	t.Logf("    | Average Deviation: %f", averageValue)

	if averageValue > TEST_AVERAGE {
		t.Errorf("    | Average Value > %f", TEST_AVERAGE)
	}
}