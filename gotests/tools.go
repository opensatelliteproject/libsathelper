package SatHelper

import (
	"math"
	"math/rand"
)

func exp(z complex64) complex64 {
	ex := math.Exp(float64(real(z)))
	r := ex * math.Cos(float64(imag(z)))
	c := ex * math.Sin(float64(imag(z)))
	return complex(float32(r), float32(c))
}

func mul(z complex64, v float32) complex64 {
	r := float32(real(z)) * v
	i := float32(imag(z)) * v

	return complex(r, i)
}

func add(a complex64, b complex64) complex64 {
	r := float32(real(a)) + float32(real(b))
	i := float32(imag(a)) + float32(imag(b))

	return complex(r, i)
}

func compareByteArray(a []byte, b []byte, len int) int {
	for i := 0; i < len; i++ {
		if a[i] != b[i] {
			return i
		}
	}
	return -1;
}

// Range -50 to 50
func genDistributedRandom() int8 {
	return int8(rand.Intn(100) - 50)
}

func randomByte() byte {
	return byte(rand.Intn(255) % 256)
}

func compareFloat(a float32, b float32, epsilon float32) bool {
	return math.Abs(float64(a - b)) < float64(epsilon)
}