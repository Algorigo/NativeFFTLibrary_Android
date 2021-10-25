package com.algorigo.nativefft

class NativeFFT {

    /**
     * A native method that is implemented by the 'nativefft' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'nativefft' library on application startup.
        init {
            System.loadLibrary("nativefft")
        }

        @JvmStatic
        fun fftC2c(arrayCount: Int, values: List<DoubleArray>): List<Array<Complex>> {
            return fftC2c(arrayCount, values, values.size)
        }

        @JvmStatic
        fun fftC2cAbs(arrayCount: Int, values: List<DoubleArray>): List<DoubleArray> {
            return fftC2cAbs(arrayCount, values, values.size)
        }

        @JvmStatic
        fun fftC2cAbsSum(arrayCount: Int, values: List<DoubleArray>): List<Double> {
            return fftC2cAbsSum(arrayCount, values, values.size)
        }

        @JvmStatic
        external fun fftC2c(arrayCount: Int, values: List<DoubleArray>, n: Int): List<Array<Complex>>

        @JvmStatic
        external fun fftC2cAbs(arrayCount: Int, values: List<DoubleArray>, n: Int): List<DoubleArray>

        @JvmStatic
        external fun fftC2cAbsSum(arrayCount: Int, values: List<DoubleArray>, n: Int): List<Double>
    }
}